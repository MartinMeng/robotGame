#include "Robot.h"
#include "Arena.h"
#include <iostream>
#include "globals.h"
#include <cstdlib>
#include <string>
#include "Player.h"

using namespace std;
///////////////////////////////////////////////////////////////////////////
//  Arena implementation
///////////////////////////////////////////////////////////////////////////

Arena::Arena(int nRows, int nCols)
 : m_rows(nRows), m_cols(nCols), m_player(NULL), m_nRobots(0), m_history(nRows,nCols)
{
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
    {
        cout << "***** Arena created with invalid size " << nRows << " by "
             << nCols << "!" << endl;
        exit(1);
    }
    for (int r = 1; r <= m_rows; r++)
        for (int c = 1; c <= m_cols; c++)
            setCellStatus(r, c, EMPTY);
}

Arena::~Arena()
{
    for (int k = 0; k < m_nRobots; k++)
        delete m_robots[k];
    delete m_player;
}

int Arena::rows() const
{
    return m_rows;
}

int Arena::cols() const
{
    return m_cols;
}

Player* Arena::player() const
{
    return m_player;
}

int Arena::robotCount() const
{
    return m_nRobots;
}

int Arena::getCellStatus(int r, int c) const
{
    checkPos(r, c);
    return m_grid[r-1][c-1];
}

int Arena::numberOfRobotsAt(int r, int c) const
{
    int count = 0;
    for (int k = 0; k < m_nRobots; k++)
    {
        Robot* rp = m_robots[k];
        if (rp->row() == r  &&  rp->col() == c)
            count++;
    }
    return count;
}

void Arena::display(string msg) const
{
    char displayGrid[MAXROWS][MAXCOLS];
    int r, c;
    
      // Fill displayGrid with dots (empty) and stars (wall)
    for (r = 1; r <= rows(); r++)
        for (c = 1; c <= cols(); c++)
            displayGrid[r-1][c-1] = (getCellStatus(r,c) == EMPTY ? '.' : '*');

      // Indicate robot positions by their channels.  If more than one robot
      // occupies a cell, show just one (any one will do).
    for (int k = 0; k < m_nRobots; k++)
    {
        Robot* rp = m_robots[k];
        displayGrid[rp->row()-1][rp->col()-1] = '0' + rp->channel();
    }

      // Indicate player's position
    if (m_player != NULL)
        displayGrid[m_player->row()-1][m_player->col()-1] = (m_player->isDead() ? 'X' : '@');

      // Draw the grid
    clearScreen();
    for (r = 1; r <= rows(); r++)
    {
        for (c = 1; c <= cols(); c++)
            cout << displayGrid[r-1][c-1];
        cout << endl;
    }
    cout << endl;

      // Write message, robot, and player info
    if (msg != "")
        cout << msg << endl;
    cout << "There are " << robotCount() << " robots remaining." << endl;
    if (m_player == NULL)
        cout << "There is no player!" << endl;
    else if (m_player->isDead())
        cout << "The player is dead." << endl;
}

void Arena::setCellStatus(int r, int c, int status)
{
    checkPos(r, c);
    m_grid[r-1][c-1] = status;
}

bool Arena::addRobot(int r, int c, int channel)
{
    if (! isPosInBounds(r, c)  ||  getCellStatus(r,c) != EMPTY)
        return false;
    if (m_player != NULL  &&  m_player->row() == r  &&  m_player->col() == c)
        return false;
    if (channel < 1  ||  channel > MAXCHANNELS)
        return false;
    if (m_nRobots == MAXROBOTS)
        return false;
    m_robots[m_nRobots] = new Robot(this, r, c, channel);
    m_nRobots++;
    return true;
}

bool Arena::addPlayer(int r, int c)
{
    if (m_player != NULL  ||  ! isPosInBounds(r, c)  ||  getCellStatus(r,c) != EMPTY)
        return false;
    if (numberOfRobotsAt(r, c) > 0)
        return false;
    m_player = new Player(this, r, c);
    return true;
}

string Arena::moveRobots(int channel, int dir)
{
      // Robots on the channel will respond with probability 1/2
    bool willRespond = (randInt(0, 1) == 0);

      // Move all robots
    int nRobotsOriginally = m_nRobots;
    for (int k = m_nRobots-1; k >= 0; k--)
    {
        Robot* rp = m_robots[k];
        if (willRespond  &&  rp->channel() == channel)
            rp->forceMove(dir);
        else
            rp->move();

        if (m_player != NULL  &&
                rp->row() == m_player->row()  &&  rp->col() == m_player->col())
            m_player->setDead();

        if (rp->isDead())
        {
            delete rp;

              // The order of Robot pointers in the m_robots array is
              // irrelevant, so it's easiest to move the last pointer to
              // replace the one pointing to the now-deleted robot.  Since
              // we are traversing the array from last to first, we know this
              // last pointer does not point to a dead robot.

            m_robots[k] = m_robots[m_nRobots-1];
            m_nRobots--;
        }
    }

    if (m_nRobots < nRobotsOriginally)
        return "Some robots have been destroyed.";
    else
        return "No robots were destroyed.";
}

bool Arena::isPosInBounds(int r, int c) const
{
    return (r >= 1  &&  r <= m_rows  &&  c >= 1  &&  c <= m_cols);
}

void Arena::checkPos(int r, int c) const
{
    if (!isPosInBounds(r, c))
    {
        cout << "***** " << "Invalid arena position (" << r << ","
             << c << ")" << endl;
        exit(1);
    }
}

History& Arena::history() { return m_history; }
