#coding:utf-8

import PythonAIs.CppBridge as cb
import SendGame

def Brain(num,team):
    cb.init(num,team)
    me = cb.GetMe()
    if me.ID == cb.SendGame.Yose:
        tar = cb.GetEnemyHighHPMonster()
        cb.SendGame.addAction(tar.num,cb.SendGame.FIRE)
        pass
    elif me.ID == cb.SendGame.Uma:
        tar = cb.GetEnemyLowHPMonster()
        if me.MP >= 20:
            cb.SendGame.addAction(tar.num,cb.SendGame.TACKLE)
        cb.SendGame.addAction(tar.num,cb.SendGame.CHASE)
        cb.SendGame.addAction(tar.num,cb.SendGame.ATTACK)
        pass

    cb.End()
