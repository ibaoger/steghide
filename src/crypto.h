/*
 * steghide 0.4.5 - a steganography program
 * Copyright (C) 2002 Stefan Hetzl <shetzl@teleweb.at>
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

#ifndef SH_CRYPTO_H
#define SH_CRYPTO_H

#include "io.h"

#define PASSPHRASE_MAXLEN	512

#define CRYPTOALGO_STHDR		"blowfish"
#define CRYPTOALGO_STHDR_COMPAT	"blowfish-compat"
#define CRYPTOMODE_STHDR		"ecb"

#define CRYPTOALGO_DATA			"blowfish"
#define CRYPTOALGO_DATA_COMPAT	"blowfish-compat"
#define CRYPTOMODE_DATA			"cbc"

#ifdef WIN32
#define CRYPTOALGODIR	"./modules/"
#define CRYPTOMODEDIR	"./modules/"
#else
#define CRYPTOALGODIR	NULL
#define CRYPTOMODEDIR	NULL
#endif

#define BLOCKSIZE_BLOWFISH 8

/* function prototypes */
void encrypt_plnfile (PLNFILE *plnfile, char *passphrase) ;
void decrypt_plnfile (PLNFILE *plnfile, char *passphrase) ;
void encrypt_sthdr (void *buf, int buflen, char *passphrase) ;
void decrypt_sthdr (void *buf, int buflen, char *passphrase) ;

#endif /* ndef SH_CRYPTO_H */