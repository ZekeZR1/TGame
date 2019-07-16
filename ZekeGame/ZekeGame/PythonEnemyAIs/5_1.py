#coding:utf-8

import PythonAIs.CppBridge as cb

def Brain(num,team):
    cb.init(num,team)
    me = cb.GetMe()
    bc = cb.gameData.buddyCount
    ec = cb.gameData.enemyCount
    n = num-ec
    if n == 0:
        tar = cb.GetEnemyFarMonster()
        if me.MP >= 20:
            cb.SendGame.addAction(tar.num,cb.SendGame.TACKLE)
        cb.SendGame.addAction(tar.num,cb.SendGame.CHASE)
        cb.SendGame.addAction(tar.num,cb.SendGame.ATTACK)
    elif n == 1:
        tar = cb.GetEnemyNeerMonster()
        if me.MP >= 15:
            cb.SendGame.addAction(tar.num,cb.SendGame.CHASE)
            cb.SendGame.addAction(tar.num,cb.SendGame.TACKLE)
        cb.SendGame.addAction(tar.num,cb.SendGame.CHASE)
        cb.SendGame.addAction(tar.num,cb.SendGame.ATTACK)
        pass
    elif n == 2:
        tar = cb.GetEnemyLowHPMonster()
        if me.HP <= 30:
            cb.SendGame.addAction(tar.num,cb.SendGame.DEFENSE)
            cb.SendGame.addAction(tar.num,cb.SendGame.ATTACK)
        else:
            cb.SendGame.addAction(tar.num,cb.SendGame.CHASE)
            cb.SendGame.addAction(tar.num,cb.SendGame.ATTACK)
        pass
    
    cb.End()
