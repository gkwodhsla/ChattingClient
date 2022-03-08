// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RoomInfoWidget.generated.h"

class UButton;
class UTextBlock;

class AUser;
UCLASS()
class CHATTINGCLIENT_API URoomInfoWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct()override;
	UFUNCTION()
	void SpecificInfoButtonClickedCallback();
	UFUNCTION()
	void JoinButtonClickedCallback();

public:
	UPROPERTY(meta = (BindWidget))
	UButton* SpecificInfoButton = nullptr;
	UPROPERTY(meta = (BindWidget))
	UButton* JoinButton = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* RoomInfoText = nullptr;
	AUser* User;
};
