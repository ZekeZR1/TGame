#coding: utf-8

import CppBridge as cb

def Brain(MeNum,MeTeam,f):
    cb.gameData.init(MeNum)
    ME = cb.gameData.me
    mon = cb.gameData.GetEnemyHighHP()
    
    cb.Chase(mon)
    cb.Atack(mon)
    if ME.HP < 3:
        cb.Leave(mon)
    #cb.End()
    #return cb.gameData.tesGetEneNum()
    return cb.actions

