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
foundStates: the states we have already explored
parent: parent of agent(as its recursive)
finalCheckFunction: if there are more than one final strings, environment can supply function to check if state is final or not.
"""
def dfsAgent(initialState, finalState, getPossibleOutComes, foundStates = [], parent = None):
    if initialState in foundStates:
        return
    else:
        foundStates.append(initialState)
    print('exploring ', initialState)
    if initialState == finalState:
        print('Found SolN')
        print('total explored ', len(foundStates))
        return True
    initialNode = Node(state = initialState, cost = 1, parent = parent)
    # its all list at the end but stack makes more sense as we insert at the start
    newStates = getPossibleOutComes(initialNode.state)
    for newState in newStates:
        if newState == finalState:
            print('Found Soln______')
            print('total explored ', len(foundStates))
            newNode = Node(state = newState, parent = initialNode, cost = 1)
            backTracking(newNode)
            return True
        if newState not in foundStates:
            newNode = Node(state = newState, parent = initialNode, cost = 1)
            z = dfsAgent(newState, finalState, getPossibleOutComes, foundStates, initialNode)
            if z:
                return True