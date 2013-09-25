#include "Robot.h"
#include "Arena.h"
#include <iostream>
#include "globals.h"
#include <cstdlib>

using namespace std;

///////////////////////////////////////////////////////////////////////////
//  Robot implementation
///////////////////////////////////////////////////////////////////////////

Robot::Robot(Arena* ap, int r, int c, int channel)
 : m_arena(ap), m_row(r), m_col(c), m_channel(channel), m_health(ROBOT_HEALTH)
{
    if (ap == NULL)
    {
        cout << "***** A robot must be created in some Arena!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols())
    {
        cout << "***** Robot created with invalid coordinates (" << r << ","
             << c << ")!" << endl;
        exit(1);
    }
    if (channel < 1  ||  channel > MAXCHANNELS)
    {
        cout << "***** Robot created with invalid channel " << channel << endl;
        exit(1);
    }
}

int Robot::row() const
{
    return m_row;
}

int Robot::col() const
{
    return m_col;
}

int Robot::channel() const
{
    return m_channel;
}

bool Robot::isDead() const
{
    return m_health == 0;
}

void Robot::forceMove(int dir)
{
      // Suffer one unit of damage if moving fails

    if (!isDead()  &&  !attemptMove(*m_arena, dir, m_row, m_col))
        m_health--;
}

void Robot::move()
{
      // Attempt to move in a random direction; if we can't move, don't move
    if (!isDead())
        attemptMove(*m_arena, randInt(0, NUMDIRS-1), m_row, m_col);
}

