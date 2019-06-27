#coding:utf-8

import CppBridge as cb

def Brain(num,team):
    cb.init(num,team)
    me = cb.GetMe()
    tar = cb.GetEnemyNeerMonster()
    cb.SendGame.addAction(tar.num,cb.SendGame.CHASE)
    cb.SendGame.addAction(tar.num,cb.SendGame.Kamikaze)

    cb.End()
