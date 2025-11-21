#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UObject/ObjectMacros.h"

#include "DNEVActor.generated.h"

class UDNEVMeshComponent;

/** DNEV actor, serves as a place-able actor for DNEV objects*/
UCLASS(ComponentWrapperClass, hidecategories = (Materials))
class DNEV_API ADNEVActor : public AActor
{
	GENERATED_UCLASS_BODY()

protected:
	//~ Begin AActor Interface.
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	virtual void BeginDestroy();
	virtual void Destroyed();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	/** If true, actor is ticked even if TickType==LEVELTICK_ViewportsOnly     */
	virtual bool ShouldTickIfViewportsOnly() const override { return true; }
	//~ End AActor Interface.

private:
	
	UPROPERTY(VisibleAnywhere, Category = "DNEVActor", BlueprintReadOnly, meta = (ExposeFunctionCategories = "Mesh,Rendering,Physics,DNEV", AllowPrivateAccess = "true"))
	TObjectPtr<UDNEVMeshComponent> DNEVMeshComponent;

public:

	/** Returns DNEVMeshComponent subobject **/
	UFUNCTION(BlueprintCallable, Category = "DNEVActor")
	UDNEVMeshComponent* GetDNEVMeshComponent() const;
};
