// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Componentes/Salud.h"
#include "Net/UnrealNetwork.h"

USalud::USalud()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true); 
}

void USalud::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(USalud, CurrentHealth);
	DOREPLIFETIME(USalud, MaxHealth);
}

void USalud::Curar(int CuracionRecibida)
{
	int CuracionReal = FMath::Clamp(CuracionRecibida, 0, MaxHealth - CurrentHealth);
	CurrentHealth += CuracionReal;

	OnRep_CurrentHealth();
}

void USalud::BeginPlay()
{
	Super::BeginPlay();
}

void USalud::OnRep_CurrentHealth()
{
	SaludCambio.Broadcast(CurrentHealth);
}
