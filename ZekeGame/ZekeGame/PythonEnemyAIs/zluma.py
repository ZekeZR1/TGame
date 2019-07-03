#coding: utf-8

import PythonAIs.CppBridge as cb
import SendGame

def Brain(num,team):
	cb.init(num,team)
	mon = cb.FindEnemyMonster(cb.SendGame.Book)
	if mon != None:
		cb.addAction(mon,SendGame.TACKLE)
	else:
		mon = cb.GetEnemyHighATKMonster()
		cb.addAction(mon,SendGame.TACKLE)
	mon = cb.GetEnemyNeerMonster()
	cb.addAction(mon,SendGame.CHASE)
	mon = cb.GetEnemyNeerMonster()
	cb.addAction(mon,SendGame.Majinken)
	mon = cb.GetEnemyNeerMonster()
	cb.addAction(mon,SendGame.ATTACK)
	cb.End()
