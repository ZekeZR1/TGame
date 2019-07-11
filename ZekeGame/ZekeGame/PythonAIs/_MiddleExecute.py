###PLAYER###
import importlib

def execute(num,team,file):
    try:
        mod = importlib.import_module(file)
        mod.Brain()
    except:
        import sys
        import os
        from datetime import datetime
        import SendGame

        if False:
            path = __file__
            path = path[:path.rfind("\\")] + "/error.log"
            with open(path,"a") as file:
                etuple = sys.exc_info()
                file.write("---ERROR---\n")
                time = datetime.now().strftime('%Y/%m/%d %H:%M:%S')
                file.write(time+"\n")
                file.write("MonsterNum:"+str(num)+"\n")
                file.write("MonsterTeam:"+str(team)+"\n")
                file.write(str(etuple[0])+"\n")
                file.write(str(etuple[1])+"\n")
                file.write(str(etuple[2])+"\n\n")

        SendGame.MMprint("MonsterNum:"+str(num))
        SendGame.MMprint("MonsterTeam:"+str(team))
        SendGame.MMprint(str(etuple[0]))
        SendGame.MMprint(str(etuple[1]))
        SendGame.MMprint(str(etuple[2]))
        return 0
    return 1
