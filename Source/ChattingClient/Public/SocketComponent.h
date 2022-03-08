#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include <string>
#include <vector>
#include <queue>
#include "SocketComponent.generated.h"

class FSocket;

const int32 MAX_BUFFER_SIZE = 1024;
const int32 ADDITIONAL_PACKET_SIZE = 2;
//�ڳ� Ŭ���̾�Ʈ�� �޽��� ����� �����ϱ� ���ؼ�
//��û�� �޽����� �߰������� \r\n���ڸ� �ٿ��ݴϴ�.
const std::string USER_LIST_COMMAND = "UserList";
const std::string USER_INFO_COMMAND = "UserInfo";
const std::string ROOM_LIST_COMMAND = "RoomList";
const std::string ROOM_INFO_COMMAND = "RoomInfo";


const char END_SIGN = '\f';
//����->Ŭ���̾�Ʈ ���� �������� \f�� ����մϴ�.

USTRUCT(BlueprintType)
struct FSendBuffer
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY()
	uint32 LeftPos;
	UPROPERTY()
	uint32 RightPos;
	TStaticArray<char, MAX_BUFFER_SIZE> Buffer;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CHATTINGCLIENT_API USocketComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USocketComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void SendMsg(const FString& Msg);
	void ProcessingRecv();
	void ProcessingSend();

public:
	static std::vector<std::string> Tokenizing(const std::string& Str, const char Delimiter);

	
private:
	void ShowUserInfo();
	void EndGame();
	void ProcessingPacket(const std::string& Packet);

private:
	FSocket* Socket = nullptr;
	TStaticArray<char, MAX_BUFFER_SIZE> RecvBuffer;
	int32 RecvRightPos;
	TQueue<FSendBuffer, EQueueMode::Spsc> SendQ; //Single Producer, Single Consumer
	//������ ������ �Լ����� SendQ�� �����͸� �־���ٰ�
	//���߿� Tick���� �� �濡 �����͸� �۽Ź��ۿ� �����մϴ�.
};
