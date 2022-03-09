// Fill out your copyright notice in the Description page of Project Settings.


#include "ChattingWindowWidget.h"
#include "User.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "MsgWidget.h"
#include "Kismet/GameplayStatics.h"

void UChattingWindowWidget::NativeConstruct()
{
	Chattings.Reserve(100);

	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUser::StaticClass(), actors);
	User = Cast<AUser>(actors[0]);

	QuitButton->OnClicked.AddUniqueDynamic(this, &UChattingWindowWidget::QuitButtonClickedCallback);
	MsgBox->OnTextCommitted.AddDynamic(this, &UChattingWindowWidget::TextCommitedCallback);
}

void UChattingWindowWidget::AddNewChatting(const std::string& Chatting)
{
	auto newWidget = CreateWidget(GetWorld(), User->MsgWidgetClass);

	auto newTextBlock = Cast<UMsgWidget>(newWidget);
	if (newTextBlock)
	{
		FString temp(Chatting.c_str());
		newTextBlock->Msg->SetText(FText::FromString(temp));
		ChattingScroll->AddChild(newTextBlock);
		Chattings.Add(newTextBlock);
	}
}

void UChattingWindowWidget::TextCommitedCallback(const FText& InText, ETextCommit::Type InCommitType)
{
	if (InCommitType == ETextCommit::OnEnter && InText.ToString() != "")
	{
		User->SendMsg(InText.ToString());
		MsgBox->SetText(FText());
	}
}

void UChattingWindowWidget::EraseAllChatting()
{
	for (int i = 0; i < Chattings.Num(); ++i)
	{
		ChattingScroll->RemoveChild(Chattings[i]);
	}
	Chattings.Reset();
}

void UChattingWindowWidget::QuitButtonClickedCallback()
{
	User->QuittingRoom();
	User->SendMsg("/q");
}
