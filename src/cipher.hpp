#ifndef _CIPHER_HPP
#define _CIPHER_HPP

class cipher
{

	public:
		virtual char * encrypt(char *messageText, int length)	{ return NULL; };
		virtual char * decrypt(char *cipherText, int length)	{ return NULL; };
		virtual int set_key(char *key)							{ return 0; };
};


#endif
