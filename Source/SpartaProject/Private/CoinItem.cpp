
#include "CoinItem.h"
#include "SpartaGameState.h"
#include "Engine/World.h"
#include "BaseItem.h"

ACoinItem::ACoinItem()
	: SpinSpeed(180.f)
	, bOrbitMode(false)
	, OrbitAngle(0.f)
	, OrbitRadius(100.f)
	, PointValue(10)
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACoinItem::BeginPlay()
{
	Super::BeginPlay();

	OriginalSpawnLocation = GetActorLocation();
}

void ACoinItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateSpin(DeltaTime);

	if (bOrbitMode)
	{
		UpdateOrbit(DeltaTime);
	}
}

void ACoinItem::UpdateSpin(float DeltaTime)
{
	
	AddActorLocalRotation(FRotator(0.f, SpinSpeed * DeltaTime, 0.f));
}

void ACoinItem::UpdateOrbit(float DeltaTime)
{

	const float OrbitSpeed = 100.f;
	OrbitAngle += OrbitSpeed * DeltaTime;

	const float Radians = FMath::DegreesToRadians(OrbitAngle);

	FVector NewPosition = OriginalSpawnLocation;
	NewPosition.X += OrbitRadius * FMath::Cos(Radians);
	NewPosition.Y += OrbitRadius * FMath::Sin(Radians);

	SetActorLocation(NewPosition);
}

void ACoinItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);

	if (Activator && Activator->ActorHasTag("Player"))
	{
		if (UWorld* World = GetWorld())
		{
			if (ASpartaGameState* GameState = World->GetGameState<ASpartaGameState>())
			{
				GameState->AddScore(PointValue);
				GameState->OnCoinCollected();
			}
		}
		DestroyItem();
	}
}

void ACoinItem::SetWave3OrbitActive(bool bActive)
{
	bOrbitMode = bActive;
}
