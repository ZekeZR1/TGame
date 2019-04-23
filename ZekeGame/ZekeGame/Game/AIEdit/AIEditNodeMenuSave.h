#pragma once

class AIEditNodeProcess;
class AIEditNodeMenu;
class AIEditNodeSelectButtons;
class AIEditNodeMenuSave :public GameObject
{

public:

	~AIEditNodeMenuSave();

	//デストラクタ
	void OnDestroy() override;

	void Awake() override;
	bool Start();
	void Update();
	void Confirmation();

	//保存するブロックが選択されたとき実行される。
	void AISelected();

	//確認の時の処理
	void confProc();

	//パレットの初期化
	void PaletteInit();

	//パレットの処理
	void PaletteProc();

private:

	int button = 2;
	bool click = false;   //選択したらtrueになる。
	bool clickyes = false;  //はいを選択したらtrueになる。
	bool stop = false;

	std::vector<SpriteRender*> sp;
	std::vector<SpriteRender*> m_buttons;
	SpriteRender* m_spriteRender = nullptr;
	SpriteRender* m_spriteRender2 = nullptr;
	SpriteRender* m_spriteRender3 = nullptr;
	std::vector<FontRender*> m_fonts;
	FontRender* m_fonts2 = nullptr;
	FontRender* m_fonts3 = nullptr;
	FontRender* m_fonts4 = nullptr;

	GameCursor* m_gamecursor = nullptr;
	
	AIEditNodeMenu* m_aieditnodemenu = nullptr;
	AIEditNodeProcess* m_aieditnodeprocess = nullptr;
	AIEditNodeSelectButtons* m_aieditselectbuttons = nullptr;

	CVector3 cursorpos = CVector3::Zero();

	CVector3 confpos = CVector3::Zero();
	CVector3 m_positionselect = CVector3::Zero();
	CVector3 m_positionselect2 = CVector3::Zero();
	CVector3 m_Confirmationposition = CVector3::Zero();
	CVector2 m_fontpos = CVector2::Zero();
	CVector2 m_fontpos2 = CVector2::Zero();
	CVector2 m_fontpos3 = CVector2::Zero();


	SpriteRender* m_back = nullptr;			//後ろのやつ
	std::vector<SpriteRender*> m_buttonsF;	//ボタン
	std::vector<FontRender*> m_fontsF;		//ボタンのフォント

	SpriteRender* m_close = nullptr;		//閉じるボタン
	FontRender* m_cfont = nullptr;			//閉じるのフォント

	FontRender* m_head = nullptr;			//見出し

	bool m_isSelected = false;				//選択されたのか？
	int m_SelectBlock = 0;					//選択されたブロック


	SpriteRender* m_backC = nullptr;		//パレットの背景
	std::vector<SpriteRender*> m_palette;	//パレットの色
	FontRender* m_headC = nullptr;			//パレットの見出し
	enum enColor
	{
		enRed,
		enBlu,
		enYel,
		enWhi
	};
	int m_selCol = enRed;					//パレットで選択した色
	bool m_isColSel = false;				//パレットで色を選択したのか？

};