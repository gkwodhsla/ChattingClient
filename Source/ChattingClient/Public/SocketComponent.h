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
//텔넷 클라이언트와 메시지 양식을 통일하기 위해서
//요청한 메시지에 추가적으로 \r\n문자를 붙여줍니다.
const std::string USER_LIST_COMMAND = "UserList";
const std::string USER_INFO_COMMAND = "UserInfo";
const std::string ROOM_INFO_COMMAND = "RoomList";


const char END_SIGN = '\f';
//서버->클라이언트 엔드 사인으로 \f를 사용합니다.

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
	//데이터 보내는 함수에서 SendQ에 데이터를 넣어놨다가
	//나중에 Tick에서 한 방에 데이터를 송신버퍼에 복사합니다.
};
