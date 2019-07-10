#pragma once

class Fade;
class MusicFade;
class LoadBalancingListener;
class ModeSelect;
class ExchangeData;
class backParticle;
class GameCursor;
class ReturnButton;

class NetPVPMode :public GameObject
{
public:
	NetPVPMode();
	void init(std::vector<std::string > files, int monai[3], int moid[3],int aimode[3]);
	bool Start() override;
	void Update() override;
	void OnDestroy() override;
private:

	//Scene遷移
	void BattleStart();
	void BackToMenu();
	//Fade
	Fade* m_fade = nullptr;
	bool m_isfade = false;

	//Ai Data
	std::vector<std::string> m_files;		//pythonファイルの名前
	int m_aimode[6] = { 0 };		//PythonAIかVisualAiを識別する物
	int m_monai[6] = { 0 };				//モンスターのAI
	int m_moid[6] = { 0 };				//モンスターのID
	int m_enemyAi[3] = { 0 };		//敵のモンスターのAI
	int m_enemyId[3] = { 0 };		//敵のモンスターのID

	//通信
	LoadBalancingListener* m_lbl = nullptr;
	void RaiseData();
	void RaiseRatingData();
	void RaiseMonsterID();
	void RaiseAiTextData();
	void RaiseAiVaData();
	void LoadEnemyData();
	void CheckDatas();
	bool m_dataLoaded = false;		//相手のデータを読み込み済みか
	//データ送信状況管理
	bool m_monsterDataRaised = false;
	bool m_monsterAisRaised = false;
	bool m_RateInfoRaised = false;
	float m_dataRaiseTimer = 0.f;		//データ送信のインターバル用タイマー
	//送信用情報読み込み状態
	bool m_myPyAIsLoaded = false;
	bool m_myVaAIsLoaded = false;

	//TimeOut
	void TimeOut();
	void Reconnect();
	void UpdateTimeOutTimer();
	void UpdateTimeOutProc();
	bool m_isTimeout = false;
	int timeout = 100;
	float m_timer = 0.f;		//タイムアウト用のタイマー
	int m_recTime = 120; //再接続するまでに待つ時間(frame)
	int m_rcuTime = 0;
	float startTimer = 0;
	float errorTimer = 0;

	//UI
	void InitUI();
	void UiUpdate();
	int m_numParticle = 20;
	bool m_isEnemyHere = false;
	GameCursor* m_cur = nullptr;
	FontRender* m_font = nullptr;
	CVector3 m_bbPos = { -500,-300,0 };
	SpriteRender* m_wallpaper = nullptr;
	std::vector<backParticle*> m_particles;
	ReturnButton* m_returnButton = nullptr;
	CVector2 m_findFontPos = { -270.f,320.f };
	SpriteRender* m_informationSp = nullptr;
	CVector3 m_informationPos = { 0.f,300.f,0.f };
	CVector2 m_waitingFontPos = { -180.f,320.f };
};