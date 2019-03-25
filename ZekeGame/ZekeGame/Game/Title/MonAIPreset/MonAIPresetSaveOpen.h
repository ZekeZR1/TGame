#pragma once

#include "MonAIPresetOpenSuper.h"

class SuperMonsterSelect;
typedef SuperMonsterSelect SMS;


class GameCursor;
class MonAIPresetSaveOpen :public MonAIPresetOpenSuper
{
public:
	MonAIPresetSaveOpen();
	void Execute(int num) override;
private:
};