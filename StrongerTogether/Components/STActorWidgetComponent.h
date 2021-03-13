#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "STActorWidgetComponent.generated.h"

/**
* Extension of the WidgetComponent to make it easy to have owning Actor context to the Widget. Commonly used to display health bars, names, and interaction panels above Actors.
Automatically calls SetOwningActor on the widget if the correct type of widget is used (ActorAttachWidget)
*/
UCLASS(meta = (BlueprintSpawnableComponent))
class STRONGERTOGETHER_API USTActorWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()
	
	public:

	virtual void InitWidget() override;
	
	USTActorWidgetComponent();
	
};