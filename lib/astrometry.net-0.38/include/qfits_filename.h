/* $Id: qfits_filename.h,v 1.7 2006/02/20 09:45:25 yjung Exp $
 *
 * This file is part of the ESO QFITS Library
 * Copyright (C) 2001-2004 European Southern Observatory
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 * $Author: yjung $
 * $Date: 2006/02/20 09:45:25 $
 * $Revision: 1.7 $
 * $Name: qfits-6_2_0 $
 */

#ifndef QFITS_FILENAME_H
#define QFITS_FILENAME_H

/*-----------------------------------------------------------------------------
                        Function ANSI C prototypes
 -----------------------------------------------------------------------------*/

char * qfits_get_dir_name(const char *);
char * qfits_get_base_name(const char *);
char * qfits_get_root_name(const char *);
char * qfits_get_ext_name(const char *);

#endif
