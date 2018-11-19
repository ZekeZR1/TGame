#port CppBridge as cb

print("""
def Brain1():
    ME = cb.gameData.me
    mon = cb.gameData.GetEnemyHighHP()
    
    cb.Chase(mon)
    cb.Atack(mon)
    if ME.HP < 3:
        cb.Leave(mon)
    return cb.actions""")

def Brain(args):
    return 1