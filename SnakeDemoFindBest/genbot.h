#ifndef BOT_H
#define BOT_H

#include <vector>

class GenBot
{
public:
    GenBot();
    void doStep(std::vector<uint8_t> &in, std::vector<uint8_t> &out);
    void randMe();


    uint8_t m_reg[8];

    uint8_t m_mem[256];
    uint8_t m_gen[256];

private:

    uint8_t m_iter;

};

#endif // BOT_H
