// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InterfazInteractuar.generated.h"

UINTERFACE()
class UInterfazInteractuar : public UInterface
{
	GENERATED_BODY()
};

class TP1OBLIGATORIO_API IInterfazInteractuar
{
	GENERATED_BODY()

public:
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ActivarCurar(AActor* Solicitante);
};
