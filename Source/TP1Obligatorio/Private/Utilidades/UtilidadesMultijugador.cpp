// Fill out your copyright notice in the Description page of Project Settings.


#include "Utilidades/UtilidadesMultijugador.h"

void UUtilidadesMultijugador::MostrarRol(AActor* Actor,FString& Rol)
{
	if (Actor ->HasAuthority())
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Emerald,TEXT("TIENE AUTORIDAD"));
		}
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1,5.0f,FColor::Emerald,TEXT("NO TIENE AUTORIDAD"));

	}
	switch ( Actor-> GetLocalRole())
	{
	case ROLE_None:
		Rol = TEXT("No tiene rol");
		break;
	case ROLE_SimulatedProxy:
		Rol = TEXT("SimulatedProxy");
		break;
	case ROLE_AutonomousProxy:
		Rol = TEXT("AutonomousProxy");
		break;
	case ROLE_Authority:
		Rol = TEXT("Authority");
		break;
	case ROLE_MAX:
		break;
	}
}
