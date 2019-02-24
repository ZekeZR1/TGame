import CppBridge as cb

def Brain(num,team):
    cb.init(num,team)

    me = cb.GetMe()
    if me.ID == cb.UmataurID:
        mon = cb.GetEnemyNeerMonster()
        if me.MP >= 20:
            cb.Tackle( mon )
        else:
            cb.Chase(mon)
            cb.Atack(mon)
    elif me.ID == cb.FairyID:
        if me.MP >= 20:
            mon = cb.GetBuddyLowHPMonster()
            if cb.GetPercentHP(mon) < 0.4:
                cb.Recovery(mon)
            else:
                mon = cb.GetEnemyLowHPMonster()
                cb.Fire(mon)
        mon = cb.GetEnemyNeerMonster()
        cb.Leave(mon)

    cb.End()
    return 1
