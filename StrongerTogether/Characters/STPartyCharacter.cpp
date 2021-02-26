// Fill out your copyright notice in the Description page of Project Settings.


#include "STPartyCharacter.h"

#include "StrongerTogether/Pawns/STAnchor.h"


// Sets default values
ASTPartyCharacter::ASTPartyCharacter()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}


void ASTPartyCharacter::SetOwningAnchor(ASTAnchor* InAnchor)
{
	if(InAnchor != nullptr)
	{
		OwningAnchor = InAnchor;
		OwningAnchor->AnchorMoving.AddDynamic(this, &ASTPartyCharacter::StartMoving);
		OwningAnchor->AnchorStopping.AddDynamic(this, &ASTPartyCharacter::StopMoving);
	}
}