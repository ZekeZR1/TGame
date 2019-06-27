#coding: utf-8

import PythonAIs.CppBridge as cb

def Brain(MeNum,MeTeam):
    cb.init(MeNum,MeTeam)
    me = cb.gameData.me
    mon = cb.GetEnemyHighHP()
    
    cb.Chase(mon)
    cb.Atack(mon)
    
    if cb.GetMePercentHP() <= 0.3:
        cb.Leave(mon)
    
    cb.End()