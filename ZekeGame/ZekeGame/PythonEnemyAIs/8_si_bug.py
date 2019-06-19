#coding: utf-8

import CppBridge as cb

def Brain(num,team):
	cb.init(num,team)
	mon = cb.GetEnemyNeerMonster()
	cb.addAction(mon,0)
	mon = cb.GetBuddyNeerMonster()
	cb.addAction(mon,22)
	cb.End()