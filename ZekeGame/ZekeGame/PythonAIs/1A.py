#coding: utf-8

import CppBridge as cb
import SendGame

def Brain(num,team):
	cb.init(num,team)
	mon = cb.GetEnemyNeerMonster()
	cb.addAction(mon,SendGame.FIRE)
	cb.End()