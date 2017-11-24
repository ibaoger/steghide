/*
 * steghide 0.4.6 - a steganography program
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

#ifndef SH_JPEGJFIFAPP0_H
#define SH_JPEGJFIFAPP0_H

#include <string>

#include "binaryio.h"
#include "bufmanag.h"
#include "jpegbase.h"

/**
 * \class JpegJFIFAPP0
 * \brief JFIF APP0 segment
 **/
class JpegJFIFAPP0 : public JpegSegment {
	public:
	JpegJFIFAPP0 (void) ;
	JpegJFIFAPP0 (BinaryIO *io) ;
	virtual ~JpegJFIFAPP0 (void) ;

	/**
	 * read a JFIF APP0 marker segment
	 * \param io the jpeg stream
	 **/
	void read (BinaryIO *io) ;

	/**
	 * write a JFIF APP0 marker segment
	 * \param io the jpeg stream
	 **/
	void write (BinaryIO *io) ;

	private:
	string identifier ;	
	unsigned int version ;
	unsigned char units ;
	unsigned int Xdensity ;
	unsigned int Ydensity ;
	unsigned char Xthumbnail ;
	unsigned char Ythumbnail ;
	BUFFER *thumbnail ;
} ;

#endif // ndef SH_JPEGJFIFAPP0_H