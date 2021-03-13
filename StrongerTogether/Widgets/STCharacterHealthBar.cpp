#include "STCharacterHealthBar.h"

void USTCharacterHealthBar::SetOwningActor(AActor* NewOwner)
{
	if (OwningActor == NewOwner)
	{
		// Skip repeated calls
		return;
	}

	OwningActor = NewOwner;

	OnOwningActorChanged.Broadcast(NewOwner);
}