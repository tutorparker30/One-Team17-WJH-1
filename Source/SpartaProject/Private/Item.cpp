#include "Item.h"

AItem::AItem()
{

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);


	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));

	StaticMeshComp->SetupAttachment(SceneRoot);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Shapes/Shape_Cube.Shape_Cube"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}


	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Resources/Materials/M_Power_Sphere.M_Power_Sphere"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
	}

	PrimaryActorTick.bCanEverTick = true;
	RotationSpeed = 90.0f;
}
void AItem::BeginPlay()
{
	Super::BeginPlay();

	OnItemPickedUp();
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	if (!FMath::IsNearlyZero(RotationSpeed))
	{
		AddActorLocalRotation(FRotator(0.0f, RotationSpeed * DeltaTime, 0.0f));
	}

	FVector NewLocation = GetActorLocation();
	NewLocation.Z += SpeedZ * DeltaTime; 
	SetActorLocation(NewLocation);

	
	TimeElapsed += DeltaTime;
	float ScaleFactor = 1.5f + 0.5f * FMath::Sin(TimeElapsed * PI); 
	SetActorScale3D(FVector(ScaleFactor));
}

void AItem::ResetActorPosition()
{
	
	SetActorLocation(FVector::ZeroVector);
}

float AItem::GetRotationSpeed() const
{
	return RotationSpeed;
}
