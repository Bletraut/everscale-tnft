#include "qsnake.h"

static int g_next = 0;

QSnake::QSnake()
{
    m_startSize = 5;

    pixel a;
    a.y = g_next;
    a.x = 0;

    g_next += 5;

    for(int i = 0; i < m_startSize; i++)
    {
        a.x++;
        m_snake.push(a);
    }

    m_direction.x = 1;
    m_direction.y = 0;

    m_die = 0;
}

bool QSnake::step(QSnake *enemy, int x, int y, int sizeX, int sizeY, int cornX, int cornY, bool walls)
{
    pixel pix = m_snake.back();

    if(m_direction.x * x < 0)
        x = m_direction.x;
    if(m_direction.y * y < 0)
        y = m_direction.y;
    if(x == 0 && y == 0)
    {
        x = m_direction.x;
        y = m_direction.y;
    }

    if(x != 0)
    {
        if(x > 0)
            pix.x++;
        else
            pix.x--;

        m_direction.x = x;
        m_direction.y = 0;

    }
    else if(y != 0)
    {
        if(y > 0)
            pix.y++;
        else
            pix.y--;

        m_direction.y = y;
        m_direction.x = 0;
    }

    int dieI = 0;

    if(walls)
    {
        if(pix.x < 0 || pix.y < 0 || sizeX <= pix.x || sizeY <= pix.y)
        {
            dieI++;
        }
    }
    else
    {
        if(pix.x < 0)
            pix.x = sizeX - 1;
        if(pix.y < 0)
            pix.y = sizeY - 1;

        pix.x = pix.x % sizeX;
        pix.y = pix.y % sizeY;
    }

    bool b = (cornX != pix.x || cornY != pix.y);
    if(b)
        m_snake.pop();

    m_snake.push(pix);

    bool bb = false;

    std::queue<pixel> snake = m_snake;

    while(!snake.empty())
    {
        if(m_snake.back().x == snake.front().x && m_snake.back().y == snake.front().y)
            dieI++;

        snake.pop();
    }

    bb = (dieI > 1);
    if(!bb)
    {
        snake = enemy->m_snake;
        while(!snake.empty())
        {
            if(m_snake.back().x == snake.front().x && m_snake.back().y == snake.front().y)
                dieI++;

            snake.pop();
        }

        bb = (dieI > 1);
    }

    if(bb)
    {
        die();
    }

    return !b;
}

void QSnake::die()
{
    while(!m_snake.empty())
    {
        m_snake.pop();
    }

    pixel a;
    a.y = g_next;
    a.x = 0;

    g_next +=1;

    for(int i = 0; i < m_startSize; i++)
    {
        a.x++;
        m_snake.push(a);
    }

    m_direction.x = 1;
    m_direction.y = 0;

    m_die++;
}
