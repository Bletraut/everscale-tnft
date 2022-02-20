#include "genbot.h"

GenBot::GenBot()
{
    for(size_t i = 0; i < 256; i++)
        m_gen[i] = static_cast<uint8_t>(rand() % 256);
}

void GenBot::doStep(std::vector<uint8_t> &in, std::vector<uint8_t> &out)
{    
    if(in.empty())
        in.push_back(1);
    if(out.empty())
        out.push_back(1);

    switch (m_gen[m_iter++])
    {
    case 0:
        break;
    case 1:
    {
        uint8_t i0 = m_iter++;
        uint8_t i1 = m_iter++;

        if(m_mem[m_gen[m_iter++]] % 2 == 0)
        {
            i0 = m_mem[m_gen[m_iter++]];
            i1 = m_mem[m_gen[m_iter++]];
        }

        switch (m_gen[m_iter++])
        {
        case 1:
            m_mem[m_gen[i0]] = in[m_gen[i1] % in.size()];
            break;
        case 2:
            out[m_gen[i0] % out.size()] = m_mem[m_gen[i1]];
            break;
        case 3:
            m_mem[m_gen[i0]] = m_gen[m_gen[i1]];
            break;
        case 4:
//            m_gen[m_gen[i0]] = m_mem[m_gen[i1]];
            break;
        case 5:
            std::swap(m_mem[m_gen[i0]],m_gen[m_gen[i1]]);
            break;
        case 6:
            m_mem[m_mem[i0]] = in[m_mem[i1] % in.size()];
            break;
        case 7:
            out[m_mem[i0] % out.size()] = m_mem[m_mem[i1]];
            break;
        case 8:
            m_mem[m_mem[i0]] = m_gen[m_mem[i1]];
            break;
        case 9:
//            m_gen[m_mem[i0]] = m_mem[m_mem[i1]];
            break;
        case 10:
            std::swap(m_mem[m_mem[i0]],m_gen[m_mem[i1]]);
            break;
        default:
            m_gen[m_iter] = static_cast<uint8_t>(rand() % 256);
            break;
        }
    }
        break;
    case 2:
    {
        uint8_t i0 = m_iter++;
        uint8_t i1 = m_iter++;

        if(m_mem[m_gen[m_iter++]] % 2 == 0)
        {
            i0 = m_mem[m_gen[m_iter++]];
            i1 = m_mem[m_gen[m_iter++]];
        }

        switch (m_gen[m_iter++])
        {
        case 1:
            m_mem[m_gen[i0]]++;
            break;
        case 2:
            m_mem[m_gen[i0]]--;
            break;
        case 3:
            m_mem[m_gen[i0]] += m_mem[m_gen[i1]];
            break;
        case 4:
            m_mem[m_gen[i0]] -= m_mem[m_gen[i1]];
            break;
        case 5:
            m_mem[m_gen[i0]] *= m_mem[m_gen[i1]];
            break;
        case 6:
//            m_mem[m_gen[i0]] /= m_mem[m_gen[i1]] == 0 ? 1 : m_mem[m_gen[i1]];
            break;
        case 7:
            m_mem[m_gen[i0]] %= m_mem[m_gen[i1]] == 0 ? 1 : m_mem[m_gen[i1]];
            break;
        case 8:
            m_mem[m_gen[i0]] = ~(m_mem[m_gen[i1]]);
            break;
        case 9:
            m_mem[m_gen[i0]] |= m_mem[m_gen[i1]];
            break;
        case 10:
            m_mem[m_gen[i0]] <<= m_mem[m_gen[i1]];
            break;
        case 11:
            m_mem[m_gen[i0]] >>= m_mem[m_gen[i1]];
            break;
        default:
            m_gen[m_iter] = static_cast<uint8_t>(rand() % 256);;
            break;
        }
    }
        break;
    case 3:
    {
        uint8_t i2 = m_iter++;
        uint8_t i3 = m_iter++;

        uint8_t i0 = m_mem[m_gen[m_iter++]];
        uint8_t i1 = m_mem[m_gen[m_iter++]];

        if(m_mem[m_gen[i0]] > m_mem[m_gen[i1]])
        {
            m_iter = m_gen[i2];
        }
        else
        {
            m_iter = m_gen[i3];
        }
    }
        break;
    case 4:
        switch (m_gen[m_iter % 256])
        {
        case 0:
            break;
//        case 1:
//            m_mem[m_reg[0] % 256] = in;
//            break;
//        case 2:
//            m_mem[m_reg[1] % 256] = x;
//            break;
//        case 3:
//            m_mem[m_reg[2] % 256] = y;
//            break;
//        case 5:
//            m_mem[m_reg[3] % 256] = m_rating;
//            break;
//        case 6:
//            m_answer = m_mem[m_reg[4] % 256];
//            break;
//        case 7:
//            m_word[m_reg[5] % 256] = m_mem[m_reg[6] % 256];
//            break;
//        case 8:
//            switch (m_reg[7] % 4) {
//            case 0:
//                m_mem[m_reg[6] % 256] = bots[(x + 1) % (256) + (256 * (y))]->m_word[m_reg[5] % 256];
//                break;
//            case 1:
//                m_mem[m_reg[6] % 256] = bots[(x - 1) % (256) + (256 * (y))]->m_word[m_reg[5] % 256];
//                break;
//            case 2:
//                m_mem[m_reg[6] % 256] = bots[x + (256 * ((y + 1) % (256)))]->m_word[m_reg[5] % 256];
//                break;
//            case 3:
//                m_mem[m_reg[6] % 256] = bots[x + (256 * ((y - 1) % (256)))]->m_word[m_reg[5] % 256];
//                break;
//            }
//            break;
        case 9:
            std::swap(m_reg[0],m_reg[1]);
            break;
        case 10:
            std::swap(m_reg[0],m_reg[2]);
            break;
        case 11:
            std::swap(m_reg[0],m_reg[3]);
            break;
        case 12:
            std::swap(m_reg[0],m_reg[4]);
            break;
        case 13:
            std::swap(m_reg[0],m_reg[5]);
            break;
        case 14:
            std::swap(m_reg[0],m_reg[6]);
            break;
        case 15:
            std::swap(m_reg[0],m_reg[7]);
            break;
        case 16:
            m_reg[0] = m_reg[1];
            break;
        case 17:
            m_reg[0] = m_reg[2];
            break;
        case 18:
            m_reg[0] = m_reg[3];
            break;
        case 19:
            m_reg[0] = m_reg[4];
            break;
        case 20:
            m_reg[0] = m_reg[5];
            break;
        case 21:
            m_reg[0] = m_reg[6];
            break;
        case 22:
            m_reg[0] = m_reg[7];
            break;
        case 23:
            m_reg[0] = 0;
            break;
        case 24:
            m_reg[0] = std::numeric_limits<uint64_t>::max();
            break;
        case 25:
            m_reg[0]++;
            break;
        case 26:
            m_reg[0]--;
            break;
        case 27:
            m_reg[0] += m_reg[1];
            break;
        case 28:
            m_reg[0] -= m_reg[1];
            break;
        case 29:
            m_reg[0] *= m_reg[1];
            break;
        case 30:
            m_reg[0] /= (m_reg[1] == 0? 1 : m_reg[1]);
            break;
        case 31:
            m_reg[0] %= (m_reg[1] == 0? 1 : m_reg[1]);
            break;
        case 32:
            m_reg[0] <<= m_reg[1];
            break;
        case 33:
            m_reg[0] >>= m_reg[1];
            break;
        case 34:
            m_reg[0] |= m_reg[1];
            break;
        case 35:
            m_reg[0] = ~m_reg[1];
            break;
        case 36:
            if(m_reg[1] > m_reg[2])
                m_iter++;
            break;
        case 37:
            m_iter += m_reg[3];
            break;
        case 38:
            m_iter -= m_reg[3];
            break;
//        case 39:
//            switch (m_reg[7] % 4)
//            {
//            case 0:
//                if(bots[(x + 1) % (256) + (256 * (y))]->m_rating < m_rating)
//                {
//                    bots[(x + 1) % (256) + (256 * (y))]->setGen(m_reg[3],m_reg[4]);
//                    bots[(x + 1) % (256) + (256 * (y))]->m_genX = x;
//                    bots[(x + 1) % (256) + (256 * (y))]->m_genY = y;
//                }
//                break;
//            case 1:
//                if(bots[(x - 1) % (256) + (256 * (y))]->m_rating < m_rating)
//                {
//                    bots[(x - 1) % (256) + (256 * (y))]->setGen(m_reg[3],m_reg[4]);
//                    bots[(x - 1) % (256) + (256 * (y))]->m_genX = x;
//                    bots[(x - 1) % (256) + (256 * (y))]->m_genY = y;
//                }
//                break;
//            case 2:
//                if(bots[x + (256 * ((y + 1) % (256)))]->m_rating < m_rating)
//                {
//                    bots[x + (256 * ((y + 1) % (256)))]->setGen(m_reg[3],m_reg[4]);
//                    bots[x + (256 * ((y + 1) % (256)))]->m_genX = x;
//                    bots[x + (256 * ((y + 1) % (256)))]->m_genY = y;
//                }
//                break;
//            case 3:
//                if(bots[x + (256 * ((y - 1) % (256)))]->m_rating < m_rating)
//                {
//                    bots[x + (256 * ((y - 1) % (256)))]->setGen(m_reg[3],m_reg[4]);
//                    bots[x + (256 * ((y + 1) % (256)))]->m_genX = x;
//                    bots[x + (256 * ((y + 1) % (256)))]->m_genY = y;
//                }
//                break;
//            }

//            if(m_rating > 0)
//                m_rating--;

//            break;
//        case 40:
//            if(m_rating > 0)
//            {
//                m_rating--;
//                switch (m_reg[7] % 4)
//                {
//                case 0:
//                    bots[(x + 1) % (256) + (256 * (y))]->m_rating++;
//                    break;
//                case 1:
//                    bots[(x - 1) % (256) + (256 * (y))]->m_rating++;
//                    break;
//                case 2:
//                    bots[x + (256 * ((y + 1) % (256)))]->m_rating++;
//                    break;
//                case 3:
//                    bots[x + (256 * ((y - 1) % (256)))]->m_rating++;
//                    break;
//                }
//                break;
//            }
        case 41:
            m_mem[m_reg[5] % 256] += m_gen[m_reg[6] % 256];
            break;
        case 42:
//            m_gen[m_reg[5] % 256] += m_mem[m_reg[6] % 256];
            break;
        case 43:
            std::swap(m_mem[m_reg[7] % 256],m_reg[1]);
            break;
//        case 44:
//            std::swap(m_word[m_reg[7] % 256],m_reg[1]);
//            break;
//        case 46:
//            if(bots[(x + 1) % (256) + (256 * (y))] == empty)
//    //        if(bots[(x + (256 * y))]->m_rating > bots[(x + 1) % (256) + (256 * (y))]->m_rating)
//                std::swap(bots[(x + (256 * y))],bots[(x + 1) % (256) + (256 * (y))]);
//            break;
//        case 47:
//            if(bots[(x - 1) % (256) + (256 * (y))] == empty)
//    //        if(bots[(x + (256 * y))]->m_rating > bots[(x - 1) % (256) + (256 * (y))]->m_rating)
//                std::swap(bots[(x + (256 * y))],bots[(x - 1) % (256) + (256 * (y))]);
//            break;
//        case 48:
//            if(bots[x + (256 * ((y + 1) % (256)))] == empty)
//    //        if(bots[(x + (256 * y))]->m_rating > bots[x + (256 * ((y + 1) % (256)))]->m_rating)
//                std::swap(bots[(x + (256 * y))],bots[x + (256 * ((y + 1) % (256)))]);
//            break;
//        case 49:
//    //        if(bots[(x + (256 * y))]->m_rating > bots[x + (256 * ((y - 1) % (256)))]->m_rating)
//            if(bots[x + (256 * ((y - 1) % (256)))] == empty)
//                std::swap(bots[(x + (256 * y))],bots[x + (256 * ((y - 1) % (256)))]);
//            break;
//        case 50:
//                switch (m_reg[7] % 4)
//                {
//                case 0:
//                    m_reg[5] = bots[(x + 1) % (256) + (256 * (y))]->m_rating;
//                    break;
//                case 1:
//                    m_reg[5] = bots[(x - 1) % (256) + (256 * (y))]->m_rating;
//                    break;
//                case 2:
//                    m_reg[5] = bots[x + (256 * ((y + 1) % (256)))]->m_rating;
//                    break;
//                case 3:
//                    m_reg[5] = bots[x + (256 * ((y - 1) % (256)))]->m_rating;
//                    break;
//                }
//            break;
//        case 51:
//                if(m_rating > 2)
//                {
//                    switch (m_reg[7] % 4)
//                    {
//                    case 0:
//                        if(bots[((x + 1) % (256) + (256 * (y)))] == empty)
//                        {
//                            bots[(x + 1) % (256) + (256 * (y))] = new QBot(false);
//                            bots[(x + 1) % (256) + (256 * (y))]->m_rating = m_rating/2;
//                        }
//                        break;
//                    case 1:
//                        if(bots[(x - 1) % (256) + (256 * (y))] == empty)
//                        {
//                            bots[(x - 1) % (256) + (256 * (y))] = new QBot(false);
//                            bots[(x - 1) % (256) + (256 * (y))]->m_rating = m_rating/2;
//                        }
//                        break;
//                    case 2:
//                        if(bots[x + (256 * ((y + 1) % (256)))] == empty)
//                        {
//                            bots[x + (256 * ((y + 1) % (256)))] = new QBot(false);
//                            bots[x + (256 * ((y + 1) % (256)))]->m_rating = m_rating/2;
//                        }
//                        break;
//                    case 3:
//                        if(bots[x + (256 * ((y - 1) % (256)))] == empty)
//                        {
//                            bots[x + (256 * ((y - 1) % (256)))] = new QBot(false);
//                            bots[x + (256 * ((y - 1) % (256)))]->m_rating = m_rating/2;
//                        }
//                        break;
//                    }
//                    m_rating = m_rating/2;
//                }
//            break;
        default:
            m_gen[m_iter % 256] = rand();
            break;
        }

        break;
    default:
        m_gen[m_iter] = static_cast<uint8_t>(rand() % 256);;
        break;
    }
}

void GenBot::randMe()
{
    for(size_t i = 0; i < 256; i++)
        m_gen[i] = static_cast<uint8_t>(rand() % 256);
}
