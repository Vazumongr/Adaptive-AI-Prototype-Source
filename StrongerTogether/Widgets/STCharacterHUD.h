// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STCharacterHUD.generated.h"

/**
 * 
 */
UCLASS()
class STRONGERTOGETHER_API USTCharacterHUD : public UUserWidget
{
	GENERATED_BODY()

public: 
	virtual bool Initialize() override;

	void ClearHUD();

	void SetCharacterTurnText(const FName& CharName);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ASTPlayerController* OwningController;
	
	UFUNCTION(BlueprintCallable)
	void Update(class ASTPartyCharacter* InActor);

protected:

	void UpdateController(int32 AbilityIndex) const;

	UFUNCTION()
	void UpdateOwnerAbilityIndexToZero() const;
	UFUNCTION()
	void UpdateOwnerAbilityIndexToOne() const;
	UFUNCTION()
	void UpdateOwnerAbilityIndexToTwo() const;
	UFUNCTION()
	void UpdateHealth();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* CharacterNameTextBlock;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* AbilityOneTextBlock;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* AbilityTwoTextBlock;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* AbilityThreeTextBlock;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* HealthTextBlock;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* ManaTextBlock;;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UTextBlock* CharacterTurnTextBlock;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UBorder* AbilityOneBorder;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UBorder* AbilityTwoBorder;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta = (BindWidget))
	class UBorder* AbilityThreeBorder;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	class ASTPartyCharacter* SelectedCharacter;
	
};
