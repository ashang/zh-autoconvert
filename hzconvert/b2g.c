/*
AutoConvert, a Chinese HZ/GB/Big5 encodings auto-converter
Copyright (C) 1999  �ڹ��  Yu Guanghui <ygh@dlut.edu.cn>

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or any
later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330,
Boston, MA  02111-1307, USA.
*/
/*
 * hack from hztty-2.0(Yongguang ZHANG,1992 COPYRIGHT)
 * by Yu Guanghui <ygh@dlut.edu.cn>
 * 1999.10
 */ 
//$Header: /home/prog/autoconvert/hzconvert/b2g.c,v 1.2 2001/04/28 01:45:46 ygh Exp $
#include "hz.h"

#define	BtoG_bad1 0xa1
#define	BtoG_bad2 0xf5
#define	GtoB_bad1 0xa1
#define	GtoB_bad2 0xbc

extern unsigned char GtoB[], BtoG[];
extern int GtoB_count, BtoG_count;

#define	c1	(unsigned char)(s[0])
#define	c2	(unsigned char)(s[1])

static void g2b(s)
     register char *s;
{
  register unsigned int i;

	if ((c2 >= 0xa1) && (c2 <= 0xfe)) {
		if ((c1 >= 0xa1) && (c1 <= 0xa9)) {
			i = ((c1 - 0xa1) * 94 + (c2 - 0xa1)) * 2;
			s[0] = GtoB[i++];  s[1] = GtoB[i];
			return;
		} else if ((c1 >= 0xb0) && (c1 <= 0xf7)) {
			i = ((c1 - 0xb0 + 9) * 94 + (c2 - 0xa1)) * 2;
			s[0] = GtoB[i++];  s[1] = GtoB[i];
			return;
		}
	}
	s[0] = GtoB_bad1;  s[1] = GtoB_bad2;
}

static void b2g(s)
     register char *s;
{
  register int i;

	if ((c1 >= 0xa1) && (c1 <= 0xf9)) {
		if ((c2 >= 0x40) && (c2 <= 0x7e)) {
			i = ((c1 - 0xa1) * 157 + (c2 - 0x40)) * 2;
			s[0] = BtoG[i++];  s[1] = BtoG[i];
			return;
		} else if ((c2 >= 0xa1) && (c2 <= 0xfe)) {
			i = ((c1 - 0xa1) * 157 + (c2 - 0xa1) + 63) * 2;
			s[0] = BtoG[i++];  s[1] = BtoG[i];
			return;
		}
	}
	s[0] = BtoG_bad1;  s[1] = BtoG_bad2;
}

#undef c1
#undef c2

extern char *hzconvert ();
static char gb2big_savec[MAX_MODULE];
static char big2gb_savec[MAX_MODULE];

int gb2big_init (arg)
     char *arg;
{
/*
  static int gb2big_inst = 0;

	gb2big_savec[gb2big_inst] = '\0';
	return (gb2big_inst++);
*/
	int i;
	for(i=0;i<MAX_MODULE;i++)
		gb2big_savec[i] = '\0';
	return (i++);

}

int big2gb_init (arg)
     char *arg;
{
/*
  static int big2gb_inst = 0;

	big2gb_savec[big2gb_inst] = '\0';
	return (big2gb_inst++);
*/
	int i;
	for(i=0;i<MAX_MODULE;i++)
		big2gb_savec[i] = '\0';
	return (i++);
}

char *gb2big (s,plen,inst)
     char *s;
     int *plen;
     int inst;
{
	return (hzconvert (s, plen, &gb2big_savec[inst], g2b));
}

char *big2gb (s,plen,inst)
     char *s;
     int *plen;
     int inst;
{
	return (hzconvert (s, plen, &big2gb_savec[inst], b2g));
}

