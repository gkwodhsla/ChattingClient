// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SendMailWindowWidget.generated.h"

class AUser;
class UEditableTextBox;
class UButton;

const FString SEND_MAIL_REQ_COMMAND = "to ";

UCLASS()
class CHATTINGCLIENT_API USendMailWindowWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct()override;

	UFUNCTION()
	void SendButtonClickedCallback();

	void ChangeSendMailMode();
	void ChangeInviteMode();

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
