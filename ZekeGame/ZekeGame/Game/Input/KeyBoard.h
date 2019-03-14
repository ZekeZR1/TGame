#pragma once

enum KeyboardEve
{
	enEnter = 0x0D,
	enBackSpace = 0x08,
};

namespace Keyboard
{
	//入力されたキーに対応するcharを返す。
	char GetKeyChar();

	//指定したキーが入力されているか。
	//arg:
	//	ke: キーの指定
	bool isTrriger(KeyboardEve ke);
}