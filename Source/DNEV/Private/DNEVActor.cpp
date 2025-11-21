#include "DNEVActor.h"
#include "Utils.h"
#include "DNEVMeshComponent.h"
#include "DNEVPrivatePCH.h"

// Sets default values
ADNEVActor::ADNEVActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.bCanEverTick = true;

	DNEVMeshComponent = CreateDefaultSubobject<UDNEVMeshComponent>(TEXT("DNEVMeshComponent"));
	DNEVMeshComponent->Mobility = EComponentMobility::Movable;

	AddOwnedComponent(DNEVMeshComponent);
	SetRootComponent(DNEVMeshComponent);
}

void ADNEVActor::BeginPlay()
{
	Super::BeginPlay();
}

void ADNEVActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void ADNEVActor::BeginDestroy()
{
	Super::BeginDestroy();
}

void ADNEVActor::Destroyed()
{
	Super::Destroyed();
}

void ADNEVActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UDNEVMeshComponent* ADNEVActor::GetDNEVMeshComponent() const
{
	return DNEVMeshComponent;
}