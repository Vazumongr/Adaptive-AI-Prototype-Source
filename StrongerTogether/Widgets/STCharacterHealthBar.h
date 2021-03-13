#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STCharacterHealthBar.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnOwningActorChanged, AActor*, NewOwner);


/**
* Base class for UMG Widgets that belong to a single Actor in the world via a WidgetComponent, eg. for 3D health-bars, nameplate, interaction tooltip.
*/
UCLASS()
class STRONGERTOGETHER_API USTCharacterHealthBar : public UUserWidget
{
	GENERATED_BODY()

	protected:

	/* Actor that widget is attached to via WidgetComponent */
	UPROPERTY(BlueprintReadOnly, Category = "ActorWidget")
	AActor* OwningActor;
 
	public:

	/* Set the owning actor so widgets have access to whatever is, broadcasting OnOwningActorChanged event */
	UFUNCTION(BlueprintCallable, Category = "LODZERO|UI")
    void SetOwningActor(AActor* NewOwner);

	UPROPERTY(BlueprintAssignable, Category = "LODZERO|UI")
	FOnOwningActorChanged OnOwningActorChanged;
};