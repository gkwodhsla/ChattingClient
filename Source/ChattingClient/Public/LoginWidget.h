// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoginWidget.generated.h"

class UEditableTextBox;
class UButton;

UCLASS()
class CHATTINGCLIENT_API ULoginWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* LoginTextBox = nullptr;

	UPROPERTY(meta = (BindWidget))
	UButton* LoginButton = nullptr;

};
