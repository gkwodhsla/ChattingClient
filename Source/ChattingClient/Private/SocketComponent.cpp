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

	//int32 bytesRead = 0;
	//Socket->Recv((uint8*)data, 1024, bytesRead);
	//if (bytesRead > 0)
	//{
	//	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, data);
	//}
	//������, ���� ������, ������ ���� ����Ʈ ��, �÷���
	//0�� ��ȯ �� ���� ���ۿ� �����Ͱ� ������ �ǹ��Ѵ�.

	//���⼭ ��� send, recv�� �����Ѵ�.
	//send�� �츮�� ������ �����ϰ� ť�� �ְ� ��� ������!
}

