#ifndef QSNAKE_H
#define QSNAKE_H

#include <queue>

typedef struct
{
    int x;
    int y;
} pixel;

class QSnake
{
public:
    QSnake();
    std::queue<pixel> m_snake;
    pixel m_direction;

    bool step(QSnake *enemy, int x, int y, int sizeX, int sizeY, int cornX, int cornY, bool walls = false);
    void die(void);

    int m_die;
    int m_startSize;
};

#endif // QSNAKE_H
