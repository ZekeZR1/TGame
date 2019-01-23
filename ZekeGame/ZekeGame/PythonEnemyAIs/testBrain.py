#coding: utf-8

import PythonAIs.CppBridge as cb

def Brain(MeNum,MeTeam):
    cb.init(MeNum,MeTeam)
    ME = cb.gameData.me
    mon = cb.GetEnemyHighHP()
    
    cb.Chase(mon)
    cb.Atack(mon)
    if ME.HP < 3:
        cb.Leave(mon)
    cb.End()
    #return cb.gameData.tesGetEneNum()
    return 1
    return cb.actions

