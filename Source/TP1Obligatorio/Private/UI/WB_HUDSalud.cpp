// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/UI/WB_HUDSalud.h"
#include "Public/Componentes/Salud.h"
#include "TP1ObligatorioCharacter.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

void UWB_HUDSalud::NativeConstruct()
{
	Super::NativeConstruct();
	InicializarConPersonaje();
}

void UWB_HUDSalud::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (!bInicializado)
	{
		InicializarConPersonaje();
	}
}

void UWB_HUDSalud::InicializarConPersonaje()
{
	APawn* Pawn = GetOwningPlayerPawn();
	if (!Pawn) return;

	ATP1ObligatorioCharacter* Personaje = Cast<ATP1ObligatorioCharacter>(Pawn);
	if (!Personaje) return;

	ComponenteSalud = Personaje->GetComponenteSalud();
	if (!ComponenteSalud) return;

	ComponenteSalud->SaludCambio.AddDynamic(this, &UWB_HUDSalud::OnSaludCambio);

	ActualizarUI();
	bInicializado = true;
}

void UWB_HUDSalud::OnSaludCambio(int )
{
	ActualizarUI();
}

void UWB_HUDSalud::ActualizarUI()
{
	if (!ComponenteSalud) return;

	int VidaActual = ComponenteSalud->GetCurrentHealth();
	int VidaMax    = ComponenteSalud->GetMaxHealth();

	if (TextVidaActual)
	{
		TextVidaActual->SetText(FText::AsNumber(VidaActual));
	}

	if (TextVidaMaxima)
	{
		TextVidaMaxima->SetText(FText::AsNumber(VidaMax));
	}

	if (BarraSalud && VidaMax > 0)
	{
		BarraSalud->SetPercent(static_cast<float>(VidaActual) / static_cast<float>(VidaMax));
	}
}
