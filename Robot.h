#ifndef ROBOT_INCLUDED
#define ROBOT_INCLUDED

class Arena;  // This is needed to let the compiler know that Arena is a
               // type name, since it's mentioned in the Robot declaration.
 
 class Robot
 {
   public:
       // Constructor
     Robot(Arena* ap, int r, int c, int channel);
 
       // Accessors
     int  row() const;
     int  col() const;
     int  channel() const;
     bool isDead() const;
 
       // Mutators
     void forceMove(int dir);
     void move();
 
   private:
     Arena* m_arena;
     int    m_row;
     int    m_col;
     int    m_channel;
     int    m_health;
};

#endif //ROBOTS_INCLUDED
