#coding:utf-8

import CppBridge as cb

def Brain(num,team):
    cb.init(num,team)
    me = cb.GetMe()
    tar = cb.GetEnemyNeerMonster()
    if me.ID == cb.SendGame.Book:
        cb.SendGame.addAction(tar.num,cb.SendGame.Clear_Stack)
        pass
    elif me.ID == cb.SendGame.Kikyo:
        if me.MP >= 40:
            cb.SendGame.addAction(tar.num,cb.SendGame.MP_Heal)
        cb.SendGame.addAction(tar.num,cb.SendGame.SUPER_BEAM)
        pass
    cb.End()
