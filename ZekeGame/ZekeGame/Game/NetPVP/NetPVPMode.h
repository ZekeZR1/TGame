#pragma once

class Fade;
class MusicFade;

class ModeSelect;
class ExchangeData;
class NetPVPMode :public GameObject
{
public:
	//初期化
	NetPVPMode();

	//初期化。
	void init(std::vector<std::string > files, int monai[3], int moid[3]);

	bool Start() override;
	void Update() override;
	//デストラクタ
	void OnDestroy() override;
private:


	Fade* m_fade = nullptr;				//fade
	MusicFade* m_mscfade = nullptr;		//musicfade
	ModeSelect* m_modesel = nullptr;	//modeselect
	ExchangeData* m_exdata = nullptr;	//ネットでやり取りするときに使うやつ

	std::vector<std::string> m_files;		//pythonファイルの名前
	int m_monai[3] = { 0 };				//モンスターのAI
	int m_moid[3] = { 0 };				//モンスターのID

	bool m_isConect = false;			//繋がっていますか？
};