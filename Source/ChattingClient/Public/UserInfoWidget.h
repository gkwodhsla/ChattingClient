// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserInfoWidget.generated.h"

class UButton;
class UTextBlock;

class AUser;

UCLASS()
class CHATTINGCLIENT_API UUserInfoWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct()override;
	UFUNCTION()
	void SpecificInfoButtonClickedCallback();

public:
	UPROPERTY(meta = (BindWidget))
	UButton* SpecificInfoButton = nullptr;
	UPROPERTY(meta = (BindWidget))
	UTextBlock* UserInfoText = nullptr;
	AUser* User;

};
