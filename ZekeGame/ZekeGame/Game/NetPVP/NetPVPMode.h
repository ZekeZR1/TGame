#pragma once

class Fade;
class MusicFade;
class LoadBalancingListener;
class ModeSelect;
class ExchangeData;
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
	void RaiseData();
	void RaiseRatingData();
	void LoadEnemyData();
	void RaiseAiTextData();
	void RaiseAiVaData();
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
	int m_visualAiDatas[3][1024];
	int m_aimode[6] = { 0 };
	int m_moid[6] = { 0 };				//モンスターのID
	int m_enemyAi[3] = { 0 };
	int m_enemyId[3] = { 0 };
	bool m_isConect = false;			//繋がっていますか？
	bool m_myPyAIsLoaded = false;
	bool m_myVaAIsLoaded = false;
	std::vector<std::string> m_vaFiles;
	//UI
	SpriteRender* m_informationSp;
	CVector3 m_informationPos = { 0.f,300.f,0.f };
	LoadBalancingListener* m_lbl = nullptr;
};