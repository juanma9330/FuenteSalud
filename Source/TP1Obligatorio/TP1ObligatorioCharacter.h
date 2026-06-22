// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "TP1ObligatorioCharacter.generated.h"

class USalud;
class USpringArmComponent;
class UCameraComponent;
class UInputAction;
class UWB_HUDSalud;   
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(abstract)
class ATP1ObligatorioCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USalud> Salud;

	UPROPERTY()
	TObjectPtr<AActor> ShrineEnRango;
	
	UFUNCTION(Client, Reliable)
	void Client_MensajeCurado();

	UFUNCTION(BlueprintImplementableEvent, Category = "UI")
	void BP_MostrarUICurado();
	
	UFUNCTION(Server, Reliable, BlueprintCallable, Category = "Interaccion")
	void Server_IntentarInteractuar(AActor* ObjetoAInteractuar);

protected:
	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* JumpAction;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* MouseLookAction;

	UPROPERTY(EditAnywhere, Category="Input")
	UInputAction* Interactuar;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
	TSubclassOf<UUserWidget> ClaseHUDSalud;

	UPROPERTY()
	TObjectPtr<UUserWidget> WidgetHUDSalud;

public:
	ATP1ObligatorioCharacter();

	virtual void BeginPlay() override;

	void SetShrineEnRango(AActor* Shrine) { ShrineEnRango = Shrine; }

	UFUNCTION(BlueprintPure, Category="Salud")
	USalud* GetComponenteSalud() const { return Salud; }

private:
	UFUNCTION()
	void OnSaludCambio(int NuevaSalud);

	void CrearHUD();

protected:
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

public:
	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoMove(float Right, float Forward);

	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoLook(float Yaw, float Pitch);

	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpStart();

	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoJumpEnd();

	UFUNCTION(BlueprintCallable, Category="Input")
	virtual void DoInteract();

public:
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }
};
