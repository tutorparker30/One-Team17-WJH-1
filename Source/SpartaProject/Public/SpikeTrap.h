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

	// Ʈ�� Ȱ��ȭ: ������ũ�� õõ�� �ö������ ����
	UFUNCTION(BlueprintCallable, Category = "Trap")
	void ActivateTrap();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

private:
	// Tick���� ������ũ�� ��ġ ������Ʈ
	void UpdateSpike(float DeltaTime);

	// ������ũ �޽� ������Ʈ (��Ʈ ������Ʈ)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Trap", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SpikeMesh;

	// ������ũ�� �ö�� ���̿� �ɸ��� �ð�
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap", meta = (AllowPrivateAccess = "true"))
	float RiseHeight;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap", meta = (AllowPrivateAccess = "true"))
	float RiseDuration;

	// Ȱ��ȭ ���� �� ��� �ð�
	bool bIsActivating;
	float CurrentTime;

	// �����Ϳ� ��ġ�� ������ũ�� �ʱ� ��� ��ġ
	FVector DefaultRelativeLocation;
};