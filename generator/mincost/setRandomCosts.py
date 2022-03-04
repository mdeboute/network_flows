from random import randint
import sys


def setRandomCosts():
    fileName = str(sys.argv[1])

    file= open(fileName,"r")
    lines= file.readlines()
    file.close()

    nbLines = int(lines[1].split()[3])

    for index in range(nbLines):
        lines[3+index] = lines[3+index][0:len(lines[3+index])-2] + str(randint(0,100)) + "\n"

    file= open(fileName,"w")
    file.writelines(lines)
    file.close()


setRandomCosts()
