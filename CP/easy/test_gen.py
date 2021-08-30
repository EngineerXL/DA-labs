from random import *

MIN_CORD = -10 ** 9
MAX_CORD = 10 ** 9
DIGITS = 6

def randCord():
    return (randint(MIN_CORD, MAX_CORD) / (10 ** DIGITS), randint(MIN_CORD, MAX_CORD) / (10 ** DIGITS))

def dist(u, v):
    (xu, yu) = u
    (xv, yv) = v
    return ((xu - xv) * (xu - xv) + (yu - yv) * (yu - yv)) ** 0.5

TEST_COUNT = 99
MIN_VERTICIES = 20
MAX_VERTICIES = 50
MIN_EDGES = 40
MAX_EDGES = 200
MIN_QUERY = 10
MAX_QUERY = 20

INF = 10 ** 18

for i in range(1, TEST_COUNT + 1):
    testFile = open("tests/" + str(i) + ".in", "w")
    ansFile = open("tests/" + str(i) + ".out", "w")

    n = randint(MIN_VERTICIES, MAX_VERTICIES)
    verticies = []
    for j in range(n):
        verticies.append(randCord())

    m = min((n * (n - 1)) // 2, randint(MIN_EDGES, MAX_EDGES))
    existEdges = set()
    edges = []
    for j in range(m):
        u = randint(1, n)
        v = randint(1, n)
        while ((u, v) in existEdges or (v, u) in existEdges):
            u = randint(1, n)
            v = randint(1, n)
        existEdges.add((u, v))
        existEdges.add((v, u))
        edges.append((u, v))

    q = randint(MIN_QUERY, MAX_QUERY)
    query = []
    for j in range(q):
        u = randint(1, n)
        v = randint(1, n)
        while (u == v):
            v = randint(1, n)
        query.append((u, v))

    # Ford-Bellman
    ans = []
    for j in range(q):
        d = [INF for ii in range(n)]
        d[query[j][0] - 1] = 0
        for ii in range(n):
            for jj in range(m):
                u = edges[jj][0] - 1
                v = edges[jj][1] - 1
                d[u] = min(d[u], d[v] + dist(verticies[v], verticies[u]))
                d[v] = min(d[v], d[u] + dist(verticies[u], verticies[v]))
        ans.append(d[query[j][1] - 1])

    # .in
    testFile.write(str(n) + " " + str(m) + "\n")
    for j in range(n):
        testFile.write("{:.6f}".format(verticies[j][0]) + " " + "{:.6f}".format(verticies[j][1]) + "\n")
    for j in range(m):
        testFile.write(str(edges[j][0]) + " " + str(edges[j][1]) + "\n")
    testFile.write(str(q) + "\n")
    for j in range(q):
        testFile.write(str(query[j][0]) + " " + str(query[j][1]) + "\n")

    # .out
    for j in range(q):
        if (ans[j] < INF):
            ansFile.write("{:.6f}".format(ans[j]) + "\n")
        else:
            ansFile.write("-1\n")

    testFile.close()
    ansFile.close()
