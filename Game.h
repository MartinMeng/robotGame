#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include <string>

class Arena;

class Game
{
  public:
      // Constructor/destructor
    Game(int rows, int cols, int nRobots);
    ~Game();

      // Mutators
    void play();

  private:
    Arena* m_arena;

      // Helper functions
    std::string takePlayerTurn();
    std::string takeRobotsTurn();
};

#endif //GAME_INCLUDED
