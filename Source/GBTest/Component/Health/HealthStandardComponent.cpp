// Fill out your copyright notice in the Description page of Project Settings.


#include "./HealthStandardComponent.h"

void UHealthStandardComponent::Initialize(FHealthComponentInitializer& initializer) {
    Super::Initialize(initializer);
    CurrentHealth = initializer.MaxHealth;
}

float UHealthStandardComponent::GetHealth() {
    return CurrentHealth;
}

void UHealthStandardComponent::TakeDamage(AGameCharacter* otherCharacter, ETypeDamage typeDamage, float power) {
    if ((CurrentHealth -= power) <= 0) {
        Death();
    }
}
