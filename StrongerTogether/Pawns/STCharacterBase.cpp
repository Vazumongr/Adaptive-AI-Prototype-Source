// Fill out your copyright notice in the Description page of Project Settings.


#include "STCharacterBase.h"


#include "StrongerTogether/Abilities/STAbilitySystemComponent.h"
#include "StrongerTogether/Pawns/STAnchor.h"
#include "StrongerTogether/Abilities/STGameplayAbility.h"
#include "StrongerTogether/DataAssets/STAbilityDataAsset.h"

// Sets default values
ASTCharacterBase::ASTCharacterBase()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Skeletal Mesh Component"));
	SetRootComponent(SkeletalMeshComponent);

	AbilitySystemComponent = CreateDefaultSubobject<USTAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);

	AttributeSet = CreateDefaultSubobject<USTAttributeSet>(TEXT("AttributeSet"));

	CharacterLevel = 1;
	bAbilitiesInitialized = false;

	FGuid MyID = FGuid::NewGuid();
	Name = MyID.ToString();
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

void ASTCharacterBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASTCharacterBase, CharacterLevel);
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
			if(DataAsset == nullptr) return;
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

bool ASTCharacterBase::SetCharacterLevel(int32 NewLevel)
{
	if(CharacterLevel != NewLevel && NewLevel > 0)
	{
		CharacterLevel = NewLevel;
		return true;
	}
	return false;
}

// Called when the game starts or when spawned
void ASTCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

