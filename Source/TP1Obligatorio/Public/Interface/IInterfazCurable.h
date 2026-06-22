// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IInterfazCurable.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UIInterfazCurable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TP1OBLIGATORIO_API IIInterfazCurable
{
	GENERATED_BODY()

public:

	virtual void RecibirCuracion(int CantidadCuracion) = 0;

};
