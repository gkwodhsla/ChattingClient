// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SendMailWindowWidget.generated.h"

class UEditableTextBox;
class UButton;
class AUser;

UCLASS()
class CHATTINGCLIENT_API USendMailWindowWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct()override;

	UFUNCTION()
	void SendButtonClickedCallback();

public:
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* ToTextBox = nullptr;
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* MessageTextBox = nullptr;
	UPROPERTY(meta = (BindWidget))
	UButton* SendButton = nullptr;
	UPROPERTY()
	AUser* User = nullptr;
};
