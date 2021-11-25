#include "navigation.h"

// Navigator

Navigator::Navigator(int startDir) : path(startDir)
{
    currentDir = startDir;
}

int Navigator::nextTurn()
{
    int nextTurn = path.getTurn(numTurns);
    numTurns++;
    currentDir += nextTurn;
    if (currentDir < 0)
        currentDir += 4;

    int prevNode = currentNode;
    currentNode = path.getNode(numTurns, -1);
    if (currentNode != prevNode && willGoHome)
    {
        path = MazePath(currentDir, currentNode);
        willGoHome = false;
    }

    return nextTurn;
}

void Navigator::goHome()
{
    willGoHome = true;
}

// Navigator::MazePath

Navigator::MazePath::MazePath(int startDir)
{
    numTurns = numExplorePathTurns;
    initPath(explorePathTurns, startDir);
}

Navigator::MazePath::MazePath(int startDir, int node)
{
    numTurns = numHomePathTurns[node];
    initPath(homePathTurns[node], startDir);
}

void Navigator::MazePath::initPath(const int p[][2], int startDir)
{
    // The first turn is cardinal, convert to relative
    turns[0][0] = p[0][0] - startDir;
    turns[0][0] = (turns[0][0] == 3) ? -1 : turns[0][0];

    turns[0][1] = p[0][1];

    for (int t = 1; t < numTurns; t++)
    {
        turns[t][0] = p[t][0];
        turns[t][1] = p[t][1];
    }
}

int Navigator::MazePath::getTurn(int t) { return turns[t][0]; }

int Navigator::MazePath::getNode(int t, int searchDirection)
{
    int i = t;
    while ((i < numTurns && searchDirection == 1) || (i >= 0 && searchDirection == -1))
    {
        if (turns[i][1] != -1)
            return turns[i][1];
        i += searchDirection;
    }
    return -1;
}