#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpikeTrap.generated.h"

UCLASS()
class SPARTAPROJECT_API ASpikeTrap : public AActor
{
	GENERATED_BODY()

public:
	ASpikeTrap();

	// 트랩 활성화: 스파이크가 천천히 올라오도록 시작
	UFUNCTION(BlueprintCallable, Category = "Trap")
	void ActivateTrap();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	// Tick에서 스파이크의 위치 업데이트
	void UpdateSpike(float DeltaTime);

	// 스파이크 메시 컴포넌트 (루트 컴포넌트)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trap", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SpikeMesh;

	// 스파이크가 올라올 높이와 걸리는 시간
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap", meta = (AllowPrivateAccess = "true"))
	float RiseHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap", meta = (AllowPrivateAccess = "true"))
	float RiseDuration;

	// 활성화 상태 및 경과 시간
	bool bIsActivating;
	float CurrentTime;

	// 에디터에 배치된 스파이크의 초기 상대 위치
	FVector DefaultRelativeLocation;
};