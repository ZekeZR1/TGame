###PLAYER###
import SendGame


def sqrt(v):
    n = 1
    for i in range(32):
        n = (n + v/n)/2
    return n

class Vector3:
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
        self.Attack = 0
        self.AttackEx = 0
        self.Defence = 0
        self.DefenceEx = 0
        self.speed = 0
        self.movespeed = Vector3()
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


class GameData:
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

            mon.Attack = datas[i][6]
            mon.AttackEx = datas[i][7]
            mon.Defence = datas[i][8]
            mon.DefenceEx = datas[i][9]

            mon.speed = datas[i][10]
            pos = datas[i][11]
            mon.movespeed.SetVector(pos[0],pos[1],pos[2])

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

    def Init(self):
        """
        ゲームデータの初期化
        必ず最初に使いましょう。
        """
        num = SendGame.GetMyNum()
        team = SendGame.GetMyTeam()
        
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

            mon.Attack = datas[i][6]
            mon.AttackEx = datas[i][7]
            mon.Defence = datas[i][8]
            mon.DefenceEx = datas[i][9]

            mon.speed = datas[i][10]
            pos = datas[i][11]
            mon.movespeed.SetVector(pos[0],pos[1],pos[2])

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

    def GetEnemyLowHPMonster(self):
        lomon = None
        for mon in self.Enemys:
            if lomon == None or lomon.HP > mon.HP:
                lomon = mon
        return lomon

    def GetBuddyLowHPMonster(self):
        lomon = None
        for mon in self.Buddy:
            if lomon == None or lomon.HP > mon.HP:
                lomon = mon
        return lomon

    def GetHighATKMonster(self):
        lomon = None
        for mon in self.Enemys:
            if lomon == None or lomon.Attack < mon.Attack:
                lomon = mon
        for mon in self.Buddy:
            if lomon.Attack < mon.Attack:
                lomon = mon
        return lomon

    def GetEnemyHighATKMonster(self):
        lomon = None
        for mon in self.Enemys:
            if lomon == None or lomon.Attack < mon.Attack:
                lomon = mon
        return lomon

    def GetBuddyHighATKMonster(self):
        lomon = None
        for mon in self.Buddy:
            if lomon == None or lomon.Attack < mon.Attack:
                lomon = mon
        return lomon

    def FindEnemyMonster(self,monID):
        for mon in self.Enemys:
            if mon.ID == monID:
                return mon
        return None

    def FindBuddyMonster(self,monID):
        for mon in self.Buddy:
            if mon.ID == monID:
                return mon
        return None

    def FindEnemyMonsters(self,monID):
        mons = list()
        for mon in self.Enemys:
            if mon.ID == monID:
                mons.append(mon)
        return mons

    def FindBuddyMonsters(self,monID):
        mons = list()
        for mon in self.Buddy:
            if mon.ID == monID:
                mons.append(mon)
        return mons

gameData = GameData()

Uma = SendGame.Uma
Yose = SendGame.Yose
Armor = SendGame.Armor
Goblin = SendGame.Goblin
Book = SendGame.Book
RedHead = SendGame.RedHead
Kikyo = SendGame.Kikyo
SicoChu = SendGame.SicoChu
Ringo = SendGame.Ringo
Chris = SendGame.Chris


def init(num,team):
    """ゲームデータの初期化
        必ず最初に使いましょう。
        """
    #SendGame.gameData.init(num,team)
    gameData.init(num,team)

def Init():
    gameData.Init()


def GetMe():
    return gameData.me


def GetFarMonster():
    return gameData.GetFarMonster()

def GetBuddyFarMonster():
    return gameData.GetBuddyFarMonster()

def GetEnemyFarMonster():
    return gameData.GetEnemyFarMonster()



def GetNeerMonster():
    return gameData.GetNeerMonster()

def GetBuddyNeerMonster():
    return gameData.GetBuddyNeerMonster()

def GetEnemyNeerMonster():
    return gameData.GetEnemyNeerMonster()



def GetHighHPMonster():
    """#一番HPの高いモンスターを返します"""
    return gameData.GetHighHPMonster()

def GetBuddyHighHPMonster():
    """#一番HPの高い仲間のモンスターを返します"""
    return gameData.GetBuddyHighHPMonster()

def GetEnemyHighHPMonster():
    """#一番HPの高い敵のモンスターを返します"""
    return gameData.GetEnemyHighHP()

#def GetLowHPMonster():
    #return gameData.GetLowHPMonster()

def GetEnemyLowHPMonster():
    return gameData.GetEnemyLowHPMonster()

def GetBuddyLowHPMonster():
    return gameData.GetBuddyLowHPMonster()



def GetHighATKMonster():
    return gameData.GetHighATKMonster()

def GetEnemyHighATKMonster():
    return gameData.GetEnemyHighATKMonster()

def GetBuddyHighATKMonster():
    return gameData.GetBuddyHighATKMonster()



def FindBuddyMonster(monID):
    return gameData.FindBuddyMonster(monID)

def FindBuddyMonsterList(monID):
    return gameData.FindBuddyMonsters(monID)

def FindEnemyMonster(monID):
    return gameData.FindEnemyMonster(monID)

def FindEnemy(monID):
    return gameData.FindEnemyMonster(monID)

def FindEnemyMonsterList(monID):
    return gameData.FindEnemyMonsters(monID)


actions = []


def addAction(target,action):
    """外から使わないでね!"""
    if target == None:
        return
    actions.append([int(action),target.num])

def Chase(target):
    SendGame.addAction(target.num,SendGame.CHASE)
    
def Attack(target):
    SendGame.addAction(target.num,SendGame.ATTACK)

def Escape(target):
    SendGame.addAction(target.num,SendGame.ESCAPE)

def Defense(target):
    SendGame.addAction(target.num,SendGame.DEFENSE)

def Fire(target):
    SendGame.addAction(target.num,SendGame.FIRE)

def Tackle(target):
    SendGame.addAction(target.num,SendGame.TACKLE)

def Guardian(target):
    SendGame.addAction(target.num,SendGame.GUARDIAN)

def Heal(target):
    SendGame.addAction(target.num,SendGame.HEAL)

def SUPER_BEAM(target):
    SendGame.addAction(target.num,SendGame.SUPER_BEAM)

def Obst_Move(target):
    SendGame.addAction(target.num,SendGame.Obst_Move)

def Cleanse(target):
    SendGame.addAction(target.num,SendGame.Cleanse)

def ATK_Buff(target):
    SendGame.addAction(target.num,SendGame.ATK_Buff)

def ATK_Debuff(target):
    SendGame.addAction(target.num,SendGame.ATK_Debuff)

def DEF_Buff(target):
    SendGame.addAction(target.num,SendGame.DEF_Buff)

def DEF_Debuff(target):
    SendGame.addAction(target.num,SendGame.DEF_Debuff)

def Clear_Stack(target):
    SendGame.addAction(target.num,SendGame.Clear_Stack)

def Majinken(target):
    SendGame.addAction(target.num,SendGame.Majinken)

def MP_Heal(target):
    SendGame.addAction(target.num,SendGame.MP_Heal)

def Blizzard(target):
    SendGame.addAction(target.num,SendGame.Blizzard)

def Ignite(target):
    SendGame.addAction(target.num,SendGame.Ignite)

def Poison(target):
    SendGame.addAction(target.num,SendGame.Poison)

def Thunder(target):
    SendGame.addAction(target.num,SendGame.Thunder)

def Kamikaze(target):
    SendGame.addAction(target.num,SendGame.Kamikaze)

    

def Move(targetPosition):
    """モンスターを指定したポジションに移動させる。"""
    SendGame.Move(targetPosition.x,targetPosition.z)

def End():
    SendGame.SetAction(actions,gameData.me.num);


def Brain():
    Init()
    End()


