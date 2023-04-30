"""
The missionaries and cannibals problem is usually stated as follows. 
Three missionaries and three cannibals are on one side of a river, along with a boat that can hold one or two people. Find a way to get everyone to the other side without ever leaving a group of missionaries in one place outnumbered by the cannibals in that place. This problem is famous in AI because it was the subject of the first paper that approached problem-formulation from an analytical viewpoint.
"""

from Agents.bfs import bfsAgent
from Agents.dfs import dfsAgent

def createState(m, c, boat):
    return str(m) + ' ' + str(c) + ' ' +  str(boat)

def isValidMove(missionary, cannibal):
    if missionary > 3 or cannibal > 3 or missionary < 0 or cannibal < 0:
        return False
    # if all missionaries on one side
    if missionary == 0 or missionary == 3:
        return True
    return missionary >= cannibal and (3 - missionary) >= (3 - cannibal)

def allPossibleOutcomes(m, c, boat):
    if boat == 0:
        return [
            [m-1, c],
            [m-2, c],
            [m, c-1],
            [m, c-2],
            [m-1, c-1]
        ]
    else:
        return [
            [m+1, c],
            [m+2, c],
            [m, c+1],
            [m, c+2],
            [m+1, c+1]
        ]

def getPossibleOutComes(state):
    z = state.split(' ')
    boatLocation = int(z[2])
    m = int(z[0])
    c = int(z[1])

    nextBoatLocation = 1 if boatLocation == 0 else 0
    moves = []
    for i in allPossibleOutcomes(m, c, boatLocation):
        poss = createState(i[0], i[1], nextBoatLocation)
        if poss != state and isValidMove(i[0], i[1]):
            moves.append(poss)
    return moves

missionaryInitialState = '3 3 0'
missionaryTargetState = '0 0 1'
print('BFS::')
bfsAgent(initialState=missionaryInitialState, finalState=missionaryTargetState, getPossibleOutComes = getPossibleOutComes)
print('\nDFS::')
dfsAgent(initialState = missionaryInitialState, finalState = missionaryTargetState, getPossibleOutComes = getPossibleOutComes)
