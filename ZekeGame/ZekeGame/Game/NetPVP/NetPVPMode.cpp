#include "stdafx.h"
#include <fstream>
#include <random>
#include "CRatingSystem.h"
#include "NetPVPMode.h"
#include "../Title/ModeSelect.h"
#include "../Fade/Fade.h"
#include "../Fade/MusicFade.h"
#include "../ExchangeData/ExchangeData.h"
#include "..//GameCursor.h"
#include "NetAISelect.h"
#include "../SaveLoad/PythonFileLoad.h"
#include "../Online/NetworkLogic.h"
#include "../Online/Console.h"
#include "backParticle.h"
#include "../Game.h"
#include "..//Fade/MusicFade.h"
#include "../ReturnButton/ReturnButton.h"

NetPVPMode::NetPVPMode()
{
	NetSystem().CreateNetworkSystem();
	m_fade = FindGO<Fade>("fade");
	m_fade->FadeIn();
}

void NetPVPMode::init(std::vector<std::string> files, int monai[3], int moid[3],int aimode[3])
{
	for (int i=0;i<3;i++)
	{
		if (aimode[i] == 1) 
			m_files.push_back("VISUAL AI");
		else 
			m_files.push_back(files[monai[i]]);
		m_monai[i] = monai[i];
		m_moid[i] = moid[i];
		m_aimode[i] = aimode[i];
	}
}

bool NetPVPMode::Start() {
	std::random_device rnd;
	timeout  = rnd() % 20;
	timeout += 10;
	InitUI();
	return true;
}

void NetPVPMode::OnDestroy()
{
	DeleteGO(m_informationSp);
	DeleteGO(m_font);
	DeleteGO(m_cur);
	DeleteGO(m_wallpaper);
	DeleteGO(m_returnButton);
	NetSystem().DestroyNetworkSystem();
	for (auto p : m_particles) {
		DeleteGO(p);
	}
	m_lbl->DataReset();
}

void NetPVPMode::Update() {
	if (m_lbl == nullptr) {
		m_lbl = NetSystem().GetNetworkLogic().GetLBL();
		if (m_lbl == nullptr)
			return;
	}
	NetSystem().GetNetworkLogic().Update();
	//AIやモンスターやレートなどのデータを送信
	 RaiseData();
	 //敵のデータを読み込む
	 LoadEnemyData();
	 //ボタンやテキストの更新
	 UiUpdate();
	 //通信データの状態をチェックする
	 CheckDatas();
	 //フェード後に戦闘開始
	 if (m_fade->isFadeStop() && m_isfade)  BattleStart();
	//タイムアウト関係の処理
	 UpdateTimeOutProc();
}

void NetPVPMode::TimeOut() {
	printf("time out. disconnecting...\n");
	m_lbl->disconnect();
	m_lbl->DataReset();
	m_timer = 0.f;
	startTimer = 0.f;
	errorTimer = 0.f;
	std::random_device rnd;
	int add = rnd() % 100;
	m_recTime = 120 + add;
	m_isTimeout = true;
	m_isEnemyHere = false;
}

void NetPVPMode::Reconnect() {
	printf("recconecting...\n");
	OutputDebugString("reconnecting...\n");
	m_lbl->connect(JString(L"NV") + GETTIMEMS());
	m_isTimeout = false;
	m_isfade = false;
	m_rcuTime = 0;
}

void NetPVPMode::RaiseData() {
	//相手がいない時は何も送信しない
	if (!m_isEnemyHere) return;
	//ロードできてたら相手に伝える
	if (m_dataLoaded) {
		printf("loading enemy datas complete...\n");
		m_lbl->raiseMyLoadingState();
	}

	//相手が自分のデータをロードできていたら送信は行わない
	if (m_lbl->isEnemyLoadedMydata())
		return;

	//Monster情報
	if (m_dataRaiseTimer >= 1 and !m_monsterDataRaised) {
		printf("raise my monster ids...\n");
		RaiseMonsterID();
		m_monsterDataRaised = true;
	}
	//AIファイル
	if (m_dataRaiseTimer >= 2 and !m_monsterAisRaised) {
		printf("raise my ai datas...\n");
		RaiseAiVaData();
		RaiseAiTextData();
		m_monsterAisRaised = true;
	}
	//レート情報
	if (m_dataRaiseTimer >= 3.5 and !m_RateInfoRaised) {
		printf("raise my rating info...\n");
		RaiseRatingData();
		m_RateInfoRaised = true;
	}

	//Timerリセット
	if (m_dataRaiseTimer >= 5) {
		printf("timer reset\n");
		m_monsterDataRaised = false;
		m_monsterAisRaised = false;
		m_RateInfoRaised = false;
		m_dataRaiseTimer = 0.f;
	}
	m_dataRaiseTimer += IGameTime().GetFrameDeltaTime();
}

void NetPVPMode::LoadEnemyData() {
	if (m_dataLoaded) 
		return;
	//Load Enemy Ids
	auto ids = m_lbl->GetEnemyTeamIDs();
	if (ids[0] == -1)
		return;
	for (int i = 0; i < 3; i++) {
		m_enemyId[i] = ids[i];
	}
	//Load Enemy AIs (including va)
	if (m_lbl->isGotEnemyPythonCodes()) {
		m_dataLoaded = true;
	}
}

void NetPVPMode::BattleStart() {
	auto game = NewGO<Game>(0, "Game");
	game->SetRandomPVPMode(m_lbl->GetEnemyRate());
	auto enemyFiles = PythonFileLoad::FilesLoadOnlineEnemy();
	StageSetup::NetworkPvPSetup(m_files, enemyFiles, m_monai, m_moid,m_aimode);
	DeleteGO(this);
}

void NetPVPMode::RaiseAiTextData() {
	if (!m_myPyAIsLoaded) {
		for (int i = 0; i < 3; i++) {
			if (m_aimode[i] != 0) continue;

			char cd[255] = { '\0' };
			GetCurrentDirectoryA(255, cd);
			std::string path = "\\PythonAIs\\";
			path += m_files[i];
			char* cstr = new char[path.size() + 1];
			std::char_traits<char>::copy(cstr, path.c_str(), path.size() + 1);
			strcat(cd, cstr);
			strcat(cd, ".py");
			OutputDebugString("PYTHON CODE RAISED!! PATH IS \n");
			OutputDebugString(cd);
			OutputDebugString("\n");
			delete[] cstr;
			FILE* file;
			fpos_t pos;
			file = fopen(cd, "r");
			fseek(file, 0, SEEK_END);
			fgetpos(file, &pos);
			long size = pos;
			fseek(file, 0, SEEK_SET);
			char text[1024] = { '\0' };
			fread(text, size, 1, file);
			fclose(file);
			OutputDebugString(text);
			m_lbl->SetText(text, i);
			m_myPyAIsLoaded = true;
		}
	}
	m_lbl->raiseMonAIs();
}

void NetPVPMode::RaiseAiVaData() {
	using namespace std;
	using namespace ExitGames::Common;
	if (!m_myVaAIsLoaded){
		auto vaFiles = VisualAiFileLoad::FilesLoad();
		for (int i = 0; i < 3; i++) {
			if (m_aimode[i] == 0) continue;
			char cd[255] = { '\0' };
			GetCurrentDirectoryA(255, cd);
			std::string path = "\\Assets\\VisualAI\\";
			path += vaFiles[m_monai[i]];
			path += ".va";
			char* cstr = new char[path.size() + 1];
			std::char_traits<char>::copy(cstr, path.c_str(), path.size() + 1);
			strcat(cd, cstr);
			delete[] cstr;

			ifstream ifs;
			JString data;
			ifs.open(cd, ios::in | ios::binary);
			if (!ifs)
				OutputDebugString("va open failed\n");
			ifs.seekg(0, fstream::end);
			UINT endpos = ifs.tellg();
			ifs.seekg(0, fstream::beg);
			while (ifs.tellg() != endpos) {
				byte x;
				ifs.read((char*)& x, 1);
				char ss[256];
				sprintf_s(ss, "%02x", x);
				data += ss;
			}
			m_lbl->SetAiMode(m_aimode[i], i);
			m_lbl->SetVisualAiData(data, i);
			m_myVaAIsLoaded = true;
			OutputDebugString("Visual AI Data loaded!! setting lbl...\n");
			OutputDebugString(cd);
			OutputDebugString("\n");
		}
	}
	if (m_lbl->isConect()) {
		m_lbl->raiseVisualAIsData();
	}
}

void NetPVPMode::RaiseRatingData() {
	m_lbl->raiseRating();
}

void NetPVPMode::BackToMenu() {
	//NewGO<NetAISelect>(0);
	//DeleteGO(this);
}

void NetPVPMode::InitUI() {
	m_wallpaper = NewGO<SpriteRender>(0);
	m_wallpaper->Init(L"Assets/Sprite/wallpaper3.dds", 1280.f, 720.f);

	m_cur = NewGO<GameCursor>(0);

	m_returnButton = NewGO<ReturnButton>(0, "rb");
	m_returnButton->init(this, "pvp", m_cur);
	
	//particle
	for (int i = 0; i < m_numParticle; i++) {
		auto s = NewGO<backParticle>(0);
		m_particles.push_back(s);
	}
	//notification font
	m_font = NewGO<FontRender>(2);
	m_font->SetTextType(CFont::en_Japanese);
	m_font->Init(L"対戦相手を検索中", m_waitingFontPos, 0.f, CVector4::White, 1.f, { 1,1 });
	m_font->DrawShadow();
	//other
	m_informationSp = NewGO<SpriteRender>(1);
	m_informationSp->Init(L"Assets/Sprite/hakkou1.dds", 600.f, 100.f);
	m_informationSp->SetPosition(m_informationPos);
}

void NetPVPMode::UiUpdate() {
	//if (m_lbl->isConect()) {
	if (m_lbl->isConect()) {
		m_font->Init(L"対戦相手が見つかりました", m_findFontPos, 0.f, CVector4::White, 1.f, { 1,1 });
	}
	else {
		m_font->Init(L"対戦相手を検索中", m_waitingFontPos, 0.f, CVector4::White, 1.f, { 1,1 });
	}
	if(!m_isfade)
		m_returnButton->UpdateEx<NetAISelect>();
}

void NetPVPMode::CheckDatas() {

	if (m_lbl->CanStartGame()/* or m_dataLoaded and m_lbl->isEnemyAbandoned()*/) {
		if (!m_isfade) {

			m_lbl->raiseMyLoadingState();
			auto eneaimode = m_lbl->GetEnemyAiModes();
			for (int i = 3; i < 6; i++) {
				m_monai[i] = i - 3;
				m_moid[i] = m_enemyId[i - 3];
				m_aimode[i] = eneaimode[i - 3];
			}
			m_isfade = true;
			m_fade->FadeOut();

			auto mf = NewGO<MusicFade>(0);
			auto bgm = FindGO<Sound>("BGM");
			if (bgm != nullptr) {
				mf->init(bgm, 1, 1);
			}
		}
	}

	//敵とつながったか
	if (m_lbl->isConect())
		m_isEnemyHere = true;
	else
		m_isEnemyHere = false;
}

void NetPVPMode::RaiseMonsterID() {
	//モンスターのID
	int ids[3];
	for (int i = 0; i < 3; i++)
		ids[i] = m_moid[i];
	m_lbl->SetTeamMonsterInfo(ids);
	m_lbl->raiseMonData();
	//AIモード
	for (int i = 0; i < 3; i++) {
		m_lbl->SetAiMode(m_aimode[i], i);
	}
}

void NetPVPMode::UpdateTimeOutTimer() {
	//自分がルームに接続中で敵が見つかってない時にタイマーを進める
	if (m_lbl->isJoining() and !m_lbl->isConect()) {
		m_timer += IGameTime().GetFrameDeltaTime();
	}
	if (!m_lbl->isJoining()) {
		//エラーが発生していたらエラータイマーを進める
		errorTimer += IGameTime().GetFrameDeltaTime();
	}
	//敵がいるときはタイムアウト用のタイマーを進めない
	if (m_lbl->isConect())
		m_timer = 0.f;
}

void NetPVPMode::UpdateTimeOutProc() {
	//タイムアウト用のタイマー更新
	UpdateTimeOutTimer();

	//相手が全然見つからない場合は接続しなおす
	if (!m_lbl->CanStartGame() and m_timer > timeout) {
		TimeOut();
	}

	//タイムアウトしてしばらくしたら繋ぎ直してみる
	if (m_recTime == m_rcuTime)
		Reconnect();

	if (m_isTimeout) m_rcuTime++;

	//敵がいなくなってしまったら色々リセット
	if (m_lbl->isEnemyAbandoned() and !m_lbl->CanStartGame() or errorTimer >= 20.f) {
		TimeOut();
	}
}