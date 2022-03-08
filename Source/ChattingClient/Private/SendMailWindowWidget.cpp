// Fill out your copyright notice in the Description page of Project Settings.


#include "SendMailWindowWidget.h"
#include "Components/EditableTextBox.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "User.h"

void USendMailWindowWidget::NativeConstruct()
{
	TArray<AActor*> actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AUser::StaticClass(), actors);
	User = Cast<AUser>(actors[0]);

	SendButton->OnClicked.AddUniqueDynamic(this, &USendMailWindowWidget::SendButtonClickedCallback);
}

void USendMailWindowWidget::SendButtonClickedCallback()
{
	FText to = ToTextBox->GetText();
	FText content = MessageTextBox->GetText();

	std::string msgToSend = "to ";
	msgToSend = msgToSend + std::string(TCHAR_TO_UTF8(*to.ToString())) + " " +
		std::string(TCHAR_TO_UTF8(*content.ToString()));

	User->SendMsg(msgToSend.c_str());
}
