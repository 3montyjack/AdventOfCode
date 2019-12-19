
def getResult():
    file = open("g:\Desktop\School\Advent Of Code\Day1Data.txt")
    total = 0 
    for i in file.readlines():
        total = total + getFuel(int(i.strip()))
    return total

def getFuel(mass):
    result = int(mass/3) - 2
    if (result > 0):
        return result + getFuel(result)
    return 0

print(getResult())


