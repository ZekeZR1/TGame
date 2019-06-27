#coding: utf-8

import PythonAIs.CppBridge as cb
import SendGame

def Brain(num,team):
	cb.init(num,team)
	mon = cb.GetBuddyLowHPMonster()
	cb.addAction(mon,SendGame.HEAL)
	mon = cb.GetEnemyNeerMonster()
	cb.addAction(mon,SendGame.ESCAPE)
	mon = cb.GetEnemyHighATKMonster()
	cb.addAction(mon,SendGame.FIRE)
	cb.End()	