#include "aes.hpp"

int     aes::setKey(char *_key)
{
    
    for(int i = 0; i < Nk; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            key[i*4+(3-j)] = _key[i*4+j];
        }
    }

    return expandKey();
}

int     aes::expandKey()
{
    for(int i = 0; i < Nk; i++)
    {
        roundKey[i] = (key[4*i]) | (key[4*i+1] << 8) | (key[4*i+2] << 16) | (key[4*i+3] << 24);
    }
    
    for(int i = Nk; i < (Nb*(Nr+1)); i++)
    {
        uint32_t temp = roundKey[i-1];
        if( i % Nk == 0 )
        {
            printf("\n");
            printf("\t %08x -> %08x -> %08x", temp, rotWord(temp, 1), subWord(rotWord(temp, 1)));
            temp = subWord(rotWord(temp, 1)) ^ (rcon[i/Nk] << 24);
            printf(" -> %08x\n", temp);
        }
        roundKey[i] = roundKey[i-Nk] ^ temp;
    }

    return 0;
}


uint8_t aes::rotByte(uint8_t input, int n)
{
    return __rolb(input, n);
}

uint32_t    aes::rotWord(uint32_t input, int n)
{
    uint32_t output = (input << 8) | ((input >> 24) & 0xff);
    return output;
}

uint32_t    aes::subWord(uint32_t input)
{
    uint8_t byte;
    uint32_t output = 0;
    for(int i = 0; i < 4; i++)
    {
        byte = 0xff & ( input >> (i*8) );
        output |= (s_fwd_aes[byte] << (i*8));
    }
    return output;
}

std::string aes::printRoundKeys(void)
{
    std::string output; 
    for(int i = 0; i < (Nr+1); i++)
    {
        for(int j = 0; j < Nb; j++)
        {
            output.push_back(printf("%d : %08x ", i*Nb+j, roundKey[i*Nb + j]));
        }
        output.push_back(printf("\n"));
    }
    return output;
}

std::string aes::printKey(void)
{
    std::string output;
    for(int i = 0; i < Nk*4; i++)
    {
        output.push_back(printf("%02x ", key[i]));
    }

    return output;
}

int     aes::shiftRow(uint32_t *msg)
{
}

int     aes::encryptBlock(uint32_t *msg)
{
    for(int j = 0; j < Nb; j++)
    {
        msg[j] = (msg[j] ^ roundKey[j]);
    }

    for(int i = 1; i < Nr; i++)
    {
        for(int j = 0; j < Nb; j++)
        {
            msg[j] = subWord(msg[j]);
        }

        shiftRow(msg);
        mixCol(msg);

        for(int j = 0; j < Nb; j++)
        {
            msg[j] = msg[j] ^ roundKey[j];
        }
        
    }
    

    return 0;
}
