// Fill out your copyright notice in the Description page of Project Settings.


#include "STAnchor.h"

#include "StrongerTogether/Characters/STPartyCharacter.h"

// Sets default values
ASTAnchor::ASTAnchor()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

void ASTAnchor::Tick(float DeltaSeconds)
{
	if(bIsMoving)
	{
		const float MovementThisFrame = MovementSpeed * DeltaSeconds;
		if(FMath::Abs(TargetLocation.Y - GetActorLocation().Y) <= MovementThisFrame)
		{
			SetActorLocation(TargetLocation);
			bIsMoving = false;
			AnchorStopping.Broadcast();
		}
		else
		{
			FVector NewLocation = GetActorLocation();
            NewLocation.Y += MovementThisFrame;
            SetActorLocation(NewLocation);
		}
		
	}
}

void ASTAnchor::SpawnPartyCharacter()
{
	FActorSpawnParameters SpawnParameters;
	for(int i = 0; i < 4; i++)
	{
		if(ASTPartyCharacter* PartyMember = GetWorld()->SpawnActor<ASTPartyCharacter>(CharactersClass, GetActorLocation(), GetActorRotation(), SpawnParameters))
		{
			AddPartyCharacter(PartyMember);
			PartyMember->SetOwningAnchor(this);
			PartyMember->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
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

void ASTAnchor::AddPartyCharacter(AActor* InActor)
{
	PartyActors.Add(InActor);
}

void ASTAnchor::RemovePartyCharacter(AActor* InActor)
{
	PartyActors.Remove(InActor);
}

void ASTAnchor::Advance(FVector NewLocation)
{
	TargetLocation = NewLocation;
	bIsMoving = true;
	AnchorMoving.Broadcast();
}

