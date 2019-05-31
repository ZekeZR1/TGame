#pragma once

class ModeSelectBack :public GameObject
{
public:
	ModeSelectBack();
	void OnDestroy();



	enum eMode
	{
		enNone,
		endundeon,
		enpvp,
		ennetpvp,
		enAIedit
	};
	void Dungeon()
	{
		m_mode = endundeon;
	}
	void PVP()
	{
		m_mode = enpvp;
	}
	void NetPVP()
	{
		m_mode = ennetpvp;
	}
	void AIedit()
	{
		m_mode = enAIedit;
	}
private:
	SkinModelRender* m_back = nullptr;	//haikei
	SpriteRender* m_backS = nullptr;	//haikei(sprite)
	eMode m_mode = enNone;				//Ç¢Ç‹ÇÃèÛë‘
	CEffect* m_effect = nullptr;		//effect;
};