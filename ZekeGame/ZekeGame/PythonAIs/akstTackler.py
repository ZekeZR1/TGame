#coding: utf-8

import PythonAIs.CppBridge as game

def Brain(MeNum,MeTeam):
    game.init(MeNum,MeTeam)
    mon = game.GetEnemyNeerMonster()
    me = game.GetMe()
    if me.MP >= 20:
        game.Tackle( mon )
    else:
        game.Chase(mon)
        game.Atack(mon)
    
    game.End()
    #return cb.gameData.tesGetEneNum()
    return 1
    return cb.actions

