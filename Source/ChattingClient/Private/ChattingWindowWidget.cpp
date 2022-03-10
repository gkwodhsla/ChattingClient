// Fill out your copyright notice in the Description page of Project Settings.


#include "ChattingWindowWidget.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "MsgWidget.h"
#include "User.h"

void UChattingWindowWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Chattings.Reserve(100);

	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUser::StaticClass(), actors);
	if (actors.Num() > 0)
	{
		User = Cast<AUser>(actors[0]);
	}

	QuitButton->OnClicked.AddUniqueDynamic(this, &UChattingWindowWidget::QuitButtonClickedCallback);
	MsgBox->OnTextCommitted.AddDynamic(this, &UChattingWindowWidget::TextCommitedCallback);
}

void UChattingWindowWidget::AddNewChatting(const std::string& Chatting)
{
	if (!User || !ChattingScroll)
	{
		return;
	}
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
	if (!User || !MsgBox)
	{
		return;
	}
	if (InCommitType == ETextCommit::OnEnter && InText.ToString() != "")
	{
		User->SendMsg(InText.ToString());
		MsgBox->SetText(FText());
		//메시지를 서버를 통해 같은 방의 유저들에게 보내고, 채팅 입력창을 비웁니다.
	}
}

void UChattingWindowWidget::EraseAllChatting()
{
	if (!ChattingScroll)
	{
		return;
	}
	for (int i = 0; i < Chattings.Num(); ++i)
	{
		if (Chattings[i])
		{
			ChattingScroll->RemoveChild(Chattings[i]);
		}
	}
	Chattings.Reset();
}

void UChattingWindowWidget::QuitButtonClickedCallback()
{
	if (User)
	{
		User->QuittingRoom();
		User->SendMsg(QUIT_REQ_COMMAND);
	}
}
