#include "stdafx.h"
#include "BaseView.h"
#include "OutputListener.h"
#include "LoadBalancingListener.h"
#include "TestView.h"
#include <fstream>
#include <string>

using namespace ExitGames::Common;
using namespace ExitGames::LoadBalancing;

const JString PeerStatesStr[] = {
	L"Uninitialized",
	L"PeerCreated",
	L"ConnectingToNameserver",
	L"ConnectedToNameserver",
	L"DisconnectingFromNameserver",
	L"Connecting",
	L"Connected",
	L"WaitingForCustomAuthenticationNextStepCall",
	L"Authenticated",
	L"JoinedLobby",
	L"DisconnectingFromMasterserver",
	L"ConnectingToGameserver",
	L"ConnectedToGameserver",
	L"AuthenticatedOnGameServer",
	L"Joining",
	L"Joined",
	L"Leaving",
	L"Left",
	L"DisconnectingFromGameserver",
	L"ConnectingToMasterserver",
	L"ConnectedComingFromGameserver",
	L"AuthenticatedComingFromGameserver",
	L"Disconnecting",
	L"Disconnected"
};

// TODO: update PeerStatesStr when PeerStates changes
// Checker below checks count match only
class PeerStatesStrChecker
{
public:
	PeerStatesStrChecker(void)
	{
		DEBUG_ASSERT(sizeof(PeerStatesStr) / sizeof(JString) == PeerStates::Disconnected + 1);
	}
} checker;

LocalPlayer::LocalPlayer(void) : x(0), y(0),z(0), lastUpdateTime(0)
{
}

LoadBalancingListener::LoadBalancingListener(BaseView* pView)
{
	mpLbc = NULL;
	mpView = pView;
}

LoadBalancingListener::~LoadBalancingListener(void)
{
	delete mpView;
}

void LoadBalancingListener::setLBC(ExitGames::LoadBalancing::Client* pLbc)
{
	this->mpLbc = pLbc;
}

void LoadBalancingListener::connect(const JString& userName)
{
	mpLbc->connect(AuthenticationValues().setUserID(JString() + GETTIMEMS()), userName);
}

void LoadBalancingListener::disconnect() {
	mpLbc->disconnect();
}


void LoadBalancingListener::debugReturn(int debugLevel, const JString& string)
{
	Console::get().debugReturn(debugLevel, string);
}

void LoadBalancingListener::connectionErrorReturn(int errorCode)
{
	Console::get().writeLine(JString(L"connection failed with error ") + errorCode);
	updateState();
}

void LoadBalancingListener::clientErrorReturn(int errorCode)
{
	Console::get().writeLine(JString(L"received error ") + errorCode + L" from client");
	updateState();
}

void LoadBalancingListener::warningReturn(int warningCode)
{
	Console::get().writeLine(JString(L"received warning ") + warningCode + " from client");
}

void LoadBalancingListener::serverErrorReturn(int errorCode)
{
	Console::get().writeLine(JString(L"received error ") + errorCode + " from server");
	updateState();
}

void LoadBalancingListener::joinRoomEventAction(int playerNr, const JVector<int>& playernrs, const Player& player)
{
	if (mLocalPlayerNr != playerNr)
	{
		//つながった！
		misConect = true;
	}

	Console::get().writeLine(JString("player ") + playerNr + L" " + player.getName() + L" has joined the game");
}

void LoadBalancingListener::leaveRoomEventAction(int playerNr, bool isInactive)
{
	if (isInactive)
		Console::get().writeLine(JString(L"player ") + playerNr + L" has suspended the game");
	else
	{
		Console::get().writeLine(JString(L"player ") + playerNr + L" has abandoned the game");
	}

	misConect = false;//切れた。
}

//処理いろいろ
//INFO : イベントを送信するグループもわけようと思えば分けれるよ
//この関数を参考に色々イベントを送信する関数を定義するのよ
void LoadBalancingListener::raiseSomeEvent() {
	//char message[256];
	//sprintf_s(message, "raiseEvent\n");
	//OutputDebugStringA(message);
	////さまざまな種類のイベント（「移動」、「撮影」など）を区別するために
	////別個のイベントコードを使用する
	//nByte eventCode = 2;
	////Photonsのシリアル化によってサポートされている限り、
	////好きな方法でペイロードデータを整理します
	//ExitGames::Common::Hashtable evData;
	//evData.put((nByte)1, m_val);
	////配列とかはこうやって送る

	////Hashtable data;
	////nByte coords[] = { static_cast<nByte>(mLocalPlayer.x), static_cast<nByte>(mLocalPlayer.y) };
	////data.put((nByte)1, coords, 3);

	//Hashtable ed;
	//nByte* codetext = (nByte*)malloc(sizeof(nByte)*(strlen(m_text) + 1));
	//for (int i = 0; i < strlen(m_text) + 1; i++)
	//{
	//	codetext[i] = static_cast<nByte>(m_text[i]);
	//}
	//ed.put((nByte)enText, codetext, strlen(m_text) + 1);


	////どこにでも到着する必要がある場合は、信頼できるものを送信します
	//bool sendReliable = false;
	////opRaiseEventでイベント送信する。引数にオプションで色々設定できるが
	//mpLbc->opRaiseEvent(sendReliable, m_text, enText);

	//delete[] m_text;
	//m_text = new char('\0');
}


void LoadBalancingListener::SetTeamMonsterInfo(int info[3]) {
	for (int i = 0; i < 3; i++)
		m_toRaiseTeamData[i] = info[i];
}
void LoadBalancingListener::raiseMonData()
{
	//mpLbc->opRaiseEvent(false, m_toRaiseTeamData, enMonData);
	Hashtable data;
	nByte coords[] = { static_cast<nByte>(m_toRaiseTeamData[0]), static_cast<nByte>(m_toRaiseTeamData[1]),static_cast<nByte>(m_toRaiseTeamData[2])};
	data.put((nByte)1, coords, 3);
	mpLbc->opRaiseEvent(false, data, enMonData);// , RaiseEventOptions().setInterestGroup(mSendGroup ? mSendGroup : mUseGroups ? getGroupByPos() : 0));
	//char str[256];
	////sprintf_s(str, "num is %d / raise data num ... %d \n", m_monNUM,data.getValue(1)[0]);
	//OutputDebugString(str);
}

void LoadBalancingListener::raiseMonAIs() {
	const nByte NumKey = 101;
	const nByte CodeKey = 102;
	for (int i = 0; i < 3; i++) {
		Hashtable ev;
		ev.put(NumKey, i);
		JString code = m_text[i];
		ev.put(CodeKey, code);
		mpLbc->opRaiseEvent(false, ev, enText);
	}
	//OutputDebugStringW(code);
	//mpLbc->opRaiseEvent(false, ev, enText);
	//bool sendReliable = false;
	//for (int i = 0; i < 3; i++) {
	//	mpLbc->opRaiseEvent(sendReliable, m_text[i], enText);
	//	delete[] m_text[i];
	//	m_text[i] = new char('\0');
	//}
	/*Hashtable ed;
	nByte* codetext[] = {
		(nByte*)malloc(sizeof(nByte)*(strlen(m_text[0]) + 1)),
		(nByte*)malloc(sizeof(nByte)*(strlen(m_text[1]) + 1)),
		(nByte*)malloc(sizeof(nByte)*(strlen(m_text[2]) + 1))
	};
	for (int j = 0; j < 3; j++) {
		for (int i = 0; i < strlen(m_text[j]) + 1; i++)
		{
			codetext[j][i] = static_cast<nByte>(m_text[j][i]);
		}
		ed.put((nByte)enText, codetext, strlen(m_text[j]) + 1);
	}
	bool sendReliable = false;
	mpLbc->opRaiseEvent(sendReliable, ed, enText);
	for (int i = 0; i < 3; i++) {
		delete[] m_text[i];
		m_text[i] = new char('\0');
	}*/
}

//opRaiseEventでイベントが送信されるとこの関数が呼ばれる
void LoadBalancingListener::customEventAction(int playerNr, nByte eventCode, const Object& eventContentObj)
{
	// logging the string representation of the eventContent can be really useful for debugging, but use with care: for big events this might get expensive
	//EGLOG(ExitGames::Common::DebugLevel::ALL, L"an event of type %d from player Nr %d with the following content has just arrived: %ls", eventCode, playerNr, eventContent.toString(true).cstr());
	switch (eventCode)
	{
	case 1:
	{
		//コンテンツのコピーにアクセス
		ExitGames::Common::Hashtable content = ExitGames::Common::ValueObject<ExitGames::Common::Hashtable>(eventContentObj).getDataCopy();
		//アドレスでアクセスします（この関数が返るとすぐに無効になるため、後でアクセスを続ける必要があるデータのすべての部分をコピーする必要があります）
		ExitGames::Common::Hashtable* pContent = ExitGames::Common::ValueObject<ExitGames::Common::Hashtable>(eventContentObj).getDataAddress();
	}
	break;
	case 2:
	{
		//ペイロードはハッシュテーブルである必要はありません。
		float content = ExitGames::Common::ValueObject<float>(eventContentObj).getDataCopy();
	}
	break;
	case 3:
	{
		// 浮動小数点数の配列
		float* pContent = ExitGames::Common::ValueObject<float*>(eventContentObj).getDataCopy();
		float** ppContent = ExitGames::Common::ValueObject<float*>(eventContentObj).getDataAddress();
		short contentElementCount = *ExitGames::Common::ValueObject<float*>(eventContentObj).getSizes();
		//配列をペイロードとして保持するオブジェクトでgetDataCopy（）を呼び出すときは、
		//deallocateArray（）を使用して配列のコピーを自分で割り当て解除する必要があります。
		ExitGames::Common::MemoryManagement::deallocateArray(pContent);
	}
	break;
	case 4:
	{
		//position
	}
	break;
	case enText:
	{
		const nByte NumKey = 101;
		const nByte CodeKey = 102;
		ExitGames::Common::Hashtable eventDataContent = ExitGames::Common::ValueObject<ExitGames::Common::Hashtable>(eventContentObj).getDataCopy();
		int number = -1;
		// nByte key and int value:
		if (eventDataContent.getValue(NumKey))
			number = (ExitGames::Common::ValueObject<int>(eventDataContent.getValue(NumKey))).getDataCopy();
		if (eventDataContent.getValue(CodeKey)) {
			m_isAiLoaded[number] = true;
			auto code = (ExitGames::Common::ValueObject<JString>(eventDataContent.getValue(CodeKey))).getDataCopy();
			char str[256];
			sprintf_s(str, "number is %d\n", number);
			OutputDebugString(str);
			OutputDebugStringW(code);
			OutputDebugString("\n");
			//SetCurrentDirectory("NetworkEnemyAIs");
			std::string pythonFileName = "NetworkEnemyAIs/";
			pythonFileName += std::to_string(number + 1);
			pythonFileName += "enemy.py";
			std::ofstream outputfile(pythonFileName);
			outputfile << code.toString();
			outputfile.close();
		}

		//m_isGotPythonCodes = true;
		/*OutputDebugString("GOT A EVENT CODE  TYPE :: TEXT\n Message is ");
		char* content = ExitGames::Common::ValueObject<char*>(eventContentObj).getDataCopy();
		short contentElementCount = *ExitGames::Common::ValueObject<char*>(eventContentObj).getSizes();
		OutputDebugStringW(ExitGames::Common::JString(L"\n") + eventContentObj.toString() + L"\n");
		SetCurrentDirectory("PythonEnemyAIs");
		std::ofstream outputfile("1enemy.py");
		outputfile << eventContentObj.toString();
		outputfile.close();
		ExitGames::Common::MemoryManagement::deallocateArray(content);*/
	}
	break;
	case enMonData:
	{
		//nByte* pContent = ExitGames::Common::ValueObject<nByte*>(eventContentObj).getDataCopy();
		////int** ppContent = ExitGames::Common::ValueObject<int*>(eventContentObj).getDataAddress();
		//short contentElementCount = *ExitGames::Common::ValueObject<int*>(eventContentObj).getSizes();
		////int num = static_cast<int>(pContent[0]);
		//auto num = pContent[0];
		//auto monid = pContent[1];
		//char str[256];
		//sprintf_s(str, "num is %d\n", num);
		//OutputDebugStringA(str);
		////配列をペイロードとして保持するオブジェクトでgetDataCopy（）を呼び出すときは、
		////deallocateArray（）を使用して配列のコピーを自分で割り当て解除する必要があります。
		//ExitGames::Common::MemoryManagement::deallocateArray(pContent);
		//OutputDebugString("ISFJIODFJIOSDJFIODSJFIODSJFIDOSJFIOSFJIODJSFIOSDFJ\n");
		//char* content = ExitGames::Common::ValueObject<char*>(eventContentObj).getDataCopy();
		//short contentElementCount = *ExitGames::Common::ValueObject<char*>(eventContentObj).getSizes();
		//auto str = eventContentObj.toString();
		//for (int i = 0; i < 3; i++) {
		//	//ID
		//	m_enemyTeamData[i] = str[i];
		//}
		//OutputDebugStringW(ExitGames::Common::JString(L"\n") + eventContentObj.toString() + L"\n");
		misHang = true;
		ExitGames::Common::Hashtable eventContent = ExitGames::Common::ValueObject<ExitGames::Common::Hashtable>(eventContentObj).getDataCopy();
		Object const* obj = eventContent.getValue("1");
		if (!obj)
			obj = eventContent.getValue((nByte)1);
		if (!obj)
			obj = eventContent.getValue(1);
		if (!obj)
			obj = eventContent.getValue(1.0);
		if (obj && obj->getDimensions() == 1 && obj->getSizes()[0] == 3)
		{
			if (obj->getType() == TypeCode::DOUBLE)
			{
				double* data = ((ValueObject<double*>*)obj)->getDataCopy();
				m_enemyTeamData[0] = (int)data[0];
				m_enemyTeamData[1] = (int)data[1];
				m_enemyTeamData[2] = (int)data[2];
			}
			if (obj->getType() == TypeCode::INTEGER)
			{
				int* data = ((ValueObject<int*>*)obj)->getDataCopy();
				m_enemyTeamData[0] = (int)data[0];
				m_enemyTeamData[1] = (int)data[1];
				m_enemyTeamData[2] = (int)data[2];
			}
			else if (obj->getType() == TypeCode::BYTE)
			{
				nByte* data = ((ValueObject<nByte*>*)obj)->getDataCopy();
				m_enemyTeamData[0] = (int)data[0];
				m_enemyTeamData[1] = (int)data[1];
				m_enemyTeamData[2] = (int)data[2];
			}
			else if (obj->getType() == TypeCode::OBJECT)
			{
				Object* data = ((ValueObject<Object*>*)obj)->getDataCopy();
				if (data[0].getType() == TypeCode::INTEGER)
				{
					m_enemyTeamData[0] = ((ValueObject<int>*)(data + 0))->getDataCopy();
					m_enemyTeamData[1] = ((ValueObject<int>*)(data + 1))->getDataCopy();
					m_enemyTeamData[2] = ((ValueObject<int>*)(data + 2))->getDataCopy();
				}
				else
				{
					m_enemyTeamData[0] = (int)((ValueObject<double>*)(data + 0))->getDataCopy();
					m_enemyTeamData[1] = (int)((ValueObject<double>*)(data + 1))->getDataCopy();
					m_enemyTeamData[2] = (int)((ValueObject<double>*)(data + 2))->getDataCopy();
				}
				MemoryManagement::deallocateArray(data);
			}
		}
		//char str[256];
		//sprintf_s(str, "get num is %d / get monid is %d\n", num, monid);
		//m_hangMNUM = num;
		//m_hangMID = monid;
		//OutputDebugString(str);
	}
	break;
	default:
	{
		//より洗練されたデータ型を送受信する方法のコード例については、
		//C ++クライアントSDK内のdemo_typeSupportを参照してください
	}
	break;
	}
}

void LoadBalancingListener::disconnectReturn(void)
{
	updateState();
	Console::get().writeLine(L"disconnected");
}

void LoadBalancingListener::createRoomReturn(int localPlayerNr, const Hashtable& gameProperties, const Hashtable& playerProperties, int errorCode, const JString& errorString)
{
	updateState();
	if (errorCode == ErrorCode::OK)
	{
		Console::get().writeLine(L"room has been created");
		afterRoomJoined(localPlayerNr);
	}
	else
		Console::get().writeLine(L"Warn: opCreateRoom() failed: " + errorString);
}

void LoadBalancingListener::joinOrCreateRoomReturn(int localPlayerNr, const Hashtable& gameProperties, const Hashtable& playerProperties, int errorCode, const JString& errorString)
{
	updateState();
	if (errorCode == ErrorCode::OK)
	{
		Console::get().writeLine(L"room has been entered");
		afterRoomJoined(localPlayerNr);
	}
	else
		Console::get().writeLine(L"Warn: opJoinOrCreateRoom() failed: " + errorString);
}

void LoadBalancingListener::joinRoomReturn(int localPlayerNr, const Hashtable& gameProperties, const Hashtable& playerProperties, int errorCode, const JString& errorString)
{
	updateState();
	if (errorCode == ErrorCode::OK)
	{
		Console::get().writeLine(L"game room has been successfully joined");
		afterRoomJoined(localPlayerNr);
	}
	else
		Console::get().writeLine(L"opJoinRoom() failed: " + errorString);
}

void LoadBalancingListener::joinRandomRoomReturn(int localPlayerNr, const Hashtable& gameProperties, const Hashtable& playerProperties, int errorCode, const JString& errorString)
{
	updateState();
	if (errorCode == ErrorCode::NO_MATCH_FOUND)
		createRoom();
	else if (errorCode == ErrorCode::OK)
	{
		Console::get().writeLine(L"game room has been successfully joined");
		afterRoomJoined(localPlayerNr);
	}
	else
		Console::get().writeLine(L"opJoinRandomRoom() failed: " + errorString);
}

void LoadBalancingListener::leaveRoomReturn(int errorCode, const JString& errorString)
{
	updateState();
	if (errorCode == ErrorCode::OK)
		Console::get().writeLine(L"game room has been successfully left");
	else
		Console::get().writeLine(L"opLeaveRoom() failed: " + errorString);
}

void LoadBalancingListener::gotQueuedReturn(void)
{
	updateState();
}

void LoadBalancingListener::joinLobbyReturn(void)
{
	Console::get().writeLine(L"joined lobby");
	updateState();
}

void LoadBalancingListener::leaveLobbyReturn(void)
{
	Console::get().writeLine(L"left lobby");
	updateState();
}

void LoadBalancingListener::onLobbyStatsUpdate(const JVector<LobbyStatsResponse>& res)
{
	Console::get().writeLine(L"===================== lobby stats update");
	for (unsigned int i = 0; i < res.getSize(); ++i)
		Console::get().writeLine(res[i].toString());

	// lobby stats request test
	JVector<LobbyStatsRequest> ls;
	ls.addElement(LobbyStatsRequest());
	ls.addElement(LobbyStatsRequest(L"AAA"));
	ls.addElement(LobbyStatsRequest(L"BBB"));
	ls.addElement(LobbyStatsRequest(L"CCC", LobbyType::DEFAULT));
	ls.addElement(LobbyStatsRequest(L"AAA", LobbyType::SQL_LOBBY));
	mpLbc->opLobbyStats(ls);
}

void LoadBalancingListener::onLobbyStatsResponse(const ExitGames::Common::JVector<LobbyStatsResponse>& res)
{
	Console::get().writeLine(L"===================== lobby stats response");
	for (unsigned int i = 0; i < res.getSize(); ++i)
		Console::get().writeLine(res[i].toString());
}

void LoadBalancingListener::onRoomListUpdate()
{
	const JVector<Room*>& rooms = mpLbc->getRoomList();
	JVector<JString> names(rooms.getSize());
	for (unsigned int i = 0; i < rooms.getSize(); ++i)
		names.addElement(rooms[i]->getName());
	//mpView->updateRoomList(names);
}

void LoadBalancingListener::onRoomPropertiesChange(const ExitGames::Common::Hashtable& changes)
{
}

void LoadBalancingListener::updateState()
{
	int state = mpLbc->getState();
	mpView->updateState(state, PeerStatesStr[state], state == PeerStates::Joined ? mpLbc->getCurrentlyJoinedRoom().getName() : JString());
}


void LoadBalancingListener::afterRoomJoined(int localPlayerNr)
{
	Console::get().writeLine(JString(L"afterRoomJoined: localPlayerNr=") + localPlayerNr);
	this->mLocalPlayerNr = localPlayerNr;
	MutableRoom& myRoom = mpLbc->getCurrentlyJoinedRoom();
	Hashtable props = myRoom.getCustomProperties();
}

void LoadBalancingListener::createRoom()
{
	JString name =
#ifdef __UNREAL__
		JString(L"UE-")
#else
		JString(L"native-")
#endif
		+ (rand() % 100);
	//Hashtable props;
	//props.put(L"m", mMap);
	//RoomOptions roomOptions(bool isVisible = true, bool isOpen = true, nByte maxPlayers = 2);
	//mpLbc->opCreateRoom(name, RoomOptions().setCustomRoomProperties(props));

	mpLbc->opCreateRoom(name, RoomOptions().setMaxPlayers(m_maxPlayer));
	Console::get().writeLine(L"Creating room " + name);
}

void LoadBalancingListener::connectReturn(int errorCode, const JString& errorString, const JString& region, const JString& cluster)
{
	updateState();
	if (errorCode == ErrorCode::OK)
	{
		Console::get().writeLine(L"connected to cluster " + cluster + L" of region " + region);
		mpLbc->opJoinRandomRoom(Hashtable(), m_maxPlayer);
	}
	else
		Console::get().writeLine(JString(L"Warn: connect failed ") + errorCode + L" " + errorString);
}

void LoadBalancingListener::service()
{
	unsigned long t = GETTIMEMS();
	if ((t - mLocalPlayer.lastUpdateTime) > PLAYER_UPDATE_INTERVAL_MS)
	{
		mLocalPlayer.lastUpdateTime = t;
		if (mpLbc->getState() == PeerStates::Joined) {
			//毎フレーム呼ばれる
		}
	}
}

bool LoadBalancingListener::isGotEnemyPythonCodes() {
	if (m_isAiLoaded[0] && m_isAiLoaded[1] && m_isAiLoaded[2])
		return true;
	return false;
}
