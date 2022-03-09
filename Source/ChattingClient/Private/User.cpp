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

	IsJoinRoom = false;

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


	static ConstructorHelpers::FClassFinder<UUserWidget> RoomInfoWindowWidgetBP
	(TEXT("WidgetBlueprint'/Game/WidgetBP/WBP_RoomInfo.WBP_RoomInfo_C'"));
	if (RoomInfoWindowWidgetBP.Succeeded())
	{
		RoomInfoWidgetClass = RoomInfoWindowWidgetBP.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget> MsgWidgetBP
	(TEXT("WidgetBlueprint'/Game/WidgetBP/WBP_Msg.WBP_Msg_C'"));
	if (MsgWidgetBP.Succeeded())
	{
		MsgWidgetClass = MsgWidgetBP.Class;
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

void AUser::CallLobbyWidgetUserInfo(const std::vector<std::string>& UserList)
{
	auto lobbyWidget = Cast<ULobbyWidget>(LobbyWidget);
	if (lobbyWidget)
	{
		lobbyWidget->ShowUserInfoList(UserList);
	}
}

void AUser::CallLobbyWidgetRoomInfo(const std::vector<std::string>& UserList)
{
	auto lobbyWidget = Cast<ULobbyWidget>(LobbyWidget);
	if (lobbyWidget)
	{
		lobbyWidget->ShowRoomList(UserList);
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

void AUser::CallLobbyWidgetRoomSpecificInfo(const std::vector<std::string>& RoomList)
{
	auto lobbyWidget = Cast<ULobbyWidget>(LobbyWidget);
	if (lobbyWidget)
	{
		lobbyWidget->ShowRoomSpecificInfo(RoomList);
	}
}

void AUser::AddChattingMsgToChattingWindow(const std::vector<std::string>& Chatting)
{
	auto lobbyWidget = Cast<ULobbyWidget>(LobbyWidget);
	if (lobbyWidget)
	{
		lobbyWidget->AddChattingMsgToChattingWindow(Chatting);
	}
}

void AUser::JoiningRoom()
{
	auto lobbyWidget = Cast<ULobbyWidget>(LobbyWidget);
	if (lobbyWidget)
	{
		lobbyWidget->ChattingWindowButton->OnClicked.Broadcast();
		lobbyWidget->EraseAllChatting();
		IsJoinRoom = true;
	}
}

void AUser::QuittingRoom()
{
	auto lobbyWidget = Cast<ULobbyWidget>(LobbyWidget);
	if (lobbyWidget)
	{
		lobbyWidget->GoToLobby();
		IsJoinRoom = false;
	}
}