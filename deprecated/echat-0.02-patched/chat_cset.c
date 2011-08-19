/*  chat_cset.c
 *
 *  copyright (c) 2000-2003 SeaD
 *  see GPL for copying info
 *
 */

#ifdef  CHARSET

#include "echat.h"

/* SERGEJ */

#include <string.h>

#define SIZE (2*MSG_SIZE)

char buf1[SIZE];
char buf2[SIZE];

struct cp_s
{
    unsigned char cp1251;
    unsigned short utf8;
} cp[] = {
    { 0xC0, 0x90D0 }, /* � */
    { 0xC1, 0x91D0 }, /* � */
    { 0xC2, 0x92D0 }, /* � */
    { 0xC3, 0x93D0 }, /* � */
    { 0xC4, 0x94D0 }, /* � */
    { 0xC5, 0x95D0 }, /* � */
    { 0xA8, 0x81D0 }, /* � */
    { 0xC6, 0x96D0 }, /* � */
    { 0xC7, 0x97D0 }, /* � */
    { 0xC8, 0x98D0 }, /* � */
    { 0xC9, 0x99D0 }, /* � */
    { 0xCA, 0x9AD0 }, /* � */
    { 0xCB, 0x9BD0 }, /* � */
    { 0xCC, 0x9CD0 }, /* � */
    { 0xCD, 0x9DD0 }, /* � */
    { 0xCE, 0x9ED0 }, /* � */
    { 0xCF, 0x9FD0 }, /* � */
    { 0xD0, 0xA0D0 }, /* � */
    { 0xD1, 0xA1D0 }, /* � */
    { 0xD2, 0xA2D0 }, /* � */
    { 0xD3, 0xA3D0 }, /* � */
    { 0xD4, 0xA4D0 }, /* � */
    { 0xD5, 0xA5D0 }, /* � */
    { 0xD6, 0xA6D0 }, /* � */
    { 0xD7, 0xA7D0 }, /* � */
    { 0xD8, 0xA8D0 }, /* � */
    { 0xD9, 0xA9D0 }, /* � */
    { 0xDC, 0xACD0 }, /* � */
    { 0xDB, 0xABD0 }, /* � */
    { 0xDA, 0xAAD0 }, /* � */
    { 0xDD, 0xADD0 }, /* � */
    { 0xDE, 0xAED0 }, /* � */
    { 0xDF, 0xAFD0 }, /* � */
    { 0xE0, 0xB0D0 }, /* � */
    { 0xE1, 0xB1D0 }, /* � */
    { 0xE2, 0xB2D0 }, /* � */
    { 0xE3, 0xB3D0 }, /* � */
    { 0xE4, 0xB4D0 }, /* � */
    { 0xE5, 0xB5D0 }, /* � */
    { 0xB8, 0x91D1 }, /* � */
    { 0xE6, 0xB6D0 }, /* � */
    { 0xE7, 0xB7D0 }, /* � */
    { 0xE8, 0xB8D0 }, /* � */
    { 0xE9, 0xB9D0 }, /* � */
    { 0xEA, 0xBAD0 }, /* � */
    { 0xEB, 0xBBD0 }, /* � */
    { 0xEC, 0xBCD0 }, /* � */
    { 0xED, 0xBDD0 }, /* � */
    { 0xEE, 0xBED0 }, /* � */
    { 0xEF, 0xBFD0 }, /* � */
    { 0xF0, 0x80D1 }, /* � */
    { 0xF1, 0x81D1 }, /* � */
    { 0xF2, 0x82D1 }, /* � */
    { 0xF3, 0x83D1 }, /* � */
    { 0xF4, 0x84D1 }, /* � */
    { 0xF5, 0x85D1 }, /* � */
    { 0xF6, 0x86D1 }, /* � */
    { 0xF7, 0x87D1 }, /* � */
    { 0xF8, 0x88D1 }, /* � */
    { 0xF9, 0x89D1 }, /* � */
    { 0xFC, 0x8CD1 }, /* � */
    { 0xFB, 0x8BD1 }, /* � */
    { 0xFA, 0x8AD1 }, /* � */
    { 0xFD, 0x8DD1 }, /* � */
    { 0xFE, 0x8ED1 }, /* � */
    { 0xFF, 0x8FD1 }, /* � */
    { 0xA9, 0xA9C2 }, /* (c) */
    { 0xAE, 0xAEC2 }, /* (r) */
};

char xreplace(unsigned short ch, int *replaced)
{
    int i;

	*replaced = 0;

    for(i=0; i<66; i++)
    {
        if(ch == cp[i].utf8)
        {
			*replaced = 1;
            return cp[i].cp1251;
        }
    }
    return ch & 0xFF;
}


void xrecode(char *buf, int size)
{
    int i;
	int replaced = 0;
    unsigned char *sptr = buf1;
    unsigned char *dptr = buf2;

    memset(buf1, 0, sizeof(buf1));
    memset(buf2, 0, sizeof(buf2));

    memcpy(buf1, buf, size);

    for(i=0; i<SIZE; i++)
    {
        unsigned short ch1 = *sptr;
        unsigned short ch2 = *(sptr+1);
		replaced = 0;
		if(ch1>=32)
		{
        	*dptr = xreplace(ch1 | (ch2 << 8), &replaced);
		}
		else
		{
        	*dptr = *sptr;
		}

        if(replaced)
        {
            sptr += 2;
        }
        else
        {
            sptr++;
        }
        dptr++;
    }

    memcpy(buf, buf2, size);
}
/* SERGEJ */

void cset_inout(void) {
    char src[] =        /* russian cyrillic koi8-r codepage */
        { 191, 148, 163, 193,194,215,199,196,197,214,218,201,202,203,204,205,206,207,208,210,211,212,213,198,200,195,222,219,221,223,217,216,220,192,209,
          179, 225,226,247,231,228,229,246,250,233,234,235,236,237,238,239,240,242,243,244,245,230,232,227,254,251,253,255,249,248,252,224,241 };
    char dst[] =        /* russian insane 1251 codepage */
        { 169, 174, 184, 224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255,
          168, 192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223 };
    register int n, m;

    for (n = 0; n < MSG_SIZE; n++)
        if (packet[n] < 0)
            for (m = 0; m < sizeof(src); m++)
                if (packet[n] == src[m]) { packet[n] = dst[m]; break; }
}

void cset_outin(void) {
    char dst[] =        /* russian cyrillic koi8-r codepage */
        { 191, 148, 163, 193,194,215,199,196,197,214,218,201,202,203,204,205,206,207,208,210,211,212,213,198,200,195,222,219,221,223,217,216,220,192,209,
          179, 225,226,247,231,228,229,246,250,233,234,235,236,237,238,239,240,242,243,244,245,230,232,227,254,251,253,255,249,248,252,224,241 };
    char src[] =        /* russian insane 1251 codepage */
        { 169, 174, 184, 224,225,226,227,228,229,230,231,232,233,234,235,236,237,238,239,240,241,242,243,244,245,246,247,248,249,250,251,252,253,254,255,
          168, 192,193,194,195,196,197,198,199,200,201,202,203,204,205,206,207,208,209,210,211,212,213,214,215,216,217,218,219,220,221,222,223 };
    register int n, m;

/* SERGEJ */
{
    xrecode(packet, MSG_SIZE);
}
/* SERGEJ */

    for (n = 0; n < MSG_SIZE; n++)
        if (packet[n] < 0)
            for (m = 0; m < sizeof(src); m++)
                if (packet[n] == src[m]) { packet[n] = dst[m]; break; }
}

void cset_string(void) {
    char kbd[] =        /* keyboard layout */
        { '`', 'f',',','d','u','l','t',';','p','b','q','r','k','v','y','j','g','h','c','n','e','a','[','w','x','i','o',223,'s','m','\'','.','z',
          '~', 'F','<','D','U','L','T',':','P','B','Q','R','K','V','Y','J','G','H','C','N','E','A','{','W','X','I','O',255,'S','M','\"','>','Z' };
    char chr[] =        /* russian cyrillic koi8-r codepage */
        { 163, 193,194,215,199,196,197,214,218,201,202,203,204,205,206,207,208,210,211,212,213,198,200,195,222,219,221,223,217,216,220,192,209,
          179, 225,226,247,231,228,229,246,250,233,234,235,236,237,238,239,240,242,243,244,245,230,232,227,254,251,253,255,249,248,252,224,241 };
    register int n, m;

    for (n = 0; n < STR_SIZE; n++)
        for (m = 0; m < sizeof(kbd); m++) {
            if (buf[n] == kbd[m]) { buf[n] = chr[m]; break; }
            if (buf[n] == chr[m]) { buf[n] = kbd[m]; break; }
        }
}

#endif  /* CHARSET */
