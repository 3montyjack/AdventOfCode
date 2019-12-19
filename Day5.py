

currentPC = 0
notOutput = -2

def line(opCode, val1, val2, val3, listTemp, currentPC):
    if (opCode == 1):
        # Addition
        # print(val3)
        listTemp[val3] = str(val1 + val2)
        return currentPC+2, notOutput
    elif (opCode == 2):
        #Multiply
        listTemp[val3] = str(val1 * val2)
        return currentPC+2, notOutput
    elif (opCode == 99):
        return -1, -1
    else:
        return -1, -1


def extendedLine(opcode, arg1, arg2, arg3, listTemp, currentPC, input):
    currentPC = currentPC+2
    if opcode == 3:
        # input
        listTemp[arg1] = str(input)
        print(listTemp)
        return currentPC, notOutput
    elif opcode == 4:
        # output
        # print(arg1)
        # print(arg1)
        return currentPC, arg1
    elif opcode == 5:
        # jump if true
        if arg1 is not 0:
            currentPC = arg2
        else:
            currentPC = currentPC+1
        return currentPC, notOutput
    elif opcode == 6:
        # jump if false
        if arg1 is 0:
            currentPC = arg2
        else:
            currentPC = currentPC+1
        return currentPC, notOutput
    elif opcode == 7:
        # less than
        if arg1 < arg2:
            listTemp[arg3] = str(1)
        else:
            listTemp[arg3] = str(0)
        return currentPC+2, notOutput

    elif opcode == 8:
        # equals
        if arg1 is arg2:
            listTemp[arg3] = str(1)
        else:
            listTemp[arg3] = str(0)
        return currentPC+2, notOutput
    else:
        return line(opcode, arg1,arg2,arg3, listTemp, currentPC)
        

def wrapperForInterpretingOpcode(listTemp, currentPC, input):
    opcode = listTemp[currentPC]
    if int(opcode) is 99:
        return -1, -1
    arg1 = listTemp[currentPC + 1]
    arg2 = listTemp[currentPC+2]
    arg3 = listTemp[currentPC+3]
    i = len(opcode)
    print("EHH " + opcode + " " + arg1 + " " + arg2 + " " + arg3)
    while i < 5:
        opcode = "0" + opcode
        i = i+1
    newOpCode = int(opcode[3:5])
    mode1stParamater = int(opcode[2])
    mode2ndParamater = int(opcode[1])
    mode3rdParamater = int(opcode[0])
    if mode1stParamater is 0 and newOpCode is not 3 and (newOpCode is not 99):
        arg1 = listTemp[int(arg1)]
    if (mode2ndParamater is 0) and (((newOpCode > 4) or (newOpCode < 3)) and (newOpCode is not 8) and (newOpCode is not 99)):
        arg2 = listTemp[int(arg2)]
    # This is allways taken literally in this program
    # if mode3rdParamater is 0:
    #     arg3 = listTemp[int(arg3)]
            # print("OOPS")
    print("EHH " + str(newOpCode) + " " + arg1 + " " + arg2 + " " + arg3)   
    return extendedLine(newOpCode, int(arg1), int(arg2), int(arg3), listTemp, currentPC, input)


def processController(i,j):


    file = open("g:\Desktop\School\Advent Of Code\Day5Data.txt")

    array = file.readline().strip().split(",")
    
    currentPC = 0
    output = 5

    # array[1] = str(i)
    # array[2] = str(j)
    

    while currentPC is not -1:
        print("CurrentPC: " + str(currentPC) + " OutPut: " + str(output))
        print(array)
        currentPC, tempoutput = wrapperForInterpretingOpcode(array, currentPC, output)
        # print(tempoutput)    
        output = 0 
        if tempoutput is not notOutput:
            output = tempoutput
            print(output)
    # print(array)
    return array[0]


# def getValues():
#     for i in range(0, 100):
#         for j in range(0, 100):
#             value = processController(i,j)
#             print(value)
#             if int(value) is 19690720:
#                 print(100*i + j)
#                 break

# getValues()
processController(1,1)
