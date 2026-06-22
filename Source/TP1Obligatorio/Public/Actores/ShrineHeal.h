// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "Interface/InterfazInteractuar.h"
#include "ShrineHeal.generated.h"

class USalud;
class UStaticMeshComponent;
class UNiagaraSystem;
class UNiagaraComponent;

UCLASS()
class TP1OBLIGATORIO_API AShrineHeal : public AActor, public IInterfazInteractuar
{
	GENERATED_BODY()

private:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fuente Curacion", meta=(AllowPrivateAccess="true"))
	TObjectPtr<UStaticMeshComponent> ItemMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fuente Curacion", meta=(AllowPrivateAccess="true"))
	TObjectPtr<USphereComponent> RangoInteraccion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fuente Curacion", meta=(AllowPrivateAccess="true"))
	int CantidadCura = 30;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fuente Curacion", meta=(AllowPrivateAccess="true"))
	float TiempoCooldown = 10.0f;

	UPROPERTY(ReplicatedUsing = OnRep_Disponible)
	bool bDisponible = true;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fuente Curacion")
	FLinearColor AvailableColor = FLinearColor(0.f, 1.f, 0.f);
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fuente Curacion")
	FLinearColor CooldownColor = FLinearColor(1.f, 0.f, 0.f);
	
	UPROPERTY()
	TObjectPtr<AActor> ActorEnRango;

	FTimerHandle TimerCooldownHandle;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX")
	TObjectPtr<USoundBase> ActivateSound;
 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX")
	TObjectPtr<UNiagaraSystem> ActivateParticles;

	AShrineHeal();

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;
	virtual void ActivarCurar_Implementation(AActor* Solicitante) override;

private:


	UFUNCTION(NetMulticast, Reliable)
	void Multicast_EfectoActivacion();
	
	void ActualizarColorSphere();
	
	UFUNCTION()
	void OnRep_Disponible();

	void FinCooldown();
};
