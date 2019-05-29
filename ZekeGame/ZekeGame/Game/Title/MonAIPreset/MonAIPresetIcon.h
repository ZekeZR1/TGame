#pragma once



class MonAIPresetIcon :public GameObject
{
public:
	void OnDestroy() override;
	//デストラクタ
	~MonAIPresetIcon();

	//Start
	bool Start();

	//初期化関数
	//args:
	//	monID: モンスターのID
	//	pyInd: pythonの番号
	void init(int monID,const wchar_t* pypath,CVector3 pos);

	void Setpos(CVector3 pos);
	void Setrot(float rot,CVector3 pos);

	void UpdateAIMON(int monID, const wchar_t* pypath);
	//Update
	void Update();
private:
	SpriteRender* m_Icon = nullptr;		//きっとモンスターの画像
	FontRender* m_font = nullptr;		//pythonのを表示するための

	int m_monID = 0;					//モンスターのID
	int m_pyInd = 0;					//pythonの番号

	int m_pre = 0;						//プリセットの番号
	int m_num = 0;						//何番目か。

	CVector3 m_pos = CVector3::Zero();	//position


};