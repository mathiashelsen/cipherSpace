#ifndef _BLOCKCIPHER_HPP
#define _BLOCKCIPHER_HPP

#include <cstddef>

class blockCipher
{

	public:
		virtual char *	encrypt(char *messageText, int length)	{ return NULL; };
		virtual char *	decrypt(char *cipherText, int length)	{ return NULL; };
		virtual int		set_key(char *key)						{ return 0; };
};


#endif
