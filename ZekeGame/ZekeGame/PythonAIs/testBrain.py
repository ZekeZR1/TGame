#coding: utf-8

import CppBridge as cb

def Brain(MeNum,MeTeam,f):
    cb.gameData.init(MeNum,MeTeam)
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

