// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPSWeapon.h"
#include "FPSProjectileWeapon.generated.h"

/**
 * 
 */
UCLASS()
class FPSGAME_API AFPSProjectileWeapon : public AFPSWeapon
{
	GENERATED_BODY()

protected:
	virtual void Fire() override;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile Weapon")
	TSubclassOf<AActor> ProjectileClass;
	
};
