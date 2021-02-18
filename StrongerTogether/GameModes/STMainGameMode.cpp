// Fill out your copyright notice in the Description page of Project Settings.


#include "STMainGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "StrongerTogether/Controllers/STPlayerController.h"
#include "StrongerTogether/Pawns/STAnchor.h"
#include "StrongerTogether/Characters/STPartyCharacter.h"

void ASTMainGameMode::BeginPlay()
{
    Super::BeginPlay();

    UGameplayStatics::GetAllActorsOfClass(GetWorld(), PathPointClass, PathPoints);
}

void ASTMainGameMode::HandleStartingNewPlayer_Implementation(APlayerController* NewPlayer)
{
    
    AActor* SpawnPoint = ChoosePlayerStart(NewPlayer);
    FVector SpawnLocation = SpawnPoint->GetActorLocation();
    FRotator SpawnRotation = SpawnPoint->GetActorRotation();
    
    FActorSpawnParameters SpawnParameters;    // TODO Set spawn parameters to spawn correctly i.e. rotation
    SpawnParameters.Owner = NewPlayer;

    Anchor = GetWorld()->SpawnActor<ASTAnchor>(DefaultPawnClass, SpawnLocation, SpawnRotation, SpawnParameters);

    if(Anchor != nullptr)
    {
        NewPlayer->Possess(Anchor);
        Anchor->SpawnPartyCharacter();
    }
        
            
            
}
