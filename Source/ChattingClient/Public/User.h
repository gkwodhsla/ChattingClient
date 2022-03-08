// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "User.generated.h"

class ULoginWidget;
class USocketComponent;

UCLASS()
class CHATTINGCLIENT_API AUser : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AUser();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION()
	void LoginButtonClickedCallback();

private:
	void AddLobbyCallbackFunction();

public:
	UPROPERTY()
	TSubclassOf<UUserWidget> LoginWidgetClass;
	UPROPERTY()
	UUserWidget* LoginWidget = nullptr;
	UPROPERTY()
	TSubclassOf<UUserWidget> LobbyWidgetClass;
	UPROPERTY()
	UUserWidget* LobbyWidget = nullptr;
	UPROPERTY()
	USocketComponent* SockComp = nullptr;
};
