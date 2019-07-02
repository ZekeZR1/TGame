#coding:utf-8

import PythonAIs.CppBridge as cb

def Brain(num,team):
    cb.init(num,team)
    me = cb.GetMe()
    tar = cb.GetEnemyHighATKMonster()
    if me.ID == cb.SendGame.Armor:
        if cb.gameData.buddyCount != 1:
            cb.SendGame.addAction(me.num,cb.SendGame.DEF_Buff)
            cb.SendGame.addAction(me.num,cb.SendGame.GUARDIAN)
        else:
            tar = cb.GetEnemyNeerMonster()
            cb.SendGame.addAction(tar.num,cb.SendGame.CHASE)
            cb.SendGame.addAction(tar.num,cb.SendGame.ATTACK)
        pass
    elif me.ID == cb.SendGame.Uma:
        if me.MP >= 20:
            cb.SendGame.addAction(tar.num,cb.SendGame.TACKLE)
        cb.SendGame.addAction(tar.num,cb.SendGame.CHASE)
        cb.SendGame.addAction(tar.num,cb.SendGame.ATTACK)
        pass
    elif me.ID == cb.SendGame.Book:
        cb.SendGame.addAction(tar.num,cb.SendGame.Clear_Stack)
        pass
    

    cb.End()
