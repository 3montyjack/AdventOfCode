


def isSixDigit(number):
    temp = str(number)
    # print(len(temp) == 6)
    return len(temp) == 6 

def withinRange(number, lowerBound, upperBound):
    # print(number <= upperBound and number >= lowerBound)
    return number <= upperBound and number >= lowerBound

def thereAre2AdjacentDigits(number):
    flag = False
    temp = str(number)
    prev = ""
    currentLength = 0
    for i in temp:
        if prev is i:
            currentLength = currentLength +1
            flag = True
            if currentLength != 1:
                flag = False

        else:
            if currentLength == 1:
                break
            prev = i
            currentLength = 0
    return flag

def isAscendingValues(number):
    temp = ""
    flag = True
    for i in str(number):
        if i < temp:
            flag = False
            break
        temp = i
    return flag

def findAmmountNumbers(lower, upper):
    ammount = 0
    for i in range(lower, upper+1):
        # print(i)
        # if isAscendingValues(i):
        #     print(i)
        #     isSixDigit(i) and withinRange(i, lower, upper) and
        if thereAre2AdjacentDigits(i) and isAscendingValues(i):
            print(i)
            ammount = ammount + 1
    print(ammount)
findAmmountNumbers(152085, 670283)


# findAmmountNumbers(112233, 112233)
# findAmmountNumbers(123444, 123444)
# findAmmountNumbers(111122, 111122)

