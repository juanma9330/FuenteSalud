// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Actores/ShrineHeal.h"
#include "Public/Componentes/Salud.h"
#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TP1ObligatorioCharacter.h"
#include "Net/UnrealNetwork.h"

AShrineHeal::AShrineHeal()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>("ItemMesh");
	SetRootComponent(ItemMesh);

	RangoInteraccion = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	RangoInteraccion->SetupAttachment(ItemMesh);
	RangoInteraccion->SetSphereRadius(100.0f);
	RangoInteraccion->SetLineThickness(10.0f);
}

void AShrineHeal::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AShrineHeal, bDisponible);
}

void AShrineHeal::BeginPlay()
{
	Super::BeginPlay();
	ActualizarColorSphere();
}



void AShrineHeal::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (!OtherActor) return;

	ActorEnRango = OtherActor;

	if (ATP1ObligatorioCharacter* Personaje = Cast<ATP1ObligatorioCharacter>(OtherActor))
	{
		Personaje->SetShrineEnRango(this);
	}
}

void AShrineHeal::NotifyActorEndOverlap(AActor* OtherActor)
{
	Super::NotifyActorEndOverlap(OtherActor);
	if (ActorEnRango == OtherActor)
	{
		ActorEnRango = nullptr;
	}

	if (ATP1ObligatorioCharacter* Personaje = Cast<ATP1ObligatorioCharacter>(OtherActor))
	{
		Personaje->SetShrineEnRango(nullptr);
	}
}



void AShrineHeal::ActivarCurar_Implementation(AActor* Solicitante)
{
	if (!HasAuthority()) return;
	if (!bDisponible) return;
	if (!Solicitante)return;
	if (!RangoInteraccion->IsOverlappingActor(Solicitante))return;

	USalud* ComponenteSalud = Solicitante->FindComponentByClass<USalud>();
	if (!ComponenteSalud) return;

	int SaludAntes   = ComponenteSalud->GetCurrentHealth();
	ComponenteSalud->Curar(CantidadCura);
	int CuracionReal = ComponenteSalud->GetCurrentHealth() - SaludAntes;

	bDisponible = false;
	OnRep_Disponible(); 

	Multicast_EfectoActivacion();
	if (ATP1ObligatorioCharacter* Personaje = Cast<ATP1ObligatorioCharacter>(Solicitante))
	{
		Personaje->Client_MensajeCurado();
	}
	GetWorldTimerManager().SetTimer(TimerCooldownHandle, this, &AShrineHeal::FinCooldown, TiempoCooldown, false);
}


void AShrineHeal::Multicast_EfectoActivacion_Implementation()
{
	if (ActivateParticles)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),ActivateParticles,GetActorLocation(),GetActorRotation());
	}

	if (ActivateSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this,ActivateSound,GetActorLocation());
	}
}


void AShrineHeal::OnRep_Disponible()
{
	ActualizarColorSphere();
}

void AShrineHeal::ActualizarColorSphere()
{
	RangoInteraccion->ShapeColor = bDisponible ? AvailableColor.ToFColor(true) : CooldownColor.ToFColor(true);
	RangoInteraccion->MarkRenderStateDirty();
}

void AShrineHeal::FinCooldown()
{
	bDisponible = true;
	OnRep_Disponible();
}
