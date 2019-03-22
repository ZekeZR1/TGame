#pragma once



class MonAIPresetIcon :public GameObject
{
public:
	//Start
	bool Start();

	//Update
	void Update();
private:
	SpriteRender* m_Icon = nullptr;		//きっとモンスターの画像
	FontRender* m_font = nullptr;		//pythonのを表示するための
	
	int m_pre = 0;						//プリセットの番号
	int m_num = 0;						//何番目か。

	CVector3 m_pos = CVector3::Zero();	//
};