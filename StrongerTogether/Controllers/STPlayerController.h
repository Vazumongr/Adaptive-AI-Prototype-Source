// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Abilities/GameplayAbilityTargetTypes.h"

#include "STPlayerController.generated.h"

UENUM(BlueprintType)
enum class ECombatState : uint8
{
	EnemiesTurn,
	NoCharSelected,
	CharacterSelected,
	AbilityPrimed
};

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
	
public:
	UFUNCTION(BlueprintCallable)
	void SetAbilityIndex(int32 Index);
	
	
protected:
	UFUNCTION(BlueprintImplementableEvent)
    void UpdateCharacterHUD();
	
	UFUNCTION(BlueprintCallable)
	void AdvanceCharacters();

	UFUNCTION()
	void SelectCharacter();
	
	bool GetSelectedCharacter(FHitResult& HitResult);
	
	void SetSelectedPartyCharacter(class ASTPartyCharacter* InActor);

	void HandlePartyCharacter(class ASTPartyCharacter* PartyCharacter);
	void HandleEnemyCharacter(class ASTEnemyCharacter* EnemyCharacter);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	class ASTPartyCharacter* SelectedActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	class USTCharacterHUD* CharacterHUD;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess))
	TSubclassOf<class UUserWidget> CharacterHUDClass;

	uint8 Counter = 0;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	int32 AbilityIndex;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	ECombatState PlayersCombatState;
	
};
