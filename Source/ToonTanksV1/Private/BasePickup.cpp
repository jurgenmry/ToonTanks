// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePickup.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"


// Sets default values
ABasePickup::ABasePickup()
{
	SphereRadius = 100.0f;
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SphereComp->InitSphereRadius(SphereRadius);
	SphereComp->SetCollisionProfileName("Trigger");
	RootComponent = SphereComp;
	
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(SphereComp);

	ParticleIdle = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Particle System"));
	ParticleIdle->SetupAttachment(SphereComp);

	//ParticlePicked = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Particle System"));
	//ParticlePicked->SetupAttachment(SphereComp);
	
	SphereComp->OnComponentBeginOverlap.AddDynamic(this, &ABasePickup::OnComponentBeginOverlap);

}

// Called when the game starts or when spawned
void ABasePickup::BeginPlay()
{
	Super::BeginPlay();

	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));

}

void ABasePickup::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) 
{
	if (OtherActor != nullptr && OtherActor != this && OtherComp != nullptr && OtherActor == Tank)
	{
		if (Tank)
		{
			PickedUp();
		}	
	}
}

