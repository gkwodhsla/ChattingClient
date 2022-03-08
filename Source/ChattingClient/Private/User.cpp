// Fill out your copyright notice in the Description page of Project Settings.


#include "User.h"
#include "LoginWidget.h"
#include "LobbyWidget.h"
#include "SendMailWindowWidget.h"
#include "CreateRoomWindowWidget.h"
#include "UserInfoWidget.h"
#include "SocketComponent.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AUser::AUser()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FClassFinder<UUserWidget> loginWidgetBP(TEXT("WidgetBlueprint'/Game/WidgetBP/WBP_Login.WBP_Login_C'"));
	if (loginWidgetBP.Succeeded())
	{
		LoginWidgetClass = loginWidgetBP.Class;
		LoginWidget = CreateWidget(GetWorld(), LoginWidgetClass);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> lobbyWidgetBP(TEXT("WidgetBlueprint'/Game/WidgetBP/WBP_Lobby.WBP_Lobby_C'"));
	if (lobbyWidgetBP.Succeeded())
	{
		LobbyWidgetClass = lobbyWidgetBP.Class;
		LobbyWidget = CreateWidget(GetWorld(), LobbyWidgetClass);
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> UserInfoWidgetBP(TEXT("WidgetBlueprint'/Game/WidgetBP/WBP_UserInfo.WBP_UserInfo_C'"));
	if (UserInfoWidgetBP.Succeeded())
	{
		UserInfoWidgetClass = UserInfoWidgetBP.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> UserSpecificInfoWindowWidgetBP
	(TEXT("WidgetBlueprint'/Game/WidgetBP/WBP_UserSpecificInfoWindow.WBP_UserSpecificInfoWindow_C'"));
	if (UserSpecificInfoWindowWidgetBP.Succeeded())
	{
		UserSpecificInfoWindowWidgetClass = UserSpecificInfoWindowWidgetBP.Class;
	}

	SockComp = CreateDefaultSubobject<USocketComponent>(TEXT("SockComp"));
}

// Called when the game starts or when spawned
void AUser::BeginPlay()
{
	Super::BeginPlay();
	if (LoginWidget)
	{
		auto playerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		if (IsValid(playerController))
		{
			FInputModeUIOnly mode;
			playerController->SetInputMode(mode);
			playerController->SetShowMouseCursor(true);
		}
		LoginWidget->AddToViewport();
	}
}

// Called every frame
void AUser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	SockComp->ProcessingRecv();
	SockComp->ProcessingSend();
}

void AUser::SendMsg(const FString& Msg)
{
	SockComp->SendMsg(Msg);
}


void AUser::AddLobbyCallbackFunction()
{
	//ULobbyWidget* lobbyWidget = Cast<ULobbyWidget>(LobbyWidget);
	//lobbyWidget->UserListButton->OnClicked.AddDynamic(lobbyWidget, &ULobbyWidget::UserListButtonClickedCallback);
	//lobbyWidget->RoomListButton->OnClicked.AddDynamic(lobbyWidget, &ULobbyWidget::RoomListButtonClickedCallback);
	//lobbyWidget->CreateRoomButton->OnClicked.AddDynamic(lobbyWidget, &ULobbyWidget::CreateRoomButtonClickedCallback);
	//lobbyWidget->SendMailButton->OnClicked.AddDynamic(lobbyWidget, &ULobbyWidget::SendMailButtonClickedCallback);
	//lobbyWidget->ExitButton->OnClicked.AddDynamic(lobbyWidget, &ULobbyWidget::ExitButtonClickedCallback);

	//lobbyWidget->SendMailWindow->SendButton->OnClicked.
	//	AddDynamic(lobbyWidget->SendMailWindow, &USendMailWindowWidget::SendButtonClickedCallback);
	//lobbyWidget->SendMailWindow->CancelButton->OnClicked.
	//	AddDynamic(lobbyWidget->SendMailWindow, &USendMailWindowWidget::CancelButtonClickedCallback);

	//lobbyWidget->CreateRoomWindow->CreateButton->OnClicked.
	//	AddDynamic(lobbyWidget->CreateRoomWindow, &UCreateRoomWindowWidget::CreateButtonClickedCallback);
	//lobbyWidget->CreateRoomWindow->CancelButton->OnClicked.
	//	AddDynamic(lobbyWidget->CreateRoomWindow, &UCreateRoomWindowWidget::CancelButtonClickedCallback);
}

void AUser::CallLobbyWidgetUserInfo(const std::vector<std::string>& UserList)
{
	auto lobbyWidget = Cast<ULobbyWidget>(LobbyWidget);
	if (lobbyWidget)
	{
		lobbyWidget->ShowUserInfoList(UserList);
	}
}

void AUser::CallLobbyWidgetUserSpecificInfo(const std::vector<std::string>& UserList)
{
	auto lobbyWidget = Cast<ULobbyWidget>(LobbyWidget);
	if (lobbyWidget)
	{
		lobbyWidget->ShowUserSpecificInfo(UserList);
	}
}