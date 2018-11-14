import CppBridge as cb

def Brain():
    ME = cb.gameData.me
    mon = cb.gameData.GetEnemyHighHP()
    cb.Chase(mon)
    cb.Atack(mon)
    return cb.actions