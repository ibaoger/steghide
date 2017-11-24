/*
 * steghide 0.4.6b - a steganography program
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

#ifndef SH_JPEGSCANHDR_H
#define SH_JPEGSCANHDR_H

#include "jpegbase.h"

/**
 * \class JpegScanHeader
 * \brief the header of a scan (as determined by the SOS marker)
 **/
class JpegScanHeader : public JpegSegment {
	public:
	JpegScanHeader (void) ;
	JpegScanHeader (BinaryIO *io) ;
	virtual ~JpegScanHeader (void) ;

	/**
	 * read a scan header
	 * \param io the jpeg stream
	 **/
	void read (BinaryIO *io) ;

	/**
	 * write a scan header
	 * \param io the jpeg stream
	 **/
	void write (BinaryIO *io) ;

	/**
	 * return the DC table destination specifier for Component c
	 * \param c the id of the component
	 * \return the DC table destination specifier
	 **/
	unsigned char getDCDestSpec (unsigned char c) ;

	/**
	 * return the AC table destination specifier for Component c
	 * \param c the id of the component
	 * \return the AC table destination specifier
	 **/
	unsigned char getACDestSpec (unsigned char c) ;

	unsigned char getNumComponents (void) ;

	private:
	struct Component {
		unsigned char id ;
		unsigned char DCTable ;
		unsigned char ACTable ;
	} ;
	/// number of image components in scan
	unsigned char numcomponents ;
	/// start of spectral or predictor selection
	unsigned char sospectral ;
	/// end of spectral selection
	unsigned char eospectral ;
	/// sucessive approximation bit position high
	unsigned char ah ;
	/// sucessive approximation bit position low or point transform
	unsigned char al ;
	Component *components ;

	bool isread ;
} ;

#endif // ndef SH_JPEGSCANHDR_H
