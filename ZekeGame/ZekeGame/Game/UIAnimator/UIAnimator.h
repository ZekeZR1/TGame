#pragma once

struct sUI
{
	const wchar_t* name = nullptr;
	CVector2 dimensions = { 0,0 };
	CVector3 pos = CVector3::Zero();
	CVector3 scale = CVector3::Zero();
	CQuaternion rot = CQuaternion::Identity();
};

struct UIkeyFrame
{
	int num = 0;
	float time = 0;
	CVector3 pos = {0,0,0};
	CVector3 scale = { 0,0,0 };
	CQuaternion rot = { 0,0,0,1 };
};

class UIAnimator :public GameObject
{
public:
	void loadUI(const wchar_t* path,std::function<SpriteRender*(sUI* ui,bool &isfook)> func);
	void playAnim(const wchar_t* path);

private:
	std::vector<SpriteRender*> m_Sprits;


	bool m_isAnimation = false;
};