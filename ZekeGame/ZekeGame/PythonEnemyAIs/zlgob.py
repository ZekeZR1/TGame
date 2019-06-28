#coding: utf-8

import PythonAIs.CppBridge as cb
import SendGame

def Brain(num,team):
	cb.init(num,team)
	mon = cb.GetEnemyLowHPMonster()
	cb.addAction(mon,SendGame.CHASE)
	mon = cb.GetEnemyNeerMonster()
	cb.addAction(mon,SendGame.ATTACK)
	mon = cb.GetEnemyNeerMonster()
	cb.addAction(mon,SendGame.Poison)
	mon = cb.GetEnemyHighATKMonster()
	cb.addAction(mon,SendGame.ESCAPE)
	cb.End()