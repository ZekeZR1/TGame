#pragma once
enum enMouseEve {
	enLeftClick,
	enMiddleClick,
	enRightClick,
	enNumMouseEve
	//TODO : マウスイベントのenNotchUp down追加してtrigger取れるようにする
};
namespace Mouse {
	int GetMouseNotch();
	void UpdateMouseInput();
	bool isTrigger(enMouseEve);
	bool isPress(enMouseEve);
	CVector3 GetCursorPos();
}
