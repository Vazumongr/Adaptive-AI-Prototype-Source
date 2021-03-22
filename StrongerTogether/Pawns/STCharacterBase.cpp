// Fill out your copyright notice in the Description page of Project Settings.


#include "STCharacterBase.h"


#include "StrongerTogether/Abilities/STAbilitySystemComponent.h"
#include "StrongerTogether/Pawns/STAnchor.h"
#include "StrongerTogether/Abilities/STGameplayAbility.h"
#include "StrongerTogether/DataAssets/STAbilityDataAsset.h"
#include "StrongerTogether/Components/STActorWidgetComponent.h"
#include "StrongerTogether/GameStates/STMainGameState.h"

// Sets default values
ASTCharacterBase::ASTCharacterBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh Component"));
	SetRootComponent(SkeletalMeshComponent);

	ActorWidgetComponent = CreateDefaultSubobject<USTActorWidgetComponent>(TEXT("Actor Widget Component"));
	ActorWidgetComponent->SetupAttachment(RootComponent);

	AbilitySystemComponent = CreateDefaultSubobject<USTAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	AttributeSet = CreateDefaultSubobject<USTAttributeSet>(TEXT("AttributeSet"));

	CharacterLevel = 1;
	bAbilitiesInitialized = false;

	InitialAbilitiesDAs.Init(nullptr, 3);	
}

// Called when the game starts or when spawned
void ASTCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	bMyTurn = false;
	AbilitySystemComponent->AbilityCommittedCallbacks.AddUObject(this, &ASTCharacterBase::TurnOver);
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AttributeSet->GetHealthAttribute()).AddUObject(this, &ASTCharacterBase::HealthChanged);
	
}

void ASTCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
		AddStartupGameplayAbilities();
	}
}

void ASTCharacterBase::OnRep_Controller()
{
	Super::OnRep_Controller();

	if(AbilitySystemComponent)
	{
		AbilitySystemComponent->RefreshAbilityActorInfo();
	}
}

void ASTCharacterBase::TurnOver(UGameplayAbility*)
{
	Cast<ASTMainGameState>(GetWorld()->GetGameState())->PlayerTurnOver();
}

void ASTCharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASTCharacterBase, CharacterLevel);
}

void ASTCharacterBase::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	UE_LOG(LogTemp, Warning, TEXT("PostEditChange"));

	Super::PostEditChangeProperty(PropertyChangedEvent);
	
	if(PropertyChangedEvent.Property != nullptr && PropertyChangedEvent.Property->GetFName() == GET_MEMBER_NAME_CHECKED(ASTCharacterBase, InitialAbilitiesDAs))
	{
		if(PropertyChangedEvent.ChangeType == EPropertyChangeType::ArrayAdd)
		{
			if(InitialAbilitiesDAs.Num() >= 4)
			{
				InitialAbilitiesDAs.RemoveAt(3);
			}
		}
		else if(PropertyChangedEvent.ChangeType == EPropertyChangeType::ArrayRemove)
		{
			if(InitialAbilitiesDAs.Num() < 3)
			{
				InitialAbilitiesDAs.Add(nullptr);
			}
		}
		else if(PropertyChangedEvent.ChangeType == EPropertyChangeType::ArrayClear)
		{
			InitialAbilitiesDAs.Init(nullptr, 3);
		}
		
	}
	
}

void ASTCharacterBase::SetOwningAnchor(ASTAnchor* InAnchor)
{
	if(InAnchor != nullptr)
	{
		OwningAnchor = InAnchor;
	}
}

void ASTCharacterBase::AddStartupGameplayAbilities()
{
	check(AbilitySystemComponent);

	if(!bAbilitiesInitialized)
	{
		int32 Counter = 1;
		for(USTAbilityDataAsset* DataAsset : InitialAbilitiesDAs)
		{
			if(DataAsset == nullptr) continue;
			TSubclassOf<USTGameplayAbility>& Ability = DataAsset->GameplayAbilityClass;
			FGameplayAbilitySpecHandle TempHandle = AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(Ability, GetCharacterLevel(), INDEX_NONE, this));
			AbilitySpecHandles.Add(TempHandle);
			if(Counter == 1)
				AbilityOne = DataAsset->AbilityName;
			else if(Counter == 2)
				AbilityTwo = DataAsset->AbilityName;
			else if(Counter == 3)
				AbilityThree = DataAsset->AbilityName;

			Counter++;
		}
		

		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(InitialStats, 1, EffectContext);
		if (NewHandle.IsValid())
		{
			UE_LOG(LogTemp, Warning, TEXT("Handle valid"));
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*NewHandle.Data.Get());
		}
	}

	bAbilitiesInitialized = true;
	
}

bool ASTCharacterBase::HandleTarget(AActor* TargetActor, int32 AbilityIndexToActivate)
{
	if(!bMyTurn) return false;
	if(TargetActor == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("You called HandleTarget with a nullptr!"));
		return false;
	}
	else
	{
		if(AbilityIndexToActivate > AbilitySpecHandles.Num() - 1 || AbilityIndexToActivate < 0)
		{
			UE_LOG(LogTemp, Error, TEXT("That ability is out of bounds!"));
			return false;
		}
		UE_LOG(LogTemp, Warning, TEXT("You are telling me to use ability %i on target %s"), AbilityIndexToActivate, *TargetActor->GetName());

		// Check tags on ability
		FGameplayAbilitySpecHandle& AbilityToActivate = AbilitySpecHandles[AbilityIndexToActivate];
		UGameplayAbility* AbilityBeingActivated = AbilitySystemComponent->FindAbilitySpecFromHandle(AbilityToActivate)->Ability;
		FGameplayTagContainer& AbilitiesTags = AbilityBeingActivated->AbilityTags;

		
		
		if(/*Cast<AllyClassPtr>(TargetActor)*/ AllyClass != nullptr && TargetActor->GetClass()->IsChildOf(AllyClass)) // ally
		{
			if(AbilitiesTags.HasTagExact(FGameplayTag::RequestGameplayTag(FName("Ability.Targets.Ally"))))
			{
				SetTarget(TargetActor);
				ActivateAbilityByIndex(AbilityIndexToActivate);
			}
		}
		else if(/*Cast<EnemyClass>(TargetActor)*/ EnemyClass != nullptr && TargetActor->GetClass()->IsChildOf(EnemyClass))
		{
			if(AbilitiesTags.HasTagExact(FGameplayTag::RequestGameplayTag(FName("Ability.Targets.Enemy"))))
			{
				SetTarget(TargetActor);
				ActivateAbilityByIndex(AbilityIndexToActivate);
			}
		}
	}
	return true;
}

void ASTCharacterBase::ActivateAbilityByIndex(int32 Index)
{
	if(AbilitySystemComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("%f"), AbilitySpecHandles.Num());
		if(Index < AbilitySpecHandles.Num() && Index > -1)
		{
			AbilitySystemComponent->TryActivateAbility(AbilitySpecHandles[Index]);
		}
		
	}
}

void ASTCharacterBase::SetTarget(AActor* TargetActor)
{
	TargetData.Clear();
	FGameplayAbilityTargetData_ActorArray* NewData = new FGameplayAbilityTargetData_ActorArray();
	NewData->TargetActorArray.Add(TargetActor);
	TargetData.Add(NewData);
}

float ASTCharacterBase::GetHealth() const
{
	if(!AttributeSet)
		return 1.f;

	return AttributeSet->GetHealth();
}

float ASTCharacterBase::GetMaxHealth() const
{
	if(!AttributeSet)
		return 1.f;

	return AttributeSet->GetMaxHealth();
}

float ASTCharacterBase::GetMana() const
{
	if(!AttributeSet)
		return 1.f;

	return AttributeSet->GetMana();
}

float ASTCharacterBase::GetMaxMana() const
{
	if(!AttributeSet)
		return 1.f;

	return AttributeSet->GetMaxMana();
}

float ASTCharacterBase::GetSpeed() const
{
	if(!AttributeSet)
		return 1.f;
	return AttributeSet->GetSpeed();
}

bool ASTCharacterBase::SetCharacterLevel(int32 NewLevel)
{
	if(CharacterLevel != NewLevel && NewLevel > 0)
	{
		CharacterLevel = NewLevel;
		return true;
	}
	return false;
}

