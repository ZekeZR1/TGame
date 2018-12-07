#include "stdafx.h"
#include "Mouse.h"

namespace Mouse {

	bool trigger[enNumMouseEve] = { false };
	bool prePress[enNumMouseEve] = { false };
	bool press[enNumMouseEve] = { false };
	CVector3 cursorpos = CVector3::Zero();

	void UpdateMouseInput() {
		POINT pt;
		GetCursorPos(&pt);
		cursorpos.x = float(pt.x);
		cursorpos.y = float(pt.y);
		ShowCursor(FALSE);
		//左トリガー入力判定。
		if (mEve[0] != 0) {
			trigger[enLeftClick] = 1 ^ press[enLeftClick];
			press[enLeftClick] = 1;
		}
		else {
			trigger[enLeftClick] = 0;
			press[enLeftClick] = 0;
		}
		//右トリガー
		if (mEve[2] != 0) {
			trigger[enRightClick] = 1 ^ press[enRightClick];
			press[enRightClick] = 1;
		}
		else {
			trigger[enRightClick] = 0;
			press[enRightClick] = 0;
		}
		//ミドルトリガー
		if (mEve[1] != 0) {
			trigger[enMiddleClick] = 1 ^ press[enMiddleClick];
			press[enMiddleClick] = 1;
		}
		else {
			trigger[enMiddleClick] = 0;
			press[enMiddleClick] = 0;
		}
	}

	CVector3 GetCursorPos() {
		return cursorpos;
	}
	int GetMouseNotch() {
		int nn = notch;
		notch = 0;
		return nn;
	}

	bool isTrigger(enMouseEve eve) {
		return trigger[eve];
	}

	bool isPress(enMouseEve eve) {
		return mEve[eve];
	}
}