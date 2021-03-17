// Fill out your copyright notice in the Description page of Project Settings.


#include "STMainGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "StrongerTogether/Pawns/STPlayerAnchor.h"
#include "StrongerTogether/Characters/STPartyCharacter.h"
#include "StrongerTogether/GameStates/STMainGameState.h"

ASTMainGameMode::ASTMainGameMode()
{
    GameStateClass = ASTMainGameState::StaticClass();
}

void ASTMainGameMode::BeginPlay()
{
    Super::BeginPlay();

    UGameplayStatics::GetAllActorsOfClass(GetWorld(), PathPointClass, PathPoints);
}

void ASTMainGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
    Super::InitGame(MapName, Options, ErrorMessage);
}

void ASTMainGameMode::InitGameState()
{
    Super::InitGameState();
    if(ASTMainGameState* MainGameState = Cast<ASTMainGameState>(GameState))
    {
        MainGameState->Init();
    }
}

void ASTMainGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
    
    AActor* SpawnPoint = ChoosePlayerStart(NewPlayer);
    const FVector SpawnLocation = SpawnPoint->GetActorLocation();
    const FRotator SpawnRotation = SpawnPoint->GetActorRotation();
    
    FActorSpawnParameters SpawnParameters;    // TODO Set spawn parameters to spawn correctly i.e. rotation
    SpawnParameters.Owner = NewPlayer;

    Anchor = GetWorld()->SpawnActor<ASTPlayerAnchor>(DefaultPawnClass, SpawnLocation, SpawnRotation, SpawnParameters);

    if(Anchor != nullptr)
    {
        NewPlayer->Possess(Anchor);
        
        if(ASTMainGameState* MainGameState = Cast<ASTMainGameState>(GameState))
        {
            MainGameState->ReceivePlayerAnchor(Anchor);
        }
    }

        
            
            
}
