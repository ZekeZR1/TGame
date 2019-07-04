#coding:utf-8


import PythonAIs.CppBridge as cb

def Brain(num,team):
    cb.init(num,team)
    me = cb.GetMe()
    if me.ID == cb.SendGame.Uma:
        tar = cb.GetEnemyNeerMonster()
        if me.MP >= 20:
            cb.SendGame.addAction(tar.num,cb.SendGame.TACKLE)
        elif me.MP >= 15:
            cb.SendGame.addAction(tar.num,cb.SendGame.CHASE)
            cb.SendGame.addAction(tar.num,cb.SendGame.Majinken)
        cb.SendGame.addAction(tar.num,cb.SendGame.CHASE)
        cb.SendGame.addAction(tar.num,cb.SendGame.ATTACK)

    elif me.ID == cb.SendGame.Book:
        if me.MP >= 20:
            tar = cb.GetEnemyFarMonster()
            cb.SendGame.addAction(tar.num,cb.SendGame.Clear_Stack)
        elif me.HP <= 10:
            cb.SendGame.addAction(0,cb.SendGame.DEFENSE)
        if len(cb.gameData.Buddy) > 1:
            cb.SendGame.addAction(3,cb.SendGame.CHASE)
        else:
            cb.SendGame.addAction(tar.num,cb.SendGame.CHASE)
            cb.SendGame.addAction(tar.num,cb.SendGame.ATTACK)
    cb.End()
    
