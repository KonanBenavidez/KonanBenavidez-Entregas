// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "PEV2_Proyectil.generated.h"

UCLASS()
class PRUEBA_API APEV2_Proyectil : public AActor
{
    GENERATED_BODY()

public:
    APEV2_Proyectil();

    UPROPERTY(VisibleAnywhere)
    USphereComponent* ColisionSphere;

    UPROPERTY(VisibleAnywhere)
    UProjectileMovementComponent* MovimientoProyectil;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Danio = 25.f;

    UFUNCTION()
    void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, FVector NormalImpulse,
        const FHitResult& Hit);
};