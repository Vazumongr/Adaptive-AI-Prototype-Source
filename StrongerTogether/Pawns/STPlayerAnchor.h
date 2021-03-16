// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "StrongerTogether/Pawns/STAnchor.h"
#include "STPlayerAnchor.generated.h"


UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPlayerAnchorMoving);	//Player Only

UCLASS()
class STRONGERTOGETHER_API ASTPlayerAnchor : public ASTAnchor
{
	GENERATED_BODY()

public:
	virtual void SpawnPartyCharacter() override;	// Override for player
	virtual void Advance();	//Player only
	
	FPlayerAnchorMoving AnchorMoving;	//Player only
	FPlayerAnchorMoving AnchorStopping;	//Player only

private:


protected:

	ASTPlayerAnchor();

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION()
	virtual void ComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);	//Player only

	
	
	bool bIsMoving = false;	//Player only
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	float MovementSpeed = 20.f;	//Player only

	bool bMoveForward = false;	//Player only

	FVector TargetLocation;	//Player only

};