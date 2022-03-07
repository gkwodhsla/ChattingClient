// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChattingWindowWidget.generated.h"

class UScrollBox;
class UComboBoxString;
class UEditableTextBox;

UCLASS()
class CHATTINGCLIENT_API UChattingWindowWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	UScrollBox* ChattingScroll = nullptr;

	UPROPERTY(meta = (BindWidget))
	UComboBoxString* ChattingComboBox = nullptr;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* MsgBox = nullptr;
};
