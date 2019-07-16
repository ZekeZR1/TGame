#pragma once

#include "../Fade/Fade.h"
#include "..//GameCursor.h"
//戻るボタン
class ReturnButton :public GameObject
{
public:
	//コンストラクタ
	ReturnButton();

	/*
	初期化
	arg:
		scene:現在のシーン
		name:モどルシーンの名前
		cursor:Кソー
	*/
	void init(GameObject* scene, const char* name, GameCursor* cursor)
	{
		m_scene = scene;
		m_name = name;
		m_cursor = cursor;
	}

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
				auto se = NewGO<Sound>(0);
				se->Init(L"Assets/sound/se/button.wav", false);
				se->Play();
			}
			if (!m_isOver)
			{
				m_isOver = true;
				//m_arrow->Init(L"Assets/sprite/returnArrowLong.dds", m_buttonSize.x, m_buttonSize.y);
			}
		}
		else if (m_isOver)
		{
			m_isOver = false;
			//m_arrow->Init(L"Assets/sprite/returnArrow.dds", m_buttonSize.x, m_buttonSize.y);
		}
		if (m_isOver)
		{
			if (m_bowsca < 1.f)
			{
				m_bowsca += 0.1f;
				m_bow->SetScale({ m_bowsca,1,1 });
				CVector3 bowpos = m_arrowpos;
				bowpos.x -= m_bowsca * 80;
				m_top->SetPosition(bowpos);
			}
		}
		else
		{
			if (m_bowsca > 0.7f)
			{
				m_bowsca -= 0.1f;
				m_bow->SetScale({ m_bowsca,1,1 });
				CVector3 bowpos = m_arrowpos;
				bowpos.x -= m_bowsca * 80;
				m_top->SetPosition(bowpos);
			}
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
	SpriteRender* m_top = nullptr;			//矢じり
	SpriteRender* m_bow = nullptr;			//棒

	CVector3 m_arrowpos = CVector3::Zero();//ya no pos

	CVector2 m_buttonSize = { 384,256 };	//button size
	double m_scale = 0.39024390243902439024390243902439;	//size
	CVector2 m_topsize = CVector2{ 212/2,377/2 };		//yajiri size
	
	CVector2 m_bowsize = CVector2{ 337/2,186/2 };		//bow size
	float m_bowsca = 0.6f;		//bow no scale

	CVector3 m_pos = CVector3::Zero();	//position

	GameObject* m_scene = nullptr;		//戻るシーン
	const char* m_name = nullptr;		//namae
	Fade* m_fade = nullptr;				//fade
	GameCursor* m_cursor = nullptr;		//cursor

	bool m_isOver = false;				//MouseOver～？
	bool m_isClick = false;				//クリックされたか
	bool m_isFade = false;				//ふぁでしてる～？
};