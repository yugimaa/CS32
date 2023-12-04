#ifndef Player_h
#define Player_h
#include<iostream>
using namespace std;

class Arena;  // This is needed to let the compiler know that Arena is a
// type name, since it's mentioned in the Rabbit declaration.


class Player
{
public:
    // Constructor
    Player(Arena* ap, int r, int c);

    // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;

    // Mutators
    string dropPoisonedCarrot();
    string move(int dir);
    void   setDead();

private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    bool   m_dead;
};

#endif