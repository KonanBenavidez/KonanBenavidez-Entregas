// Fill out your copyright notice in the Description page of Project Settings.


#include "PEV2_Proyectil.h"
#include "../pruebaCharacter.h"

APEV2_Proyectil::APEV2_Proyectil()
{
    bReplicates = true;

    ColisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("ColisionSphere"));
    ColisionSphere->InitSphereRadius(15.f);
    ColisionSphere->SetCollisionProfileName(TEXT("BlockAllDynamic"));
    ColisionSphere->OnComponentHit.AddDynamic(this, &APEV2_Proyectil::OnHit);
    RootComponent = ColisionSphere;

    MovimientoProyectil = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MovimientoProyectil"));
    MovimientoProyectil->InitialSpeed = 3000.f;
    MovimientoProyectil->MaxSpeed = 3000.f;
    MovimientoProyectil->bRotationFollowsVelocity = true;
    MovimientoProyectil->bShouldBounce = false;

    InitialLifeSpan = 3.f;
}

void APEV2_Proyectil::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (!HasAuthority()) return;
    if (!OtherActor || OtherActor == this || OtherActor == GetOwner()) return;

    ApruebaCharacter* Personaje = Cast<ApruebaCharacter>(OtherActor);
    if (Personaje)
    {
        AController* InstigadorController = GetInstigatorController();
        Personaje->RecibirDanio(Danio, InstigadorController);
    }

    Destroy();
}
