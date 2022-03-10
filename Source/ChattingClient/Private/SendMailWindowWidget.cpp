// Fill out your copyright notice in the Description page of Project Settings.


#include "SendMailWindowWidget.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "User.h"

void USendMailWindowWidget::NativeConstruct()
{
	Super::NativeConstruct();

	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUser::StaticClass(), actors);
	if (actors.Num() > 0)
	{
		User = Cast<AUser>(actors[0]);
	}

	SendButton->OnClicked.AddUniqueDynamic(this, &USendMailWindowWidget::SendButtonClickedCallback);
}

void USendMailWindowWidget::SendButtonClickedCallback()
{
	if (!User || !MessageTextBox || !ToTextBox)
	{
		return;
	}
	FText to = ToTextBox->GetText();
	FText content = MessageTextBox->GetText();

	FString msgToSend = SEND_MAIL_REQ_COMMAND;
	msgToSend.Append(std::string(TCHAR_TO_UTF8(*to.ToString())).c_str());
	msgToSend.AppendChar(' ');
	msgToSend.Append(std::string(TCHAR_TO_UTF8(*content.ToString())).c_str());

	User->SendMsg(msgToSend);

	ToTextBox->SetText(FText::FromString(""));
	

	if (!User->IsJoinRoom)
	{
		MessageTextBox->SetText(FText::FromString(""));
	}
}

void USendMailWindowWidget::ChangeSendMailMode()
{
	if (!MessageTextBox)
	{
		return;
	}

	MessageTextBox->SetIsReadOnly(false);
	MessageTextBox->SetHintText(FText::FromString("Message"));
}

void USendMailWindowWidget::ChangeInviteMode()
{
	if (!MessageTextBox)
	{
		return;
	}
	MessageTextBox->SetIsReadOnly(true);
	MessageTextBox->SetHintText(FText::FromString(""));

	FString msg = User->UserName.ToString();
	msg.Append(TEXT(" Invite you room "));
	msg.Append(User->RoomName.ToString());

	MessageTextBox->SetText(FText::FromString(msg));
}