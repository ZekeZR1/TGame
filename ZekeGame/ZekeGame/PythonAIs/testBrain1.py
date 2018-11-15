import CppBridge as cb

def Brain():
    """test用のAI"""
    cb.gameData.GetBuddyFarMonster()
    cb.gameData.GetBuddyHighHPMonster()
    cb.gameData.GetBuddyNeerMonster()
    cb.gameData.GetEnemyNeerMonster()
    cb.gameData.GetFarMonster()
    cb.gameData.GetHighHPMonster()
    cb.gameData.GetEnemyFarMonster()
    cb.gameData.GetNeerMonster()
    return cb.actions