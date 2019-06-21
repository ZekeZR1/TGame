#include "stdafx.h"
#include "Game.h"
#include "GameCamera3D.h"
#include "GameCamera2D.h"
#include "Title/ModeSelect.h"
#include "Fade/Fade.h"

#include "../TestScene.h"
#include "../Game/Dungeon/MonsterDrop.h"

#include "UIAnimator/UIAnimator.h"
#include "AIEdit/ShowMonsters.h"
#include "Dungeon/MonsterDrop.h"
int WINAPI wWinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPWSTR lpCmdLine,
	int nCmdShow) {
	//Initialize
	Engine::IEngine().Init(hInstance, hPrevInstance, lpCmdLine, nCmdShow);

	NewGO<Fade>(0, "fade");
	NewGO<GameCamera3D>(0, "cam3d");
	NewGO<GameCamera2D>(0, "cam2d");
	NewGO<ModeSelect>(0, "modesel");
	//NewGO<MonsterDrop>(0);
	g_physics.SetDebugDraw(false);

	/*UIAnimator* UIA = NewGO<UIAnimator>(0, "uia");
	UIA->loadUI(L"Assets/UI/modesel_aiedit.uip", [&](sUI* ui, bool isfook)->SpriteRender *
	{
		SpriteRender* sp = NewGO<SpriteRender>(0, "sp");
		return sp;
	});
	UIA->playAnim(L"Assets/UI/modesel_aiedit2.uim");
	UIA->setLoopFlag(true);*/

	/*AnimationClip anim[3];
	anim[0].Load(L"Assets/modelData/shell/hotate_idle.tka");
	anim[0].SetLoopFlag(true);
	SkinModelRender* sr = NewGO<SkinModelRender>(0, "sr");
	sr->Init(L"Assets/modelData/hotate.cmo",anim,1);
	sr->Init(L"Assets/modelData/si_bug.cmo",nullptr,0);
	sr->SetScale(CVector3{ 10,10,10 } / 100);
	sr->SetScale(CVector3::One()/2);*/


	SkinModelRender* sm = NewGO<SkinModelRender>(0, "sm");
	sm->Init(L"Assets/modelData/tesEnemy3.cmo");
	sm->SetPosition(CVector3::Zero());
	sm->SetScale({ 0.001f,0.001f,0.001f });

	//MainRoop
	Engine::IEngine().GameRoop();
	//Release
	Engine::IEngine().Final();
}
