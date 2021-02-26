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
    bShowMouseCursor = true;
    PlayersCombatState = ECombatState::NoCharSelected;
}

void ASTPlayerController::SetAbilityIndex(int32 Index)
{
    AbilityIndex = Index;
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
    SelectedActor = InActor;
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
        if(ASTPartyCharacter* PartyCharacter = Cast<ASTPartyCharacter>(HitResult.GetActor()))
            HandlePartyCharacter(PartyCharacter);
        if(ASTEnemyCharacter* EnemyCharacter = Cast<ASTEnemyCharacter>(HitResult.GetActor()))
            HandleEnemyCharacter(EnemyCharacter);
    }
    else
    {
        PlayersCombatState = ECombatState::NoCharSelected;
        SelectedActor = nullptr;
    }
}

void ASTPlayerController::HandlePartyCharacter(ASTPartyCharacter* PartyCharacter)
{
    if(PlayersCombatState == ECombatState::NoCharSelected)
    {
        SetSelectedPartyCharacter(PartyCharacter);
    }
    else if(PlayersCombatState == ECombatState::CharacterSelected)
    {
        if(SelectedActor == PartyCharacter)
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
        ensure(SelectedActor);
        SelectedActor->SetTarget(EnemyCharacter);
        SelectedActor->ActivateAbilityByIndex(AbilityIndex);
        if(CharacterHUD != nullptr)
        {
            UpdateCharacterHUD();
        }
        PlayersCombatState = ECombatState::NoCharSelected;
        SelectedActor = nullptr;
    }
}
