// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyWidget.generated.h"

class UChattingWindowWidget;
class UUserListWidget;

UCLASS()
class CHATTINGCLIENT_API ULobbyWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UChattingWindowWidget* ChattingWindow = nullptr;

	UPROPERTY(meta = (BindWidget))
	UUserListWidget* UserListWindow = nullptr;
};
