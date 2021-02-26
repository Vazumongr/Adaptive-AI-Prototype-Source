// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "AbilitySystemInterface.h"		
#include "GameFramework/Pawn.h"
#include "StrongerTogether/Abilities/STAttributeSet.h"
#include "Abilities/GameplayAbilityTargetTypes.h"

#include "STCharacterBase.generated.h"

UCLASS()
class STRONGERTOGETHER_API ASTCharacterBase : public APawn, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ASTCharacterBase();


	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_Controller() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// Implement IAbilitySystemInterface
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override { return AbilitySystemComponent; }

	void AddStartupGameplayAbilities();
	
	UFUNCTION(BlueprintCallable)
	void ActivateAbilityByIndex(int32 Index);

	void SetTarget(AActor* TargetActor);
	
	/** The component used to handle ability system interactions */
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Abilities")
	UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = GameplayEffectContainer)
	FGameplayAbilityTargetDataHandle TargetData;
	
	/** List of attributes modified by the ability system */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	USTAttributeSet* AttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HealthValue;

	bool bAbilitiesInitialized = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite);
	bool bPartyCharacter = false;

	UPROPERTY(EditAnywhere, Replicated, Category = "Abilities")
	int32 CharacterLevel;

	// Used for setting initial abilities
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TArray<class USTAbilityDataAsset*> InitialAbilitiesDAs;

	// Used for setting initial abilities
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TArray<TSubclassOf<class USTGameplayAbility>> InitialAbilities;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	TArray<FGameplayAbilitySpecHandle> AbilitySpecHandles;
	
	// Used for setting default character stats
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Abilities")
	TSubclassOf<class UGameplayEffect> InitialStats;
	
#pragma region NonGAS
	
	virtual void SetOwningAnchor(class ASTAnchor* InAnchor);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString AbilityOne;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString AbilityTwo;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString AbilityThree;
	
#pragma endregion 
#pragma region GETTERSSETTERS =
	
	/** Returns current health, will be 0 if dead */
	UFUNCTION(BlueprintCallable)
    virtual float GetHealth() const;

	/** Returns maximum health, health will never be greater than this */
	UFUNCTION(BlueprintCallable)
    virtual float GetMaxHealth() const;

	/** Returns current mana */
	UFUNCTION(BlueprintCallable)
    virtual float GetMana() const;

	/** Returns maximum mana, mana will never be greater than this */
	UFUNCTION(BlueprintCallable)
    virtual float GetMaxMana() const;

	/** Modifies the character level, this may change abilities. Returns true on success */
	UFUNCTION(BlueprintCallable)
    virtual bool SetCharacterLevel(int32 NewLevel);

	UFUNCTION(BlueprintCallable)
	virtual int32 GetCharacterLevel() const { return CharacterLevel; }

#pragma endregion 

	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess))
	class ASTAnchor* OwningAnchor;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta =(AllowPrivateAccess))
	class USkeletalMeshComponent* SkeletalMeshComponent;

};
