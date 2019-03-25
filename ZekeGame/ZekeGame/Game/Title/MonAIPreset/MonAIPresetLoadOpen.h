#pragma once

#include "MonAIPresetOpenSuper.h"

class SuperMonsterSelect;
typedef SuperMonsterSelect SMS;


class GameCursor;
class MonAIPresetLoadOpen :public MonAIPresetOpenSuper
{
public:
	MonAIPresetLoadOpen();
	void Execute(int num) override;
private:
};