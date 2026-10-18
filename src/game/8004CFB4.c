typedef struct Vector {
    int x;
    int y;
    int z;
} Vector;
typedef struct Waypoint {
    char pad00[4];
    Vector position;
} Waypoint;
typedef struct GoalTank {
    char pad000[0xFC];
    unsigned short route;
    char pad0FE[0x148 - 0xFE];
    unsigned short route_seen;
} GoalTank;
Waypoint *func_8004BE20(GoalTank *);

Vector *func_8004CFB4(GoalTank *tank) {
    Vector *goal = 0;
    Waypoint *waypoint;

    do {
    } while (0);
    if (tank->route_seen == tank->route) {
        waypoint = func_8004BE20(tank);
        if (waypoint != 0) {
            goal = &waypoint->position;
        }
    }
    return goal;
}
