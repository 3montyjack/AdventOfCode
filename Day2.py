
def line(opCode, val1, val2, val3, list):
    if (opCode == 1):
        # Addition
        # print(val3)
        return ((list[val1] + list[val2]), val3)
    if (opCode == 2):
        #Multiply
        # print(val1, val2, val3)
        return ((list[val1] * list[val2]), val3)
    if (opCode == 99):
        return (-1, -1)

def readValues(k,j):
    file = open("g:\Desktop\School\Advent Of Code\Day2Data.txt")

    array = file.readline().strip().split(",")
    intArray = []
    for i in range(0, len(array)):
        intArray.append(int(array[i]))
    
    index = 0

    intArray[1] = k
    intArray[2] = j
    value = ()
    for i in range(0, len(intArray)):
        
        if intArray[index] is not 99:
            value = line(intArray[index], intArray[index + 1],
                intArray[index + 2], intArray[index + 3], intArray)
            if value[0] != -1:
                index = index + 4
                # print(value)
                intArray[value[1]] = value[0]
                # print(intArray)
        else:
            print(value, intArray[0])
            return intArray[0]

def getValues():
    for i in range(0,100):
        for j in range(0,100):
            value = readValues(i,j)
            if value == 19690720:
                print((i,j))
                print(100*64 + 21)
                return 
getValues()
