// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UserListWidget.generated.h"

class UScrollBox;
class UEditableTextBox;

UCLASS()
class CHATTINGCLIENT_API UUserListWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	UScrollBox* UserScrollBox = nullptr;
};
