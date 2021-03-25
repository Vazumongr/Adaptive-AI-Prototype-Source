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

	void ClearHUD() const;

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
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* CharacterNameTextBlock;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* AbilityOneTextBlock;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* AbilityTwoTextBlock;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* AbilityThreeTextBlock;;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* HealthTextBlock;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* ManaTextBlock;;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UTextBlock* CharacterTurnTextBlock;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UBorder* AbilityOneBorder;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UBorder* AbilityTwoBorder;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (BindWidget))
	class UBorder* AbilityThreeBorder;
	
};
