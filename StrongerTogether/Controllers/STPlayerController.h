// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "STPlayerController.generated.h"

UDELEGATE()
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCharacterSelect);

/**
 * 
 */
UCLASS()
class STRONGERTOGETHER_API ASTPlayerController : public APlayerController
{
	GENERATED_BODY()

	virtual void SetupInputComponent() override;

	virtual void BeginPlay() override;
	
	
protected:
	UFUNCTION(BlueprintImplementableEvent)
    void UpdateCharacterHUD();
	
	UFUNCTION(BlueprintCallable)
	void AdvanceCharacters();

	UFUNCTION()
	void SelectCharacter();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	AActor* SelectedActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	class UUserWidget* CharacterHUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TSubclassOf<class UUserWidget> CharacterHUDClass;

	uint8 Counter = 0;
	
};
