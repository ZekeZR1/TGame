#coding: utf-8

import PythonAIs.CppBridge as cb
import SendGame

def Brain(num,team):
	cb.init(num,team)
	mon = cb.GetEnemyHighATKMonster()
	cb.addAction(mon,SendGame.CHASE)
	mon = cb.GetEnemyHighATKMonster()
	cb.addAction(mon,SendGame.ATTACK)
	cb.End()