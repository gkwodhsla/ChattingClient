// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WarningMsgWidget.generated.h"

class UTextBlock;
class UWidgetAnimation;
UCLASS()
class CHATTINGCLIENT_API UWarningMsgWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Msg = nullptr;
	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* FadeOut = nullptr;
};
