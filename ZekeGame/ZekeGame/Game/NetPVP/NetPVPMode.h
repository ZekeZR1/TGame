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
	//初期化
	NetPVPMode();

	//初期化。
	void init(std::vector<std::string > files, int monai[3], int moid[3],int aimode[3]);

	bool Start() override;
	void Update() override;
	//デストラクタ
	void OnDestroy() override;
private:
	void InitUI();
	void UiUpdate();
	void RaiseData();
	void RaiseRatingData();
	void LoadEnemyData();
	void RaiseAiTextData();
	void RaiseAiVaData();
	void TimeOut();
	void Reconnect();
	bool m_dataRaised = false;
	bool m_dataLoaded = false;
	void BattleStart();
	void BackToMenu();
	Fade* m_fade = nullptr;				//fade
	bool m_isfade = false;
	bool m_isBackFade = false;
	MusicFade* m_mscfade = nullptr;		//musicfade
	ModeSelect* m_modesel = nullptr;	//modeselect
	ExchangeData* m_exdata = nullptr;	//ネットでやり取りするときに使うやつ

	std::vector<std::string> m_files;		//pythonファイルの名前
	int m_monai[6] = { 0 };				//モンスターのAI
	float startTimer = 0;
	float errorTimer = 0;
	int m_visualAiDatas[3][1024];
	int m_aimode[6] = { 0 };
	int m_moid[6] = { 0 };				//モンスターのID
	int m_enemyAi[3] = { 0 };
	int m_enemyId[3] = { 0 };
	bool m_isConect = false;			//繋がっていますか？
	bool m_myPyAIsLoaded = false;
	bool m_myVaAIsLoaded = false;
	bool isRaisedVA = false;
	std::vector<std::string> m_vaFiles;
	float m_timer = 0.f;
	bool m_isTimeout = false;
	int m_recTime = 120;
	int m_rcuTime = 0;
	//UI
	int m_numParticle = 20;
	bool m_isEnemyHere = false;
	std::vector<backParticle*> m_particles;
	SpriteRender* m_informationSp = nullptr;
	CVector3 m_informationPos = { 0.f,300.f,0.f };
	SpriteRender* m_wallpaper = nullptr;
	CVector3 m_bbPos = { -500,-300,0 };
	FontRender* m_font = nullptr;
	ReturnButton* m_returnButton = nullptr;			//戻るボタン
	CVector2 m_waitingFontPos = { -180.f,320.f };
	CVector2 m_findFontPos = { -270.f,320.f };
	//other
	GameCursor* m_cur = nullptr;
	LoadBalancingListener* m_lbl = nullptr;
	int timeout = 100;
};