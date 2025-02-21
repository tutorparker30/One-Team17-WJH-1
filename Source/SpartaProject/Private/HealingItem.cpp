#include "HealingItem.h"
#include "SpartaCharacter.h"

AHealingItem::AHealingItem()
{
    HealAmount = 20.0f;
    ItemType = "Healing";
}

void AHealingItem::ActivateItem(AActor* Activator)
{
    Super::ActivateItem(Activator);

    if (Activator && Activator->ActorHasTag("Player"))
    {
        if (ASpartaCharacter* PlayerCharacter = Cast<ASpartaCharacter>(Activator))
        {
            PlayerCharacter->AddHealth(HealAmount);
            PlayerCharacter->ApplySpeedDebuff(5.0f, 0.5f);
        }

        DestroyItem();
    }
}