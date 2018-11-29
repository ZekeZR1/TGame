#from multiprocessing import Process
#import threading
from enum import IntEnum
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

    def copy(self):
        nmon = Monster()
        nmon.position = self.position
        nmon.ID = self.ID
        nmon.team = self.team
        nmon.num = self.num
        nmon.HP = self.HP
        nmon.MP = self.MP
        nmon.state = self.state
        return nmon

class ACTION(IntEnum):
    Chase = 0
    Atack = 1
    Leave = 2

class GameData:
    def fuck__init__(self):
        self.me = Monster()
        pos = SendGame.GetMyPosition();
        self.me.SetPosition(pos[0],pos[1],pos[2])
        self.me.HP = SendGame.GetMyHP()
        self.me.MP = SendGame.GetMyMP()
        self.me.num = SendGame.GetMyNum()
        self.me.team = SendGame.GetMyTeam()

        self.buddyCount = SendGame.GetBuddyCount()
        self.enemyCount = SendGame.GetEnemyCount()

        self.Buddy = []
        #poss = SendGame.GetAllBuddyPosition()
        #nums = SendGame.GetAllBuddyNum()
        datas = SendGame.GetAllBuddyData()
        #for i in range(self.buddyCount-1):
        for i in range(self.buddyCount):
            mon = Monster()
            #mon.SetPosition(poss[i][0],poss[i][1],poss[i][2])
            #mon.num = nums[i]
            mon.ID = datas[i][0]
            mon.num = datas[i][1]
            mon.team = datas[i][2]
            mon.HP = datas[i][3]
            mon.MP = datas[i][4]
            
            pos = datas[i][5]
            mon.SetPosition(pos[0],pos[1],pos[2])

            self.Buddy.append(mon)

        self.Enemys = []
        poss = SendGame.GetAllEnemyPosition()
        nums = SendGame.GetAllEnemyNum()
        HPs = SendGame.GetAllEnemyHP()
        for i in range(self.enemyCount):
            mon = Monster()
            mon.SetPosition(poss[i][0],poss[i][1],poss[i][2])
            mon.num = nums[i]
            mon.HP = HPs[i]
            self.Enemys.append(mon)

    def init(self,num,team):
        """
        ゲームデータの初期化
        必ず最初に使いましょう。
        """
        self.buddyCount = SendGame.GetBuddyCount()
        self.enemyCount = SendGame.GetEnemyCount()

        self.Buddy = []
        datas = SendGame.GetAllBuddyData(team)
        for i in range(self.buddyCount):
            mon = Monster()
            mon.ID = datas[i][0]
            mon.num = datas[i][1]
            mon.team = datas[i][2]
            mon.HP = datas[i][3]
            mon.MP = datas[i][4]
            
            pos = datas[i][5]
            mon.SetPosition(pos[0],pos[1],pos[2])

            self.Buddy.append(mon)

        self.Enemys = []
        datas = SendGame.GetAllEnemyData(team)
        for i in range(self.enemyCount):
            mon = Monster()
            mon.ID = datas[i][0]
            mon.num = datas[i][1]
            mon.team = datas[i][2]
            mon.HP = datas[i][3]
            mon.MP = datas[i][4]
            
            pos = datas[i][5]
            mon.SetPosition(pos[0],pos[1],pos[2])

            self.Enemys.append(mon)

        mm = None
        for i in range(len(self.Buddy)):
            mon = self.Buddy[i]
            if mon.num == num:
                mm = mon.copy()
                del self.Buddy[i]
                break
        if mm == None:
            return
        self.me = Monster()
        self.me.ID = mm.ID
        self.me.position = mm.position
        self.me.HP = mm.HP
        self.me.MP = mm.MP
        self.me.num = mm.num
        self.me.team = mm.team
        self.me.state = mm.state

        
    def tesGetEneNum():
        return SendGame.GetAllEnemyNum()

    def GetFarMonster(self):
        farmon = None
        farlen = 0;
        for mon in self.Buddy:
            len = Vector3.Lenght(self.me.position - mon.position)
            if len > farlen or farmon == None:
                farlen = len
                farmon = mon
        for mon in self.Enemys:
            len = Vector3.Lenght(self.me.position - mon.position)
            if len > farlen or farmon == None:
                farlen = len
                farmon = mon
        return farmon

    def GetNeerMonster(self):
        neermon = None
        neerlen = 999999999999999999999999999999
        for mon in self.Buddy:
            len = Vector3.Lenght(self.me.position - mon.position)
            if len < neerlen or neermon == None:
                neerlen = len
                neermon = mon
        for mon in self.Enemys:
            len = Vector3.Lenght(self.me.position - mon.position)
            if len < neerlen or neermon == None:
                neerlen = len
                neermon = mon
        return neermon

    def GetBuddyFarMonster(self):
        farmon = None
        farlen = 0;
        for mon in self.Buddy:
            len = Vector3.Lenght(self.me.position - mon.position)
            if len > farlen or farmon == None:
                farlen = len
                farmon = mon
        return farmon

    def GetEnemyFarMonster(self):
        farmon = None
        farlen = 0
        for mon in self.Enemys:
            len = Vector3.Lenght(self.me.position - mon.position)
            if len > farlen or farlen == None:
                farlen = len
                farmon = mon
        return farmon

    def GetBuddyNeerMonster(self):
        neermon = None
        neerlen = 999999999999999999999999999999
        for mon in self.Buddy:
            len = Vector3.Lenght(self.me.position - mon.position)
            if len < neerlen or neermon == None:
                neerlen = len
                neermon = mon
        return neermon

    def GetEnemyNeerMonster(self):
        neermon = None
        neerlen = 999999999999999999999999999999
        for mon in self.Enemys:
            len = Vector3.Lenght(self.me.position - mon.position)
            if len < neerlen or neermon == None:
                neerlen = len
                neermon = mon
        return neermon

    def GetHighHPMonster(self):
        """#一番HPの高いモンスターを返します"""
        himon = None
        for mon in self.Buddy:
            if himon == None:
                himon = mon
            elif himon.HP < mon.HP:
                himon = mon
        for mon in self.Enemys:
            if himon == None:
                himon = mon
            elif himon.HP < mon.HP:
                himon = mon
        return himon

    def GetBuddyHighHPMonster(self):
        """#一番HPの高い仲間のモンスターを返します"""
        himon = None
        for mon in self.Buddy:
            if himon == None or himon.HP < mon.HP:
                himon = mon
        return himon

    def GetEnemyHighHP(self):
        """#一番HPの高い敵のモンスターを返します"""
        himon = None
        for mon in self.Enemys:
            if himon == None or himon.HP < mon.HP:
                himon = mon
        return himon


gameData = GameData()

MonsterUseAction = [
    [ACTION.Chase,ACTION.Atack,ACTION.Leave],
    [ACTION.Chase,ACTION.Atack]
    ]

actions = []


def addAction(target,action):
    """モジュール外から使わないでね!"""
    if len(actions) >= 5 or target == None:
        return
    for ac in MonsterUseAction[gameData.me.ID]:
        if ac == action:
            actions.append([int(action),target.num])
            break

def Chase(target):
    addAction(target,ACTION.Chase)

def Atack(target):
    addAction(target,ACTION.Atack)

def Leave(target):
    addAction(target,ACTION.Leave)


def End():
    SendGame.SetAction(actions,gameData.me.num);


def testBrain(MeNum,MeTeam):
    #gameData.init(args)
    return 1


