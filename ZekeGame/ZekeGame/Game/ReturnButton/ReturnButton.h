#pragma once

#include "../Fade/Fade.h"
class GameCursor;
//戻るボタン
class ReturnButton :public GameObject
{
public:
	//コンストラクタ
	ReturnButton();

	//戻りたいシーン
	void SetScene(GameObject* scene);

	//名前をセットする
	void setName(const char* name)
	{
		m_name = name;
	}

	//デストラクタ
	void OnDestroy() override;

	//更新
	template<class T>
	void UpdateEx()
	{
		if (m_isFade)
		{
			if (m_fade->isFadeStop())
			{
				NewGO<T>(0, m_name);
				DeleteGO(this);
				DeleteGO(m_scene);
			}
		}
		m_button->SetCollisionTarget(m_cursor->GetCursor());
		if (m_button->isCollidingTarget())
		{
			if (Mouse::isTrigger(enLeftClick))
			{
				m_isFade = true;
				m_fade->FadeOut();
			}
			if (!m_isOver)
			{
				m_isOver = true;
				m_arrow->Init(L"Assets/sprite/returnArrowLong.dds", m_buttonSize.x, m_buttonSize.y);
			}
		}
		else if (m_isOver)
		{
			m_isOver = false;
			m_arrow->Init(L"Assets/sprite/returnArrow.dds", m_buttonSize.x, m_buttonSize.y);
		}
	}

	//戻る
	//GameObject* Return();


	//クリックされたか
	bool isClick()
	{
		return m_isClick;
	}

	//ふぁでしてる～？
	bool isFade()
	{
		return m_isFade;
	}
private:
	SpriteRender* m_button = nullptr;		//button
	SpriteRender* m_arrow = nullptr;		//矢印

	CVector2 m_buttonSize = { 384,256 };	//button size

	CVector3 m_pos = CVector3::Zero();	//position

	GameObject* m_scene = nullptr;		//戻るシーン
	const char* m_name = nullptr;		//namae
	Fade* m_fade = nullptr;				//fade
	GameCursor* m_cursor = nullptr;		//cursor

	bool m_isOver = false;				//MouseOver～？
	bool m_isClick = false;				//クリックされたか
	bool m_isFade = false;				//ふぁでしてる～？
};