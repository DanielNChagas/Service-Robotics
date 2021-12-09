#ifndef DRIVE_H
#define DRIVE_H

#include <Arduino.h>
#include <Servo.h>
#include <QTRSensors.h>
#include "navigation.h"

#define MAX_SPEED 180
#define STOP 90
#define SENSOR_COUNT 5
#define LIGHT_THRESHOLD 750

#define NUM_NODES 17
#define NUM_EXPLORE_PATH_TURNS 60
#define MAX_NUM_TURNS NUM_EXPLORE_PATH_TURNS

class Drive
{
private:
    Servo right_wheel;  //servo object to control the right wheel
    Servo left_wheel;   //servo object to control the left wheel

    QTRSensors qtrCentral;
    QTRSensors qtrOutter;

    uint16_t outterSensors[2];
    uint16_t centralSensors[3];

    float Kp = 0.035; 
    float Ki = 0.0001;
    float Kd = 0.01;

    

    
public:
    //Drive();
    int rightSensor=2500;
    uint16_t outterRightSensor=2500;
    uint16_t outterLeftSensor=2500;
    uint16_t leftSensor=2500;
    uint16_t middleSensor=2500;
    Navigator navigation;
    /*void goHome();
    bool hasNextTurn();
    int nextTurn();
    class MazePath
    {
    public:
        MazePath(int startDir);
        MazePath(int startDir, int node);
        bool hasTurn(int t);
        int getTurn(int t);
        int getNode(int t, int searchDirection);

    private:
        static constexpr int numExplorePathTurns = NUM_EXPLORE_PATH_TURNS;*/
        /*  1st number is the turn 2nd is the cell of the turn
        *   0 -> Move forward
        *   1 -> Turn right
        *   -1 -> Turn left
        *   2 -> 180 degrees turn 
        */
        /*static constexpr int explorePathTurns[NUM_EXPLORE_PATH_TURNS-1][2] = {
            {0, -1},
            {-1, 14},
            {-1, 13},
            {1, -1},
            {2, 15},
            {-1, -1},
            {-1, 13},
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
            {1, -1},
            {2, 4},
            {-1, -1},
            {-1, 13},
            {1, 14},
            {-1, -1},
        };

        static constexpr int numHomePathTurns[NUM_NODES] = {7, 13, 14, 6, 5, 10, 10, 9, 8, 5, 4, 5, 6, 3, 2, 5};*/
        /*static constexpr int homePathTurns[NUM_NODES - 1][14][2] = {
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
        };*/

        /*void initPath(const int p[][2], int startDir);

        int numTurns;
        int turns[MAX_NUM_TURNS][2];
    };

    
    int currentDir;
    int numTurns = 0;
    bool willGoHome = false;
    MazePath path;
    int currentNode = 16;*/
    

    int P;
    int I=0;
    int D;
    float lastError=0;

    uint64_t previousTime=0;

    void init();
    void driveForward();
    void stop();
    void turnRight();
    void turnLeft();
    void uTurn();
    void turnSlightlyLeft();
    void turnSlightlyRight();
    bool missingLine();

    void getLineSensorValue();
    float getSonar();
    void LineFollowing();
    void BasicLineFollowing();

    int controller();

    
    void printNav();


    
    
};




#endif