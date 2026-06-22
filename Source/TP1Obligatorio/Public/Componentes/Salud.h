// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Salud.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSaludCambio, int, CantidadCurada);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TP1OBLIGATORIO_API USalud : public UActorComponent
{
	GENERATED_BODY()

public:
	USalud();

	void Curar(int CuracionRecibida);

	UPROPERTY(BlueprintAssignable)
	FSaludCambio SaludCambio;

	UFUNCTION(BlueprintPure, Category = "Salud")
	int GetCurrentHealth() const { return CurrentHealth; }

	UFUNCTION(BlueprintPure, Category = "Salud")
	int GetMaxHealth() const { return MaxHealth; }

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	
	UPROPERTY(ReplicatedUsing = OnRep_CurrentHealth, EditAnywhere, BlueprintReadWrite,Category = "Salud", meta = (AllowPrivateAccess = true))
	int CurrentHealth = 53;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite,	Category = "Salud", meta = (AllowPrivateAccess = true))
	int MaxHealth = 100;

	UFUNCTION()
	void OnRep_CurrentHealth();
};
