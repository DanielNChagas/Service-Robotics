#include "navigation.h"

// Navigator

Navigator::Navigator() : path(3)
{
    currentDir = 3;
}

int Navigator::nextTurn()
{

    int prevNode = currentNode;
    currentNode = path.getNode(numTurns, -1);
    if (currentNode != prevNode && willGoHome)
    {
        path = MazePath(currentDir, currentNode);
        numTurns = 0;
        willGoHome = false;
    }

    int nextTurn = path.getTurn(numTurns);
    numTurns++;
    currentDir += nextTurn;
    if (currentDir < 0)
        currentDir += 4;
    if (currentDir > 3)
        currentDir -= 4;

    return nextTurn;
}

void Navigator::goHome()
{
    willGoHome = true;
}

bool Navigator::hasNextTurn()
{
    return path.hasTurn(numTurns);
}

// Navigator::MazePath

constexpr uint8_t Navigator::MazePath::numExplorePathTurns;
constexpr int8_t Navigator::MazePath::explorePathTurns[NUM_EXPLORE_PATH_TURNS][2];
constexpr uint8_t Navigator::MazePath::numHomePathTurns[NUM_NODES];
constexpr int8_t Navigator::MazePath::homePathTurns[NUM_NODES - 1][14][2];

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

void Navigator::MazePath::initPath(const int8_t p[][2], int startDir)
{
    // The first turn is cardinal, convert to relative
    turns[0][0] = p[0][0] - startDir;
    turns[0][0] = (turns[0][0] == 3) ? -1 : turns[0][0];

    for (int t = 1; t < numTurns; t++)
    {
        turns[t][0] = p[t][0];
        turns[t][1] = p[t][1];
    }
}

bool Navigator::MazePath::hasTurn(int t) { return t < numTurns; }

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