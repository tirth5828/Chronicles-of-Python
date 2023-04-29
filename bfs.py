from collections import deque
from .backtracking import backTracking

class Node:
    def __init__(self, state, cost=1, parent = None, children = []):
        self.state = state
        self.parent = parent
        self.cost = cost
        self.children = children

"""
params: 
initialState: initial state string
finalState: final state string
getPossibleOutComes: function from environment to return new states
finalCheckFunction: if there are more than one final strings, environment can supply function to check if state is final or not.
"""
def bfsAgent(initialState, finalState, getPossibleOutComes, finalCheckFunction=None):
    if initialState == finalState:
        print('don\'t joke around!!')
    foundStates = []
    initialNode = Node(state = initialState, cost = 1, parent = None)
    queue = deque([initialNode])
    while queue:
        z = queue.popleft()
        foundStates.append(z.state)
        newStates = getPossibleOutComes(z.state)
        print(z.state, '->', newStates)
        for newState in newStates:
            newNode = Node(state = newState, parent = z, cost = 1)
            if finalCheckFunction:
                if finalCheckFunction(newState):
                    print('Found Soln')
                    print('total explored ', len(foundStates))
                    backTracking(newNode)
                    return
            elif newState == finalState:
                print('Found Soln')
                print('total explored ', len(foundStates))
                backTracking(newNode)
                return
            if newState not in foundStates:
                foundStates.append(newState)
                queue.append(newNode)