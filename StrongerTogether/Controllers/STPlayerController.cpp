// Fill out your copyright notice in the Description page of Project Settings.


#include "STPlayerController.h"

#include "Blueprint/UserWidget.h"

#include "Kismet/GameplayStatics.h"

#include "StrongerTogether/GameModes/STMainGameMode.h"
#include "StrongerTogether/Pawns/STAnchor.h"

void ASTPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();
    InputComponent->BindAction("Advance", IE_Pressed, this, &ASTPlayerController::AdvanceCharacters);
    InputComponent->BindAction("SelectCharacter", IE_Pressed, this, &ASTPlayerController::SelectCharacter);
}

void ASTPlayerController::BeginPlay()
{
    CharacterHUD = CreateWidget<UUserWidget>(this, CharacterHUDClass);
    CharacterHUD->AddToViewport();
    bShowMouseCursor = true;
}

void ASTPlayerController::AdvanceCharacters()
{
    UE_LOG(LogTemp, Warning, TEXT("Advancing"));
    FVector NextLocation;

    if(ASTMainGameMode* GameMode = Cast<ASTMainGameMode>(GetWorld()->GetAuthGameMode()))
    {
        if(Counter > GameMode->PathPoints.Num() - 1 ) return;
        NextLocation = GameMode->PathPoints[Counter]->GetActorLocation();
    }

    if(ASTAnchor* Anchor = Cast<ASTAnchor>(GetPawn()))
    {
        Anchor->Advance(NextLocation);
    }
    
    Counter++;
}

void ASTPlayerController::SelectCharacter()
{
    
    FVector WorldLocation, WorldDirection;
    DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

    FVector StartLocation = PlayerCameraManager->GetCameraLocation();
    FVector EndLocation = (StartLocation + (WorldDirection * 1000));
    
    TArray<AActor*> ActorsToIgnore;
    //ActorsToIgnore.Add(GetPawn());

    FHitResult HitResult;

    bool bHit = UKismetSystemLibrary::LineTraceSingle(this, StartLocation, EndLocation, UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel18),
        false, ActorsToIgnore, EDrawDebugTrace::ForDuration, HitResult, true, FLinearColor::White,
        FLinearColor::Yellow, 5.0f);
    UE_LOG(LogTemp, Warning, TEXT("%s"), bHit ? TEXT("true") : TEXT("false"));
    if(bHit)
    {
        SelectedActor = HitResult.GetActor();
        if(CharacterHUD != nullptr)
        {
            UpdateCharacterHUD();
        }
    }
}
