#include "SpikeTrap.h"
#include "Components/StaticMeshComponent.h"

ASpikeTrap::ASpikeTrap()
	: RiseHeight(50.f)
	, RiseDuration(1.f)
	, bIsActivating(false)
	, CurrentTime(0.f)
{
	PrimaryActorTick.bCanEverTick = true;

	SpikeMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SpikeMesh"));
	SetRootComponent(SpikeMesh);
}

void ASpikeTrap::BeginPlay()
{
	Super::BeginPlay();

	// 에디터에서 배치된 위치를 초기 위치로 저장
	DefaultRelativeLocation = SpikeMesh->GetRelativeLocation();

	// 게임 시작 시, 스파이크를 아래로 내린 위치로 설정
	FVector StartLoc = DefaultRelativeLocation;
	StartLoc.Z -= RiseHeight;
	SpikeMesh->SetRelativeLocation(StartLoc);
}

void ASpikeTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsActivating)
	{
		UpdateSpike(DeltaTime);
	}
}

void ASpikeTrap::UpdateSpike(float DeltaTime)
{
	CurrentTime += DeltaTime;
	const float Alpha = FMath::Clamp(CurrentTime / RiseDuration, 0.f, 1.f);

	// Z축만 Lerp하여 스파이크를 위로 이동
	const float NewZ = FMath::Lerp(DefaultRelativeLocation.Z - RiseHeight, DefaultRelativeLocation.Z, Alpha);
	FVector CurrentLoc = SpikeMesh->GetRelativeLocation();
	CurrentLoc.Z = NewZ;
	SpikeMesh->SetRelativeLocation(CurrentLoc);

	// 이동 완료 시 활성화 종료
	if (Alpha >= 1.f)
	{
		bIsActivating = false;
	}
}

void ASpikeTrap::ActivateTrap()
{
	bIsActivating = true;
	CurrentTime = 0.f;
}

