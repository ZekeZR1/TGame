import PythonAIs.CppBridge as cb

def Brain(num,team):
    """test用のAI"""
    cb.init(num,team)
    cb.gameData.GetBuddyFarMonster()
    cb.gameData.GetBuddyHighHPMonster()
    cb.gameData.GetBuddyNeerMonster()
    cb.gameData.GetEnemyNeerMonster()
    cb.gameData.GetFarMonster()
    cb.gameData.GetHighHPMonster()
    cb.gameData.GetEnemyFarMonster()
    cb.gameData.GetNeerMonster()
    cb.End()
    return 0
