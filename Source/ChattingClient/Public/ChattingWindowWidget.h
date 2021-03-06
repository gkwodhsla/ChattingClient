// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <string>
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChattingWindowWidget.generated.h"
class AUser;
class UScrollBox;
class UEditableTextBox;
class UButton;
class UTextBlock;

const FString QUIT_REQ_COMMAND = "/q";

UCLASS()
class CHATTINGCLIENT_API UChattingWindowWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void NativeConstruct() override;
	void AddNewChatting(const std::string& Chatting);
	void EraseAllChatting();

public:
	UFUNCTION()
	void QuitButtonClickedCallback();
	
	UFUNCTION()
	void TextCommitedCallback(const FText& InText, ETextCommit::Type InCommitType);

public:
	UPROPERTY(meta = (BindWidget))
	UScrollBox* ChattingScroll = nullptr;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* MsgBox = nullptr;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton = nullptr;

	UPROPERTY()
	AUser* User = nullptr;

	TArray<UUserWidget*> Chattings;
};
