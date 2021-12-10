#include "navigation.h"

// Navigator

Navigator::Navigator() : path(3)
{
    currentDir = 3;
}

int Navigator::nextTurn(int savedPeople)
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
    if(savedPeople == 3){
        nextTurn = path.homePath[turnsHome][0];
        turnsHome++;
    }
    numTurns++;
    //Serial.println(nextTurn);
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
constexpr int Navigator::MazePath::homePath[2][2];
constexpr int Navigator::MazePath::numExplorePathTurns;
constexpr int Navigator::MazePath::explorePathTurns[NUM_EXPLORE_PATH_TURNS-1][2];
constexpr int Navigator::MazePath::numHomePathTurns[NUM_NODES];
//constexpr int Navigator::MazePath::homePathTurns[NUM_NODES - 1][14][2];

Navigator::MazePath::MazePath(int startDir)
{
    numTurns = numExplorePathTurns;
    Serial.print("heyhey");
    initPath(explorePathTurns, startDir);
}

Navigator::MazePath::MazePath(int startDir, int node)
{
    numTurns = numHomePathTurns[node];
    //initPath(homePathTurns[node], startDir);
}

void Navigator::MazePath::initPath(const int p[][2], int startDir)
{
    // The first turn is cardinal, convert to relative
    turns[0][0] = p[0][0] - startDir;
    turns[0][0] = (turns[0][0] == 3) ? -1 : turns[0][0];
    //Serial.print(turns[0][0]);
    Serial.println(numTurns);
    for (int t = 1; t < numTurns; t++)
    {
        turns[t][0] = p[t][0];
        turns[t][1] = p[t][1];
        //Serial.print(turns[t][0]);
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