// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoginWidget.generated.h"

const FString LOGIN_REQ_COMMAND = "login ";

class AUser;
class UEditableTextBox;
class UButton;
class UWarningMsgWidget;

UCLASS()
class CHATTINGCLIENT_API ULoginWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	void NativeConstruct()override;

protected:
	UFUNCTION()
	void LoginButtonClickedCallback();
	UFUNCTION()
	void AnimationFinishedCallback();

public:
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* LoginTextBox = nullptr;

	UPROPERTY(meta = (BindWidget))
	UButton* LoginButton = nullptr;
	
	UPROPERTY(meta = (BindWidget))
	UWarningMsgWidget* WarningMsg = nullptr;
	
	UPROPERTY()
	AUser* User;

private:
	FWidgetAnimationDynamicEvent EndDelegate;
};
