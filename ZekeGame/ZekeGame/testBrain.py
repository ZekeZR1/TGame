import CppBridge as cb

def Brain():
    ME = cb.gameData.me

    cb.Chase(0)
    return cb.actions