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

#ifndef SH_ARG_H
#define SH_ARG_H

#include <string>

#include "stegano.h"

template<class T> class Arg {
	public:
	Arg (void) ;
	Arg (T v, bool setbyuser = true) ;

	T getValue (void) ;
	void setValue (T v, bool setbyuser = true) ;
	bool is_set (void) ;

	protected:
	T value ;
	bool set ;
} ;

enum Command { EMBED, EXTRACT, SHOWVERSION, SHOWLICENSE, SHOWHELP } ;
enum Verbosity { QUIET, NORMAL, VERBOSE } ;

typedef Arg<Command> ArgCommand ;
typedef Arg<unsigned int> ArgUInt ;
typedef Arg<Verbosity> ArgVerbosity ;
typedef Arg<bool> ArgBool ;
typedef Arg<string> ArgString ;
typedef Arg<DMTDINFO> ArgDMTDINFO ;

#endif /* ndef SH_ARG_H */