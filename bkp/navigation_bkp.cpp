#include "navigation.h"
#include "iostream"
using namespace std;

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
        path = MazePath(currentDir, numTurns+1);
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

constexpr int Navigator::MazePath::numExplorePathTurns;
constexpr int Navigator::MazePath::explorePathTurns[NUM_EXPLORE_PATH_TURNS][2];
constexpr int Navigator::MazePath::numHomePathTurns;
constexpr int Navigator::MazePath::homePathTurns[NUM_HOME_PATH_TURNS][2];

Navigator::MazePath::MazePath(int startDir)
{
    initPath(explorePathTurns, numExplorePathTurns, startDir, 0);
}
Navigator::MazePath::MazePath(int startDir, int startTurn)
{
    //initPath(homePathTurns, numHomePathTurns, startDir, startTurn);
    initPath(explorePathTurns, numExplorePathTurns, startDir, startTurn);
}

void Navigator::MazePath::initPath(const int p[][2], int numTurns, int startDir, int startTurn)
{
    this->numTurns = numTurns - startTurn;
    // The first turn is cardinal, convert to relative
    if (startTurn == 0)
    {
        turns[0][0] = p[startTurn][0] - startDir;
        turns[0][0] = (turns[0][0] == 3) ? -1 : turns[0][0];
        turns[0][1] = p[startTurn][1];
        startTurn++;
    }

    for (int t = 0; t < this->numTurns; t++)
    {
        turns[t][0] = p[t + startTurn][0];
        turns[t][1] = p[t + startTurn][1];
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