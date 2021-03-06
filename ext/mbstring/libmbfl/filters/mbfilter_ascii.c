/*
 * "streamable kanji code filter and converter"
 * Copyright (c) 1998-2002 HappySize, Inc. All rights reserved.
 *
 * LICENSE NOTICES
 *
 * This file is part of "streamable kanji code filter and converter",
 * which is distributed under the terms of GNU Lesser General Public
 * License (version 2) as published by the Free Software Foundation.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with "streamable kanji code filter and converter";
 * if not, write to the Free Software Foundation, Inc., 59 Temple Place,
 * Suite 330, Boston, MA  02111-1307  USA
 *
 * The author of this file:
 *
 */
/*
 * The source code included in this files was separated from mbfilter.c
 * by Moriyoshi Koizumi <moriyoshi@php.net> on 4 Dec 2002. The file
 * mbfilter.c is included in this package .
 *
 */

#include "mbfilter.h"
#include "mbfilter_ascii.h"

static const char *mbfl_encoding_ascii_aliases[] = {"ANSI_X3.4-1968", "iso-ir-6", "ANSI_X3.4-1986", "ISO_646.irv:1991", "US-ASCII", "ISO646-US", "us", "IBM367", "IBM-367", "cp367", "csASCII", NULL};

const mbfl_encoding mbfl_encoding_ascii = {
	mbfl_no_encoding_ascii,
	"ASCII",
	"US-ASCII", /* preferred MIME name */
	mbfl_encoding_ascii_aliases,
	NULL,
	MBFL_ENCTYPE_SBCS,
	&vtbl_ascii_wchar,
	&vtbl_wchar_ascii
};

const struct mbfl_convert_vtbl vtbl_ascii_wchar = {
	mbfl_no_encoding_ascii,
	mbfl_no_encoding_wchar,
	mbfl_filt_conv_common_ctor,
	NULL,
	mbfl_filt_conv_ascii_wchar,
	mbfl_filt_conv_common_flush,
	NULL,
};

const struct mbfl_convert_vtbl vtbl_wchar_ascii = {
	mbfl_no_encoding_wchar,
	mbfl_no_encoding_ascii,
	mbfl_filt_conv_common_ctor,
	NULL,
	mbfl_filt_conv_wchar_ascii,
	mbfl_filt_conv_common_flush,
	NULL,
};

#define CK(statement)	do { if ((statement) < 0) return (-1); } while (0)

/*
 * ASCII => wchar
 */
int mbfl_filt_conv_ascii_wchar(int c, mbfl_convert_filter *filter)
{
	if (c < 0x80) {
		(*filter->output_function)(c, filter->data);
	} else {
		(*filter->output_function)(c | MBFL_WCSGROUP_THROUGH, filter->data);
	}
	return c;
}


/*
 * wchar => ASCII
 */
int mbfl_filt_conv_wchar_ascii(int c, mbfl_convert_filter *filter)
{
	if (c >= 0 && c < 0x80) {
		CK((*filter->output_function)(c, filter->data));
	} else {
		CK(mbfl_filt_conv_illegal_output(c, filter));
	}

	return c;
}
