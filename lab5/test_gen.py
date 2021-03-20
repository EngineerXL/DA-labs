from random import *

TEST_COUNT = 99
STRING_SIZE = 100

def randString():
    strSize = randint(1, STRING_SIZE)
    # strSize = STRING_SIZE
    str = ""
    for i in range(strSize):
        str = str + chr(ord('a') + randint(0, 25))
    return str

for i in range(1, TEST_COUNT + 1):
    testFile = open("tests/" + str(i) + ".in", "w")
    ansFile = open("tests/" + str(i) + ".out", "w")

    s = 100 * randString()

    # s = ""
    # num = i
    # for _ in range(6):
    #     if (num % 2 == 1):
    #         s = s + 10 * 'b'
    #     else:
    #         s = s + 20 * 'a'
    #     num = num / 2
    # s = s * 15

    testFile.write(s + "\n")

    cycle = []
    for j in range(len(s)):
        cycle.append(s[j:] + s[:j])
    cycle = sorted(cycle)
    ansFile.write(cycle[0] + "\n")

    testFile.close()
    ansFile.close()
