#include "STPlayerAnchor.h"

#include "StrongerTogether/Characters/STPartyCharacter.h"
#include "Components/BoxComponent.h"
#include "StrongerTogether/GameStates/STMainGameState.h"

ASTPlayerAnchor::ASTPlayerAnchor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	BoxCollider->OnComponentBeginOverlap.AddDynamic(this, &ASTPlayerAnchor::ComponentBeginOverlap);
}

void ASTPlayerAnchor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if(bIsMoving)
	{
		const float MovementThisFrame = MovementSpeed * DeltaSeconds;
		FVector NewLocation = GetActorLocation();
		NewLocation.Y += MovementThisFrame;
		SetActorLocation(NewLocation);
	}
}

// Moved to be called in BeginPlay()
void ASTPlayerAnchor::SpawnPartyCharacter()
{
	FActorSpawnParameters SpawnParameters;
	for(TSubclassOf<ASTCharacterBase> Class : CharactersClasses)
	{
		if(Class->IsChildOf(ASTPartyCharacter::StaticClass()))
		{
			if(ASTPartyCharacter* PartyMember = GetWorld()->SpawnActor<ASTPartyCharacter>(Class, GetActorLocation(), GetActorRotation(), SpawnParameters))
			{
				AddPartyCharacter(PartyMember);
				PartyMember->SetOwningAnchor(this);
				PartyMember->AttachToActor(this, FAttachmentTransformRules::KeepWorldTransform);
			}
		}
	}
	ArrangeParty();
}

void ASTPlayerAnchor::Advance()
{
	if(bInCombat) return;
	bIsMoving = true;
	AnchorMoving.Broadcast();
}

void ASTPlayerAnchor::ComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
     bool bFromSweep, const FHitResult& SweepResult)
{
	if(ASTAnchor* EnemyAnchor = Cast<ASTAnchor>(OtherActor))
	{
		bIsMoving = false;
		AnchorStopping.Broadcast();
		GameState->StartCombat(EnemyAnchor);
	}
}