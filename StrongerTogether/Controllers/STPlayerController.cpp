// Fill out your copyright notice in the Description page of Project Settings.


#include "STPlayerController.h"


#include "Blueprint/UserWidget.h"

#include "Kismet/GameplayStatics.h"

#include "StrongerTogether/GameModes/STMainGameMode.h"
#include "StrongerTogether/Pawns/STAnchor.h"
#include "StrongerTogether/Characters/STPartyCharacter.h"
#include "StrongerTogether/Characters/STEnemyCharacter.h"
#include "StrongerTogether/Widgets/STCharacterHUD.h"

void ASTPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    InputComponent->BindAction("Advance", IE_Pressed, this, &ASTPlayerController::AdvanceCharacters);
    InputComponent->BindAction("SelectCharacter", IE_Pressed, this, &ASTPlayerController::SelectCharacter);
}

void ASTPlayerController::BeginPlay()
{
    CharacterHUD = CreateWidget<USTCharacterHUD>(this, CharacterHUDClass);
    CharacterHUD->AddToViewport();
    CharacterHUD->OwningController = this;
    CharacterHUD->ClearHUD();
    bShowMouseCursor = true;
    PlayersCombatState = ECombatState::NoCharSelected;
    AbilityIndex = -1;
}

void ASTPlayerController::PrimeAbility(int32 Index)
{
    if(SelectedCharacter == nullptr) return;
    AbilityIndex = Index;
    PlayersCombatState = ECombatState::AbilityPrimed;
}

void ASTPlayerController::AdvanceCharacters()
{
    UE_LOG(LogTemp, Warning, TEXT("Advancing"));

    if(ASTMainGameMode* GameMode = Cast<ASTMainGameMode>(GetWorld()->GetAuthGameMode()))
    {
        if(Counter > GameMode->PathPoints.Num() - 1 || Counter < 0) return;
        const FVector NextLocation = GameMode->PathPoints[Counter]->GetActorLocation();
        
        if(ASTAnchor* Anchor = Cast<ASTAnchor>(GetPawn()))
        {
            Anchor->Advance(NextLocation);
        }
        Counter++;
    }
}

bool ASTPlayerController::GetSelectedCharacter(FHitResult& HitResult)
{
    FVector WorldLocation, WorldDirection;
    DeprojectMousePositionToWorld(WorldLocation, WorldDirection);
    
    const FVector StartLocation = PlayerCameraManager->GetCameraLocation();
    const FVector EndLocation = (StartLocation + (WorldDirection * 1000));
        
    TArray<AActor*> ActorsToIgnore;

    return UKismetSystemLibrary::LineTraceSingle(this, StartLocation, EndLocation, UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel18),
        false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResult, true, FLinearColor::White,
        FLinearColor::Yellow, 5.0f);
}

void ASTPlayerController::SetSelectedPartyCharacter(ASTPartyCharacter* InActor)
{
    SelectedCharacter = InActor;
    PlayersCombatState = ECombatState::CharacterSelected;
    if(CharacterHUD != nullptr)
    {
        UpdateCharacterHUD();
    }
}

void ASTPlayerController::SelectCharacter()
{
    if(PlayersCombatState == ECombatState::EnemiesTurn) return;
    
    FHitResult HitResult;

    if(GetSelectedCharacter(HitResult))
    {
        if(HitResult.GetActor() == nullptr) return;
        
        if(PlayersCombatState != ECombatState::AbilityPrimed)   // At this point, our only options are NoCharSelected and CharSelected
        {
            if(ASTPartyCharacter* PartyCharacter = Cast<ASTPartyCharacter>(HitResult.GetActor()))
            {
                SetSelectedPartyCharacter(PartyCharacter);
            }
        }
        else
        {
            SelectedCharacter->HandleTarget(HitResult.GetActor(), AbilityIndex);
            PlayersCombatState = ECombatState::CharacterSelected;
            if(CharacterHUD != nullptr)
            {
                UpdateCharacterHUD();
            }
        }
    }
    else
    {
        PlayersCombatState = ECombatState::NoCharSelected;
        SelectedCharacter = nullptr;
        CharacterHUD->ClearHUD();
    }
}
/* Not needed. Bad refactor
void ASTPlayerController::HandlePartyCharacter(ASTPartyCharacter* PartyCharacter)
{
    if(PlayersCombatState == ECombatState::NoCharSelected)
    {
        SetSelectedPartyCharacter(PartyCharacter);
    }
    else if(PlayersCombatState == ECombatState::CharacterSelected)
    {
        if(SelectedCharacter == PartyCharacter)
            PlayersCombatState = ECombatState::AbilityPrimed;
        else
        {
            SetSelectedPartyCharacter(PartyCharacter);
        }
    }
}

void ASTPlayerController::HandleEnemyCharacter(ASTEnemyCharacter* EnemyCharacter)
{
    if(PlayersCombatState == ECombatState::AbilityPrimed)
    {
        ensure(SelectedCharacter);
        SelectedCharacter->SetTarget(EnemyCharacter);
        SelectedCharacter->ActivateAbilityByIndex(AbilityIndex);
        if(CharacterHUD != nullptr)
        {
            UpdateCharacterHUD();
        }
        PlayersCombatState = ECombatState::NoCharSelected;
        SelectedCharacter = nullptr;
    }
}
*/