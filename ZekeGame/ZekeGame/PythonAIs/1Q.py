import CppBridge as cb

def Brain(num,team):
    cb.init(num,team)

    me = cb.GetMe()
    if me.ID == cb.UmataurID:
        mon = cb.FindBuddyMonster(cb.FairyID)
        if mon != None:
            cb.Guardian(mon)
        else:
            pass
        pass
    elif me.ID == cb.FairyID:
        if me.MP >= 5:
            mon = cb.GetBuddyLowHPMonster()
            cb.Recovery(mon)

    cb.End()
    return 1
