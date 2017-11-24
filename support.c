/*
 * steghide 0.4.1 - a steganography program
 * Copyright (C) 2001 Stefan Hetzl <shetzl@teleweb.at>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "support.h"
#include "msg.h"

/* used by the internal random number generator */
#define RND_B		31415821UL
#define RND_MAX		100000000UL
#define RND_M1		10000UL

unsigned long rndgenval = 0 ;

/* multiply p and q avoiding an overflow */
static unsigned long mult (unsigned long p, unsigned long q)
{
    unsigned long p1, p0, q1, q0 ;

    p1 = p / RND_M1 ;
    p0 = p % RND_M1 ;
    q1 = q / RND_M1 ;
    q0 = q % RND_M1 ;

    return (((p0 * q1 + p1 * q0) % RND_M1) * RND_M1 + p0 * q0) % RND_MAX ;
}

void srnd (unsigned long seed)
{
	rndgenval = seed ;
	return ;
}

/* returns pseudo-random value ranging from 0 to max - 1 */
int rnd (unsigned long max)
{
	rndgenval = (mult (rndgenval, RND_B) + 1) % RND_MAX ;
    return (int) (((double) rndgenval / RND_MAX) * max) ;
}

unsigned long readnum (char *s)
{
	unsigned long retval = 0 ;

	if ((s[0] == 'B') || (s[0] == 'b'))
		retval = strtoul ((char *) (s + 1), NULL, 2) ;
	else
		retval = strtoul (s, NULL, 0) ;

	return retval ;
}

void swap (unsigned long *x, unsigned long *y)
{
	unsigned long t ;

	t = *x ;
	*x = *y ;
	*y = t ;
}

char *stripdir (char *filename)
{
	int i = 0, j = 0, start = 0, end = 0 ;
	char *retval = NULL ;

	end = i = strlen (filename) - 1 ;
	while ((i >= 0) && (filename[i] != '\\') && (filename[i] != '/')) {
		i-- ;
	}
	start = i + 1 ;

	if ((retval = malloc (end - start + 2)) == NULL) {
		perr (ERR_MEMALLOC) ;
	}

	j = 0 ;
	for (i = start ; i <= end ; i++, j++) {
		retval[j] = filename [i] ;
	}

	return retval ;
}

int read16_le (FILE *file)
{
	int bytes[2] ;

	bytes[0] = getc (file) ;
	bytes[1] = getc (file) ;

	return ((bytes[1] << 8) | bytes[0]) ;
}

int read16_be (FILE *file)
{
	int bytes[2] ;

	bytes[0] = getc (file) ;
	bytes[1] = getc (file) ;

	return ((bytes[0] << 8) | bytes[1]) ;
}

unsigned long read32_le (FILE *file)
{
	int bytes[4] ;

	bytes[0] = getc (file) ;
	bytes[1] = getc (file) ;
	bytes[2] = getc (file) ;
	bytes[3] = getc (file) ;

	return ((bytes[3] << 24) | (bytes[2] << 16) | (bytes[1] << 8) | bytes[0]) ;
}

unsigned long read32_be (FILE *file)
{
	int bytes[4] ;

	bytes[0] = getc (file) ;
	bytes[1] = getc (file) ;
	bytes[2] = getc (file) ;
	bytes[3] = getc (file) ;

	return ((bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3]) ;
}

void write16_le (FILE *file, int val)
{
	putc (val & 0xFF, file) ;
	putc ((val >> 8) & 0xFF, file) ;
}

void write16_be (FILE *file, int val)
{
	putc ((val >> 8) & 0xFF, file) ;
	putc (val & 0xFF, file) ;
}

void write32_le (FILE *file, unsigned long val)
{
	putc (val & 0xFF, file) ;
	putc ((val >> 8) & 0xFF, file) ;
	putc ((val >> 16) & 0xFF, file) ;
	putc ((val >> 24) & 0xFF, file) ;
}

void write32_be (FILE *file, unsigned long val)
{
	putc ((val >> 24) & 0xFF, file) ;
	putc ((val >> 16) & 0xFF, file) ;
	putc ((val >> 8) & 0xFF, file) ;
	putc (val & 0xFF, file) ;
}

void cp32ul2uc_be (unsigned char *dest, unsigned long src)
{
	dest[0] = (src >> 24) & 0xFF ;
	dest[1] = (src >> 16) & 0xFF ;
	dest[2] = (src >> 8) & 0xFF ;
	dest[3] = src & 0xFF ;
}

void cp32uc2ul_be (unsigned long *dest, unsigned char *src)
{
	*dest = src[0] << 24 ;
	*dest += src[1] << 16 ;
	*dest += src[2] << 8 ;
	*dest += src[3] ;
}

void cp32ul2uc_le (unsigned char *dest, unsigned long src)
{
	dest[0] = src & 0xFF ;
	dest[1] = (src >> 8) & 0xFF ;
	dest[2] = (src >> 16) & 0xFF ;
	dest[3] = (src >> 24) & 0xFF ;
}

void cp32uc2ul_le (unsigned long *dest, unsigned char *src)
{
	*dest = src[0] ;
	*dest += src[1] << 8 ;
	*dest += src[2] << 16 ;
	*dest += src[3] << 24 ;
}

unsigned int cp_bits_to_buf_le (void *buf, unsigned int bufbitpos, unsigned long val, unsigned int val_nbits)
{
	unsigned int curbit = 0 ;
	unsigned int valbitpos = 0 ;
	unsigned char *dest = buf ;

	for (valbitpos = 0 ; valbitpos < val_nbits ; valbitpos++) {
		curbit = ((1 << valbitpos) & val) >> valbitpos ;
		dest[bufbitpos / 8] |= curbit << (bufbitpos % 8) ;
		bufbitpos++ ;
	}

	return bufbitpos ;
}

unsigned int cp_bits_from_buf_le (void *buf, unsigned int bufbitpos, unsigned long *val, unsigned int val_nbits)
{
	unsigned int curbit = 0 ;
	unsigned int valbitpos = 0 ;
	unsigned char *src = buf ;

	*val = 0 ;
	for (valbitpos = 0 ; valbitpos < val_nbits ; valbitpos++) {
		curbit = ((1 << (bufbitpos % 8)) & src[bufbitpos / 8]) >> (bufbitpos % 8) ;
		*val |= curbit << valbitpos ;
		bufbitpos++ ;
	}

	return bufbitpos ;
}
 
/* returns minimal number of bits needed to save x */
unsigned int nbits (unsigned long x)
{
	unsigned int n = 0 ;
	unsigned long y = 1 ;

	if (x == 0) {
		return 1 ;
	}

	while (x > (y - 1)) {
		y = y * 2 ;
		n = n + 1 ;
	}

	return n ;
}
