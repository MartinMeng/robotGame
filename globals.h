#ifndef GLOBALS_INCLUDED
#define GLOBALS_INCLUDED

class Arena;

const int MAXROWS = 20;             // max number of rows in the arena
int randInt(int lowest, int highest);
bool charToDir(char ch, int& dir);
bool attemptMove(const Arena& a, int dir, int& r, int& c);
bool recommendMove(const Arena& a, int r, int c, int& bestDir);
int computeDanger(const Arena& a, int r, int c);
void clearScreen();

const int MAXCOLS = 20;             // max number of columns in the arena
const int MAXROBOTS = 100;          // max number of robots allowed
const int MAXCHANNELS = 3;          // max number of channels
const int ROBOT_HEALTH = 3;         // initial robot health
const double WALL_DENSITY = 0.12;   // density of walls

const int NORTH = 0;
const int EAST  = 1;
const int SOUTH = 2;
const int WEST  = 3;
const int NUMDIRS = 4;

const int EMPTY = 0;
const int WALL  = 1;

#endif //GLOBALS_INCLUDED
