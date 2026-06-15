// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UCLASS()
class PRUEBA_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Props")
	int salud;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Props")
	int Armadura;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0.0", ClampMax = "2500", UIMin = "0.0",
		UIMax = "2500", ToolTip = "Salud del jugador"))
	int Distancia;

	UPROPERTY(EditAnywhere)
	FString MiNombre;


	UFUNCTION()
	void MostrarMensaje();

   



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
									

	

};
