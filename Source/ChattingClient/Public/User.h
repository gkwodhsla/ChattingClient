// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <vector>
#include <string>
#include "User.generated.h"

class ULoginWidget;
class USocketComponent;
class UUserInfoWidget;
class UUserSpecificInfoWindowWidget;
class URoomInfoWidget;

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
	void SendMsg(const FString& Msg);
	
	void CallLobbyWidgetUserInfo(const std::vector<std::string>& UserList);
	void CallLobbyWidgetRoomInfo(const std::vector<std::string>& UserList);
	void CallLobbyWidgetUserSpecificInfo(const std::vector<std::string>& RoomList);
	void CallLobbyWidgetRoomSpecificInfo(const std::vector<std::string>& RoomList);

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
	UPROPERTY()
	TSubclassOf<UUserInfoWidget> UserInfoWidgetClass;
	UPROPERTY()
	TSubclassOf<UUserSpecificInfoWindowWidget> UserSpecificInfoWindowWidgetClass;
	UPROPERTY()
	TSubclassOf<URoomInfoWidget> RoomInfoWidgetClass;
};