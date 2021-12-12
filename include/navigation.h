#ifndef NAVIGATION_H
#define NAVIGATION_H

#define NUM_NODES 17
#define NUM_FIRST_PERSON_PATH_TURNS 9
#define NUM_EXPLORE_PATH_TURNS 54
#define MAX_NUM_TURNS NUM_EXPLORE_PATH_TURNS

#define PATH_FIRST_PERSON 0
#define PATH_EXPLORE 1
#define PATH_HOME 2

#include <stdint.h>

class Navigator
{
public:
    Navigator();
    Navigator(int path);

    void setPath(int path);
    bool hasNextTurn();
    int nextTurn();
    class MazePath
    {
    public:
        MazePath(int startDir);
        MazePath(int path, int startDir, int node);
        bool hasTurn(int t);
        int getTurn(int t);
        int getNode(int t, int searchDirection);
        static constexpr int homePath[2][2] = {{-1,14},{-1,-1}};

    private:
        static constexpr uint8_t numFirstPersonPathTurns = NUM_FIRST_PERSON_PATH_TURNS;
        static constexpr int8_t firstPersonPathTurns[NUM_FIRST_PERSON_PATH_TURNS][2] = {
            {4, -1},
            {-1, 14},
            {-1, 13},
            {1, -1},
            {2, 15},
            {-1, -1},
            {1, 13},
            {1, 14},
            {-1, -1},
        };

        static constexpr uint8_t numExplorePathTurns = NUM_EXPLORE_PATH_TURNS;
        static constexpr int8_t explorePathTurns[NUM_EXPLORE_PATH_TURNS][2] = {
            {3, 16},
            {1, -1},
            {-1, 14},
            {0, 13},
            {1, -1},
            {1, -1},
            {1, -1},
            {-1, -1},
            {-1, 3},
            {2, 1},
            {0, 3},
            {0, 4},
            {-1, -1},
            {-1, 7},
            {-1, 5},
            {1, -1},
            {1, -1},
            {2, 1},
            {-1, -1},
            {-1, -1},
            {-1, 5},
            {1, -1},
            {-1, -1},
            {-1, -1},
            {2, 2},
            {1, -1},
            {1, -1},
            {-1, -1},
            {0, 5},
            {-1, 7},
            {-1, 8},
            {1, -1},
            {2, 6},
            {-1, -1},
            {-1, 8},
            {1, -1},
            {1, 12},
            {-1, 11},
            {1, -1},
            {-1, -1},
            {-1, -1},
            {-1, -1},
            {-1, 12},
            {0, 11},
            {0, 10},
            {2, 9},
            {1, 10},
            {1, -1},
            {0, 14},
            {1, 13},
            {2, -1},
            {-1, 13},
            {1, 14},
            {-1, -1}
        };

        static constexpr uint8_t numHomePathTurns[NUM_NODES] = {7, 13, 14, 6, 5, 10, 10, 9, 8, 5, 4, 5, 6, 3, 2, 5};
        static constexpr int8_t homePathTurns[NUM_NODES - 1][14][2] = {
            {{2, 0}, {0, 3}, {1, 4}, {-1, -1}, {-1, 13}, {1, 14}, {-1, -1}},
            {{3, 1}, {-1, -1}, {-1, -1}, {1, 5}, {-1, 7}, {0, 8}, {1, -1}, {1, 12}, {0, 11}, {-1, 10}, {1, -1}, {-1, 14}, {-1, -1}},
            {{1, 2}, {1, -1}, {1, -1}, {-1, -1}, {0, 5}, {-1, 7}, {0, 8}, {1, -1}, {1, 12}, {0, 11}, {-1, 10}, {1, -1}, {-1, 14}, {-1, -1}},
            {{2, 3}, {1, 4}, {-1, -1}, {-1, 13}, {1, 14}, {-1, -1}},
            {{3, 4}, {-1, -1}, {-1, 13}, {1, 14}, {-1, -1}},
            {{2, 5}, {-1, 7}, {0, 8}, {1, -1}, {1, 12}, {0, 11}, {-1, 10}, {1, -1}, {-1, 14}, {-1, -1}},
            {{3, 6}, {-1, -1}, {-1, 8}, {1, -1}, {1, 12}, {0, 11}, {-1, 10}, {1, -1}, {-1, 14}, {-1, -1}},
            {{1, 7}, {0, 8}, {1, -1}, {1, 12}, {0, 11}, {-1, 10}, {1, -1}, {-1, 14}, {-1, -1}},
            {{1, 8}, {1, -1}, {1, 12}, {0, 11}, {-1, 10}, {1, -1}, {-1, 14}, {-1, -1}},
            {{1, 9}, {1, 10}, {1, -1}, {-1, 14}, {-1, -1}},
            {{2, 10}, {1, -1}, {-1, 14}, {-1, -1}},
            {{3, 11}, {-1, 10}, {1, -1}, {-1, 14}, {-1, -1}},
            {{3, 12}, {0, 11}, {-1, 10}, {1, -1}, {-1, 14}, {-1, -1}},
            {{1, 13}, {1, 14}, {-1, -1}},
            {{2, 14}, {-1, -1}},
            {{1, 15}, {-1, -1}, {1, 13}, {1, 14}, {-1, -1}},
        };

        void initPath(const int8_t p[][2], int startDir);

        int numTurns;
        int8_t turns[MAX_NUM_TURNS][2];
    };

    int currentNode = 16;
    int currentDir;
    int numTurns = 0;
    int turnsHome = 0;
    bool isPathQueued = false;
    int queuedPath = 0;
    MazePath path;
};

#endif