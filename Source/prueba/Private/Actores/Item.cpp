// Fill out your copyright notice in the Description page of Project Settings.


#include "Actores/Item.h"

// Sets default values
AItem::AItem()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MiNombre = TEXT("Actor");
}

void AItem::MostrarMensaje()
{
	if (GEngine) // GEngine si existe muestro mensaje
	{
		GEngine->AddOnScreenDebugMessage(
			-1,//Esto es el key
			5.0f,// esto es el tiempo que va permanecer
			FColor::Magenta, // esto es el color
			MiNombre) // y esto es el mensaje a mostrar en pantalla
			;
	}
}

// Called when the game starts or when spawned
void AItem::BeginPlay()
{
	Super::BeginPlay();
	MostrarMensaje();

}

// Called every frame
void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


}

