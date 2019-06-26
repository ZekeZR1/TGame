#coding: utf-8

import PythonAIs.CppBridge as game

def Brain(MeNum,MeTeam):
    game.init(MeNum,MeTeam)
    mon = game.GetEnemyHighHP()


    game.Tackle( mon )
    
    game.End()
    #return cb.gameData.tesGetEneNum()
    return 1
    return cb.actions

