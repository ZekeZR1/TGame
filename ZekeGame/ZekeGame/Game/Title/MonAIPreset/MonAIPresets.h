#pragma once

class MonAIPresetOpenSuper;
typedef MonAIPresetOpenSuper MAPopen;
class MonAIPresetIcons;

class GameCursor;
class MonAIPresets :public GameObject
{
public:
	void OnDestroy() override;
	//Start
	bool Start();
	
	//initialize function
	void init(MAPopen* mapopen,GameCursor* cur);

	//Update
	void Update();

	//クリックされますたんぐたいさ。
	bool IsClick()
	{
		return m_isClick;
	}

	//何がクリックされたのかな？
	int GetClickNum()
	{
		return m_clickNum;
	}
private:
	MonAIPresetIcons* m_icons[6] = { nullptr };	//激うま！！icon６個詰めパック
	SpriteRender* m_back = nullptr;				//後ろのやつ
	SpriteRender* m_dummy = nullptr;			//後ろのやつのダミー

	MAPopen* m_mapopen = nullptr;				//このクラスを目覚めさせし者 
	GameCursor* m_cursor = nullptr;				//カーソル

	bool m_isClick = false;						//クリクリクリック。
	int m_clickNum = 999;						//クリックされたプリセットの番号

	
};