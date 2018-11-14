import CppBridge as cb

def Brain():
    GD = cb.gameData
    fm = GD.GetBuddyNeerMonster()
    cb.Chase(fm)
    fm = GD.GetBuddyFarMonster()
    cb.Chase(fm)
    return cb.actions