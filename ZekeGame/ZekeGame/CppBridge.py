#coding: utf-8
from enum import Enum
import SendGame


def sqrt(v):
    n = 1
    for i in range(32):
        n = (n + v/n)/2
    return n

class Vector3(object):
    def __init__(self,x=0,y=0,z=0):
        self.x = x
        self.y = y
        self.z = z
    def SetVector(self,x,y,z):
        self.x = x
        self.y = y
        self.z = z

    def __add__(self,o):
        result = Vector3()
        result.x = self.x + o.x
        result.y = self.y + o.y
        result.z = self.z + o.z
        return result
    def __sub__(self,o):
        result = Vector3()
        result.x = self.x - o.x
        result.y = self.y - o.y
        result.z = self.z - o.z
        return result

    def Lenght(self):
        r = sqrt(self.x*self.x+self.y*self.y+self.z*self.z)
        return r
        
    def Normalize(self):
        len = Lenght()
        self.x /= len
        self.y /= len
        self.z /= len


class Monster:
    def __init__(self):
        self.position = Vector3()
        self.ID = 0
        self.team = 0
        self.num = 0
        self.HP = 0
        self.MP = 0
        self.state = 0
    def SetPosition(self,x,y,z):
        self.position.SetVector(x,y,z)

class ACTION(Enum):
    Chase = 0
    Atack = 1


class GameData:
    def __init__(self):
        pos = SendGame.GetMyPosition();
        self.me = Monster()
        self.me.SetPosition(pos[0],pos[1],pos[2])
        self.me.HP = SendGame.GetMyHP()
        self.me.MP = SendGame.GetMyMP()
        self.me.num = SendGame.GetMyNum()
        self.me.team = SendGame.GetMyTeam()

        self.buddyCount = SendGame.GetBuddyCount()
        self.enemyCount = SendGame.GetEnemyCount()

        self.Buddy = []
        poss = SendGame.GetAllBuddyPosition()
        nums = SendGame.GetAllBuddyNum()
        for i in range(self.buddyCount-1):
            mon = Monster()
            mon.SetPosition(poss[i][0],poss[i][1],poss[i][2])
            mon.num = nums[i]
            self.Buddy.append(mon)

        self.Enemys = []
        poss = SendGame.GetAllEnemyPosition()
        for i in range(self.enemyCount):
            mon = Monster()
            mon.SetPosition(poss[i][0],poss[i][1],poss[i][2])
            self.Enemys.append(mon)

gameData = GameData()
MonsterUseAction = (
    [ACTION.Chase,ACTION.Atack]
    )
actions = []

def Chase(target):
    for ac in MonsterUseAction[gameData.me.ID]:
        if ac != ACTION.Chase:
            continue
        actions.append([ac,target])

def Atack(target):
    for ac in MonsterUseAction[gameData.me.ID]:
        if ac != ACTION.Atack:
            continue
        actions.append([ac,target])