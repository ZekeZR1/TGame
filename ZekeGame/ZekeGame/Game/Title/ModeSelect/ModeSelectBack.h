#pragma once

class UIAnimator;
class ModeSelectBack :public GameObject
{
public:
	ModeSelectBack();
	void OnDestroy();

	void Update();

	enum eMode
	{
		enNone,
		endundeon,
		enpvp,
		ennetpvp,
		enAIedit
	};

	//切り替え　ダンジョン
	void Dungeon();
	//切り替え　PVP
	void PVP();
	//切り替え　NETPVP
	void NetPVP();
	//切り替え　AIEdhit
	void AIedit();

	//スプライト　ALL　kill
	void delSprits();

	void moveDungeon();
	void movePVP();
	void moveNETPVP();
	void moveAIedit();
private:
	SkinModelRender* m_back = nullptr;	//haikei
	SpriteRender* m_backS = nullptr;	//haikei(sprite)
	eMode m_mode = enNone;				//いまの状態
	CEffect* m_effect = nullptr;		//effect;

	std::vector<SpriteRender*> m_dungeon;//ダンジョンスプライト
	std::vector<SpriteRender*> m_pvp;	//pvpスプライト
	std::vector<SpriteRender*> m_netpvp;//netpvpスプライト
	std::vector<SpriteRender*> m_AIedit;//AIedit sprite

	std::vector<SpriteRender*> m_sprits;//sprite集合体

	UIAnimator* m_uia = nullptr;	//UIAnimator

	bool m_isfirst = false;			//初めてか？

};