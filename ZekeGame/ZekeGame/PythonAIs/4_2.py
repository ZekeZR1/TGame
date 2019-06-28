#coding:utf-8

import CppBridge as cb

def Brain(num,team):
    cb.init()
    me = cb.GetMe()
    tar = GetEnemyLowHPMonster()
    if me.ID == cb.SendGame.Yose:
        cb.SendGame.addAction(tar.num,cb.SendGame.FIRE)
        pass
    elif me.ID == cb.SendGame.Armor:
        cb.SendGame.addAction(tar.num,cb.SendGame.GUARDIAN)
        pass
    elif me.ID == cb.SendGame.Uma:
        cb.SendGame.addAction(tar.num,cb.SendGame.TACKLE)
        pass
    
    cb.End()
