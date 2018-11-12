import CppBridge as cb

def Brain():
    GD = cb.gameData
    fm = GD.GetBuddyNeerMonster()
    cb.Chase(fm.num)
    fm = GD.GetBuddyFarMonster()
    cb.Chase(fm.num)
    return cb.actions