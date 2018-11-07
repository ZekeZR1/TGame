#include "stdafx.h"
#include "TestListener.h"

int EG_kbhit()
{
	int res = _kbhit();
	if (res)
		_getch();
	return res;
}

TestListener::TestListener()
{
}


TestListener::~TestListener()
{
}

void TestListener::writeString(const ExitGames::Common::JString& str)
{
	if (lastString != str)
		std::wcout << (lastString = str) << std::endl;
}

bool TestListener::anyKeyPressed() const
{
	return EG_kbhit() != 0;
}

void TestListener::onLibClosed()
{
	writeString(L"- -Press any key to quit- ------------------\n");
	while (!anyKeyPressed());
}