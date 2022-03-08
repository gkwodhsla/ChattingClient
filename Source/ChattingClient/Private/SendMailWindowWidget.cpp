// Fill out your copyright notice in the Description page of Project Settings.


#include "SendMailWindowWidget.h"

void USendMailWindowWidget::SendButtonClickedCallback()
{
	GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Cyan, "SendButtonClicked");
}

void USendMailWindowWidget::CancelButtonClickedCallback()
{
	GEngine->AddOnScreenDebugMessage(-1, 4.0f, FColor::Cyan, "CancelButtonClicked");
}
