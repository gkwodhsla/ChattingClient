#include "SocketComponent.h"
#include "Runtime/Networking/Public/Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include <algorithm>
#include <sstream>
// Sets default values for this component's properties
USocketComponent::USocketComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	Socket = nullptr;
	memset(RecvBuffer.GetData(), '\0', MAX_BUFFER_SIZE);
	RecvRightPos = 0;
}


// Called when the game starts
void USocketComponent::BeginPlay()
{
	Super::BeginPlay();
	
	Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);
	Socket->SetNonBlocking(true);
	TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	FIPv4Address ip(127, 0, 0, 1);
	int32 port = 8000;
	addr->SetIp(ip.Value);
	addr->SetPort(port);
	bool connected = Socket->Connect(*addr);
	if (connected)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, "Server Connection");
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, "Server Failed to  connection");
	}
}


// Called every frame
void USocketComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	ProcessingRecv();
	ProcessingSend();
}

void USocketComponent::SendMsg(const FString& Msg)
{
	UE_LOG(LogTemp, Log, TEXT("SendMsg: %s"), *Msg);

	FSendBuffer newMsg;
	newMsg.LeftPos = 0;
	newMsg.RightPos = Msg.Len() + ADDITIONAL_PACKET_SIZE;
	for (int i = 0; i < Msg.Len(); ++i)
	{
		newMsg.Buffer[i] = Msg[i];
	}
	newMsg.Buffer[Msg.Len()] = '\r';
	newMsg.Buffer[Msg.Len() + 1] = '\n';
	newMsg.Buffer[Msg.Len() + 2] = '\0';
	SendQ.Enqueue(newMsg);
}

void USocketComponent::ProcessingRecv()
{
	int32 recvSize = 0; //SOCKET_ERROR가 -1이라 int로 했습니다.
	bool isSuccess = Socket->Recv((uint8*)RecvBuffer.GetData(), MAX_BUFFER_SIZE, recvSize);

	if (!isSuccess)
	{
		EndGame();
	}

	RecvRightPos += recvSize;
	
	int leftPos = 0;
	for (int i = 0; i < RecvRightPos; ++i)
	{
		if (RecvBuffer[i] == END_SIGN) //엔드 사인 발견!(패킷 완성)
		{
			std::string packet(RecvBuffer.GetData() + leftPos, RecvBuffer.GetData() + (i - 1)); //패킷엔 엔드사인과 캐리지리턴을 띠어냅니다.
			leftPos = i + 1; //엔드 사인 다음을 left로 삼습니다.
			ProcessingPacket(packet);
		}
	}
	//완성된 패킷이 뭉쳐있는 경우를 처리해줍니다.

	if (leftPos != RecvRightPos) //완성되지 않은 패킷이 존재하는 경우
	{
		std::transform(RecvBuffer.GetData() + leftPos, RecvBuffer.GetData() + RecvRightPos, RecvBuffer.GetData(), [](const char Ch) {return Ch; });
		//완성되지 않은 패킷을 버퍼의 맨 앞으로 옮겨 다음 수신 때 완성된 패킷을 만들 수 있게 합니다.
	}
	else
	{
		//UE_LOG(LogTemp, Log, TEXT("Packet Complete"));
		memset(RecvBuffer.GetData(), '\0', MAX_BUFFER_SIZE);
		RecvRightPos = 0;
	}
	//모든 패킷을 정상처리했을 경우 버퍼와 RecvRightPos를 초기화시킵니다.
}
//서버에서도 메시지를 보낼 때 엔드 사인으로 '\n'을 사용합니다.

void USocketComponent::ProcessingSend()
{
	while (!SendQ.IsEmpty())
	{
		int32 sendingSize = 0;
		FSendBuffer buffer;
		SendQ.Peek(buffer);

		bool isSuccess = Socket->Send((uint8*)buffer.Buffer.GetData() + buffer.LeftPos, 
			buffer.RightPos - buffer.LeftPos, sendingSize);
		if (!isSuccess)
		{
			EndGame();
		}
		FString str(buffer.Buffer.GetData());
		UE_LOG(LogTemp, Log, TEXT("Send: %s"), *str);
		buffer.LeftPos += sendingSize;
		if (buffer.LeftPos == buffer.RightPos) //만약 데이터 송신이 성공했다면
		{
			SendQ.Pop(); //큐에서 빼내고 다음 데이터를 송신합니다.
			continue;
		}
		break;
	}
}

void USocketComponent::EndGame()
{
	Socket->Close();
	UWorld* world = GetWorld();
	UKismetSystemLibrary::QuitGame(world, UGameplayStatics::GetPlayerController(world, 0), EQuitPreference::Quit, false);
}

void USocketComponent::ProcessingPacket(const std::string& Packet)
{
	FString msg(Packet.c_str());
	UE_LOG(LogTemp, Log, TEXT("From Server: %s"), *msg);
	//각각의 패킷마다 적절한 함수를 호출해 명령어를 처리합니다.

}

std::vector<std::string> USocketComponent::Tokenizing(const std::string& Str, const char Delimiter)
{
	std::string temp;
	std::istringstream stream{ Str };
	std::vector<std::string> tokens;
	while (std::getline(stream, temp, ' '))
	{
		tokens.emplace_back(temp);
	}
	return tokens;
}