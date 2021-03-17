// Fill out your copyright notice in the Description page of Project Settings.


#include "STAnchor.h"

#include "Components/BoxComponent.h"
#include "StrongerTogether/Characters/STEnemyCharacter.h"
#include "StrongerTogether/GameStates/STMainGameState.h"

// Sets default values
ASTAnchor::ASTAnchor()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollider"));
	SetRootComponent(BoxCollider);
	BoxCollider->SetBoxExtent(FVector(32,300,32));

}

void ASTAnchor::BeginPlay()
{
	Super::BeginPlay();
	SpawnPartyCharacter();
	GameState = Cast<ASTMainGameState>(GetWorld()->GetGameState());
	if(GameState != nullptr)
	{
		GameState->CombatStartedDelegateM.AddUObject(this, &ASTAnchor::CombatStarted);
	}
	bInCombat = false;
}

void ASTAnchor::SpawnPartyCharacter()
{
	FActorSpawnParameters SpawnParameters;
	for(TSubclassOf<ASTCharacterBase> Class : CharactersClasses)
	{
		if(Class->IsChildOf(ASTEnemyCharacter::StaticClass()))
		{
			if(ASTEnemyCharacter* PartyMember = GetWorld()->SpawnActor<ASTEnemyCharacter>(Class, GetActorLocation(), GetActorRotation(), SpawnParameters))
            {
            	AddPartyCharacter(PartyMember);
            	PartyMember->SetOwningAnchor(this);
            	PartyMember->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
            }
		}
	}
	ArrangeParty();
}

void ASTAnchor::ArrangeParty()
{
	int8 Flip = 1;
	float OffsetMultiplyer = 1;
	
	for(AActor* Actor : PartyActors)
	{
		if(PartyActors.Num()%2 == 0)
		{
			FVector NewLocation = GetActorLocation();
			UE_LOG(LogTemp, Warning, TEXT("New Location: %s"), *NewLocation.ToString());

			UE_LOG(LogTemp, Warning, TEXT("NewLocation.Y = %f * %d * %d"), PartyOffset, (uint8)OffsetMultiplyer, Flip);
			NewLocation.Y += PartyOffset * (uint8)OffsetMultiplyer * Flip;
			UE_LOG(LogTemp, Warning, TEXT("New Location.Y: %f"), NewLocation.Y);
			OffsetMultiplyer += .5f;
			UE_LOG(LogTemp, Warning, TEXT("OffsetMultiplyer: %f"), OffsetMultiplyer);
			Flip *= -1;
			NewLocation = NewLocation - GetActorLocation();
			UE_LOG(LogTemp, Warning, TEXT("Final New Location(relative): %s"), *NewLocation.ToString());
			Actor->SetActorRelativeLocation(NewLocation);
			UE_LOG(LogTemp, Warning, TEXT("================LINE PURGE==============="));
		}
	}
}

void ASTAnchor::AddPartyCharacter(class ASTCharacterBase* InActor)
{
	PartyActors.Add(InActor);
}

void ASTAnchor::RemovePartyCharacter(class ASTCharacterBase* InActor)
{
	PartyActors.Remove(InActor);
}

void ASTAnchor::CombatStarted()
{
	UE_LOG(LogTemp, Warning, TEXT("CombatStarted!"));
	bInCombat = true;
}

