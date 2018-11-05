#pragma once

class MonsterAI
{
public:

	virtual void execute() {};
	enum Pattern
	{
		pat_Move,
		pat_Atack,
		pat_Defence,
	};
protected:
	Pattern m_pattern;
	std::vector<Pattern> m_patterns;
};