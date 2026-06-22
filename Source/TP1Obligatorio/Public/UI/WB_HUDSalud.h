// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WB_HUDSalud.generated.h"

class USalud;
class UTextBlock;
class UProgressBar;

UCLASS()
class TP1OBLIGATORIO_API UWB_HUDSalud : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

private:

	void InicializarConPersonaje();

	UFUNCTION()
	void OnSaludCambio(int NuevaSalud);

	UPROPERTY()
	TObjectPtr<USalud> ComponenteSalud;

	bool bInicializado = false;

protected:
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextVidaActual;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> TextVidaMaxima;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UProgressBar> BarraSalud;

	void ActualizarUI();
};
