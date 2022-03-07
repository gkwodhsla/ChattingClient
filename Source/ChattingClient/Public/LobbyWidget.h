// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyWidget.generated.h"

class UButton;
class UWidgetSwitcher;
class UUserListWidget;
class UCreateRoomWindowWidget;
class USendMailWindowWidget;

UCLASS()
class CHATTINGCLIENT_API ULobbyWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	UWidgetSwitcher* LobbyWidgetSwitcher = nullptr;
	UPROPERTY(meta = (BindWidget))
	UUserListWidget* UserListScroll = nullptr;
	UPROPERTY(meta = (BindWidget))
	UUserListWidget* RoomListScroll = nullptr;
	UPROPERTY(meta = (BindWidget))
	UCreateRoomWindowWidget* CreateRoomWindow = nullptr;
	UPROPERTY(meta = (BindWidget))
	USendMailWindowWidget* SendMailWindow = nullptr;
};
