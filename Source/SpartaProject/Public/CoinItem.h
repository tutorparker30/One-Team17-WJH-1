#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "CoinItem.generated.h"

UCLASS()
class SPARTAPROJECT_API ACoinItem : public ABaseItem
{
	GENERATED_BODY()

public:
	ACoinItem();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void ActivateItem(AActor* Activator) override;

public:
	
	void SetWave3OrbitActive(bool bActive);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin")
	float SpinSpeed;

	
	bool bOrbitMode;

	FVector OriginalSpawnLocation;

	
	float OrbitAngle;


	float OrbitRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin")
	int32 PointValue;

private:
	void UpdateSpin(float DeltaTime);

	void UpdateOrbit(float DeltaTime);
};
