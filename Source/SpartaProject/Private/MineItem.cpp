#include "MineItem.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "SpartaCharacter.h"  // 디버프 적용을 위해 캐릭터 헤더 include

AMineItem::AMineItem()
{
    ExplosionDelay = 5.0f;
    ExplosionRadius = 300.0f;
    ExplosionDamage = 30.0f;
    ItemType = "Mine";
    bHasExploded = false;

    ExplosionCollision = CreateDefaultSubobject<USphereComponent>(TEXT("ExplosionCollision"));
    ExplosionCollision->InitSphereRadius(ExplosionRadius);
    ExplosionCollision->SetCollisionProfileName(TEXT("OverlapAllDynamic"));
    ExplosionCollision->SetupAttachment(Scene);
}

void AMineItem::ActivateItem(AActor* Activator)
{
    if (bHasExploded) return;

    Super::ActivateItem(Activator);

    GetWorld()->GetTimerManager().SetTimer(
        ExplosionTimerHandle,
        this,
        &AMineItem::Explode,
        ExplosionDelay,
        false
    );

    bHasExploded = true;
}

void AMineItem::Explode()
{
    UParticleSystemComponent* Particle = nullptr;

    if (ExplosionParticle)
    {
        Particle = UGameplayStatics::SpawnEmitterAtLocation(
            GetWorld(),
            ExplosionParticle,
            GetActorLocation(),
            GetActorRotation(),
            false
        );
    }

    if (ExplosionSound)
    {
        UGameplayStatics::PlaySoundAtLocation(
            GetWorld(),
            ExplosionSound,
            GetActorLocation()
        );
    }

    // 1) 폭발 범위 안에 있는 액터들 전부 확인
    TArray<AActor*> OverlappingActors;
    ExplosionCollision->GetOverlappingActors(OverlappingActors);

    for (AActor* Actor : OverlappingActors)
    {
        if (Actor && Actor->ActorHasTag("Player"))
        {
            // 1-1) 데미지 주기
            UGameplayStatics::ApplyDamage(
                Actor,
                ExplosionDamage,
                nullptr,
                this,
                UDamageType::StaticClass()
            );

            // 1-2) 플레이어 캐릭터에게 '조작 반전 디버프' 5초간 부여
            if (ASpartaCharacter* PlayerCharacter = Cast<ASpartaCharacter>(Actor))
            {
                PlayerCharacter->ApplyReverseControlsDebuff(5.0f);
            }
        }
    }

    DestroyItem();

    if (Particle)
    {
        FTimerHandle DestroyParticleTimerHandle;
        TWeakObjectPtr<UParticleSystemComponent> WeakParticle = Particle;

        GetWorld()->GetTimerManager().SetTimer(
            DestroyParticleTimerHandle,
            [WeakParticle]()
            {
                if (WeakParticle.IsValid())
                {
                    WeakParticle->DestroyComponent();
                }
            },
            2.0f,
            false
        );
    }
}