#include "SocketComponent.h"
#include "Runtime/Networking/Public/Networking.h"
#include "Sockets.h"
#include "SocketSubsystem.h"


// Sets default values for this component's properties
USocketComponent::USocketComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
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

	int32 bytesRead = 0;
	char data[1024];
	memset(data, '\0', 1024);
	Socket->Recv((uint8*)data, 1024, bytesRead);
	FString str(data);
	UE_LOG(LogTemp, Log, TEXT("%s"), *str);
	ProcessingSend();
	//int32 bytesRead = 0;
	//Socket->Recv((uint8*)data, 1024, bytesRead);
	//if (bytesRead > 0)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, data);
	//}
}

void USocketComponent::SendMsg(const FString& Msg)
{
	UE_LOG(LogTemp, Log, TEXT("SendMsg: %s"), *Msg);

	FSendBuffer newMsg;
	newMsg.LeftPos = 0;
	newMsg.RightPos = Msg.Len() + 1;
	for (int i = 0; i < Msg.Len(); ++i)
	{
		newMsg.Buffer[i] = Msg[i];
	}
	newMsg.Buffer[Msg.Len()] = '\n';
	newMsg.Buffer[Msg.Len() + 1] = '\0';
	SendQ.Enqueue(newMsg);
}

void USocketComponent::ProcessingRecv()
{

}

void USocketComponent::ProcessingSend()
{
	while (!SendQ.IsEmpty())
	{
		int32 sendingSize = 0;
		FSendBuffer buffer;
		SendQ.Peek(buffer);

		Socket->Send((uint8*)buffer.Buffer.GetData() + buffer.LeftPos, 
			buffer.RightPos - buffer.LeftPos, sendingSize);
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