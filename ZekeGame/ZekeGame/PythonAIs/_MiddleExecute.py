
import importlib

def execute(num,team,file):
    try:
        mod = importlib.import_module(file)
        mod.Brain(num,team)
    except:
        return 0
    return 1
