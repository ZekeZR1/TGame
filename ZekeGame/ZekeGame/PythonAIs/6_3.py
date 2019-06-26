#coding:utf-8


import CppBridge as cb

def Brain(num,team):
    cb.init(num,team)
    me = cb.GetMe()
    if me.ID == cb.SendGame.Uma:
        if me.num==3:
            if me.MP >= 20:
                tar = cb.GetEnemyLowHPMonster()
                cb.SendGame.addAction(tar.num,cb.SendGame.TACKLE)
        elif me.num == 5:
            if me.MP >= 15:
                tar = cb.GetEnemyHighHPMonster()
                cb.SendGame.addAction(tar.num,cb.SendGame.CHASE)
                cb.SendGame.addAction(tar.num,cb.SendGame.Majinken)
    elif me.ID == cb.SendGame.Book:
        if me.MP >= 20:
            tar = cb.GetEnemyHighHPMonster()
            cb.SendGame.addAction(tar.num,cb.SendGame.Clear_Stack)
        elif me.HP <= 10:
            cb.SendGame.addAction(3,cb.SendGame.DEFENSE)
        cb.SendGame.addAction(3,cb.SendGame.CHASE)
    cb.End()
    
