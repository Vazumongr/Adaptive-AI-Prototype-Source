// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "STMainGameMode.generated.h"

/**
 * 
 */
UCLASS()
class STRONGERTOGETHER_API ASTMainGameMode : public AGameModeBase
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
	
public:


	virtual void HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer) override;

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TSubclassOf<AActor> PathPointClass;

	UPROPERTY()
	class ASTAnchor* Anchor;

	UPROPERTY()
	TArray<AActor*> PathPoints;

	
	
};
