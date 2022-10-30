// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Projectile.h"


ATank::ATank()
{
    //Components Setup

    SetReplicates(true);
    
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);

    ProjectileSpawnPointA = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn PointA"));
    ProjectileSpawnPointA->SetupAttachment(TurretMesh);

    ProjectileSpawnPointB = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn PointB"));
    ProjectileSpawnPointB->SetupAttachment(TurretMesh);

}

void ATank::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) 
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    
    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
    PlayerInputComponent->BindAction(TEXT("Pause"),IE_Pressed, this, &ATank::Pause);
    //PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

void ATank::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);

    if (TankPlayerController)
    {
        FHitResult HitResult;
        TankPlayerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, false, HitResult);

        //Call Function on BasePawn
        RotateTurret(HitResult.ImpactPoint);
        
        //DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 25.f, 12, FColor::Red, false, -1.f);
    }

}

//void ATank::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)
//{
//    Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//}

void ATank::HandleDestrucion() 
{
    Super::HandleDestruction();
    SetActorHiddenInGame(true);
}

float ATank::GetHealthPercent() const
{
    return Health / MaxHealth;
}

void ATank::AddSkill() 
{

}

void ATank::BeginPlay() 
{
    Super::BeginPlay();

    TankPlayerController = Cast<APlayerController>(GetController());

    PowerUpFireActive = false;

    PowerUpFireRateActive = false;

    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATank::Fire, FireRate, true, 3.f); //Inital timer with start delay.

}

void ATank::Fire() 
{

    Super::Fire();
    
    if (IsHidden())
    {
        //don't shoot.
    }
    else
    {
        if (PowerUpFireRateActive) //Check if firerate power up is active and set new timer loop true
        {
            FireRate = 0.3;

            GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATank::Fire, FireRate, true);
        }

        else if (!PowerUpFireRateActive) //if not set new timer with normal fire rate, loop false
        {
            FireRate = 0.6;

            GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATank::Fire, FireRate, false);
        }

        if (PowerUpFireActive)  //Check if TripleShot power up is active and spawn projectiles
        {
            FVector LocationA = ProjectileSpawnPointA->GetComponentLocation();
	        FRotator RotationA = ProjectileSpawnPointA->GetComponentRotation();

	        auto ProjectileA = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, LocationA, RotationA);
	        ProjectileA->SetOwner(this);

            FVector LocationB = ProjectileSpawnPointB->GetComponentLocation();
	        FRotator RotationB = ProjectileSpawnPointB->GetComponentRotation();

	        auto ProjectileB = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, LocationB, RotationB);
	        ProjectileB->SetOwner(this);
        }
    }
}

void ATank::Move(float Value) 
{
    FVector DeltaLocation = FVector::ZeroVector;
    DeltaLocation.X = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalOffset(DeltaLocation, true);
}

void ATank::Turn(float Value) 
{
    FRotator DeltaRotation = FRotator::ZeroRotator;
    DeltaRotation.Yaw = Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this);
    AddActorLocalRotation(DeltaRotation, true);
}

void ATank::Pause() 
{   
    if (bPaused)
    {
        TankPlayerController->SetPause(false);
        bPaused = false;
    }
    else
    {   TankPlayerController->SetPause(true);
        bPaused = true;
        OnPause();
    }
}


    
