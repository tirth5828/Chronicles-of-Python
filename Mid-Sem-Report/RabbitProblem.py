"""
In the rabbit leap problem, three east-bound rabbits stand in a line blocked by three west-bound rabbits. They are crossing a stream with stones placed in the east west direction in a line. There is one empty stone between them. The rabbits can only move forward one step or two steps. They can jump over one rabbit if the need arises, but not more than that. Are they smart enough to cross each other without having to step into the water?
""" 
from Agents.bfs import bfsAgent
from Agents.dfs import dfsAgent
from collections import deque


isEmpty = lambda _: _ == '0'
isRighty = lambda _: _ == '1'
isLefty = lambda _: _ == '2'

# A B C _ D E F
# can jump over 1 frog
initialState = '1 1 1 0 2 2 2'
targetState = '2 2 2 0 1 1 1'

def updatedState(previous, index, newIndex):
    rabbits = previous.split(' ')
    rabbits[newIndex] = rabbits[index]
    rabbits[index] = '0'
    return ' '.join(rabbits)

def getPossibleOutComes(state):
    rabbits = state.split(' ')
    length = len(rabbits)
    newStates = []
    for i in range(length):
        rabbit = rabbits[i]
        if isRighty(rabbit):
            if i + 1 < length and isEmpty(rabbits[i + 1]):
                # print('a', i)
                # can hope onto next one
                newStates.append(updatedState(state, i, i+1))
            if i + 2 < length and isEmpty(rabbits[i + 2]):
                # print('b', i)
                # can hope onto next to next one too
                newStates.append(updatedState(state, i, i+2))
        elif isLefty(rabbit):
            # check left condition
            if i - 1 >= 0 and isEmpty(rabbits[i - 1]):
                # print('c', i)
                # can hope onto previous one
                newStates.append(updatedState(state, i, i-1))
            if i - 2 >= 0 and isEmpty(rabbits[i - 2]):
                # print('d', i)
                # can hope onto previous to previous one too
                newStates.append(updatedState(state, i, i-2))
    return newStates

print('BFS::')
bfsAgent(initialState, finalState = targetState, getPossibleOutComes = getPossibleOutComes)
print('\nDFS::')
dfsAgent(initialState, finalState = targetState, getPossibleOutComes = getPossibleOutComes)
