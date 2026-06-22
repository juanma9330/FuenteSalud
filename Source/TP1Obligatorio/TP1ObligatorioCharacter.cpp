// Copyright Epic Games, Inc. All Rights Reserved.

#include "TP1ObligatorioCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "TP1Obligatorio.h"
#include "Public/Componentes/Salud.h"
#include "Interface/InterfazInteractuar.h"
#include "Blueprint/UserWidget.h"



void ATP1ObligatorioCharacter::Client_MensajeCurado_Implementation()
{
	BP_MostrarUICurado();
}

void ATP1ObligatorioCharacter::Server_IntentarInteractuar_Implementation(AActor* ObjetoAInteractuar)
{
	if (ObjetoAInteractuar && ObjetoAInteractuar->Implements<UInterfazInteractuar>())
	{
		IInterfazInteractuar::Execute_ActivarCurar(ObjetoAInteractuar, this);
	}
}

ATP1ObligatorioCharacter::ATP1ObligatorioCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	Salud = CreateDefaultSubobject<USalud>("Salud");
}

void ATP1ObligatorioCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocallyControlled())
	{
		CrearHUD();

		if (Salud)
		{
			Salud->SaludCambio.AddDynamic(this, &ATP1ObligatorioCharacter::OnSaludCambio);
		}
	}
}



void ATP1ObligatorioCharacter::CrearHUD()
{
	if (!ClaseHUDSalud) return; 

	WidgetHUDSalud = CreateWidget<UUserWidget>(GetWorld(), ClaseHUDSalud);
	if (WidgetHUDSalud)
	{
		WidgetHUDSalud->AddToViewport();
	}
}


void ATP1ObligatorioCharacter::OnSaludCambio(int NuevaSalud)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(1,3.f, FColor::White,FString::Printf(TEXT("HP: %d / %d"),Salud->GetCurrentHealth(),Salud->GetMaxHealth()));
	}
}


void ATP1ObligatorioCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EIC->BindAction(JumpAction,      ETriggerEvent::Started,   this, &ACharacter::Jump);
		EIC->BindAction(JumpAction,      ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EIC->BindAction(MoveAction,      ETriggerEvent::Triggered, this, &ATP1ObligatorioCharacter::Move);
		EIC->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &ATP1ObligatorioCharacter::Look);
		EIC->BindAction(LookAction,      ETriggerEvent::Triggered, this, &ATP1ObligatorioCharacter::Look);
		EIC->BindAction(Interactuar,     ETriggerEvent::Started,   this, &ATP1ObligatorioCharacter::DoInteract);
	}
	else
	{
		UE_LOG(LogTP1Obligatorio, Error,
			TEXT("'%s' no encontró Enhanced Input Component."), *GetNameSafe(this));
	}
}

void ATP1ObligatorioCharacter::Move(const FInputActionValue& Value)
{
	DoMove(Value.Get<FVector2D>().X, Value.Get<FVector2D>().Y);
}

void ATP1ObligatorioCharacter::Look(const FInputActionValue& Value)
{
	DoLook(Value.Get<FVector2D>().X, Value.Get<FVector2D>().Y);
}

void ATP1ObligatorioCharacter::DoMove(float Right, float Forward)
{
	if (!GetController()) return;
	const FRotator YawRotation(0, GetController()->GetControlRotation().Yaw, 0);
	AddMovementInput(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X), Forward);
	AddMovementInput(FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y), Right);
}

void ATP1ObligatorioCharacter::DoLook(float Yaw, float Pitch)
{
	if (!GetController()) return;
	AddControllerYawInput(Yaw);
	AddControllerPitchInput(Pitch);
}

void ATP1ObligatorioCharacter::DoJumpStart()  { Jump(); }
void ATP1ObligatorioCharacter::DoJumpEnd()    { StopJumping(); }

void ATP1ObligatorioCharacter::DoInteract()
{
	if (!ShrineEnRango) return;

	Server_IntentarInteractuar(ShrineEnRango);
}
