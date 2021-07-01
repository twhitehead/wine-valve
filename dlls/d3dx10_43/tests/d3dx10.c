/*
 * Copyright 2016 Nikolay Sivov for CodeWeavers
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#define COBJMACROS
#include "initguid.h"
#include "d3d10_1.h"
#include "d3dx10.h"
#include "wine/test.h"

/* 1x1 1bpp bmp image */
static const BYTE test_bmp_1bpp[] =
{
    0x42, 0x4d, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x28, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x12, 0x0b, 0x00, 0x00, 0x12, 0x0b, 0x00, 0x00, 0x02, 0x00,
    0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xf1, 0xf2, 0xf3, 0x80, 0xf4, 0xf5, 0xf6, 0x81, 0x00, 0x00,
    0x00, 0x00
};
static const BYTE test_bmp_1bpp_data[] =
{
    0xf3, 0xf2, 0xf1, 0xff
};

/* 1x1 4bpp bmp image */
static const BYTE test_bmp_4bpp[] =
{
    0x42, 0x4d, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x28, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x12, 0x0b, 0x00, 0x00, 0x12, 0x0b, 0x00, 0x00, 0x02, 0x00,
    0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xf1, 0xf2, 0xf3, 0x80, 0xf4, 0xf5, 0xf6, 0x81, 0x00, 0x00,
    0x00, 0x00
};
static const BYTE test_bmp_4bpp_data[] =
{
    0xf3, 0xf2, 0xf1, 0xff
};

/* 1x1 8bpp bmp image */
static const BYTE test_bmp_8bpp[] =
{
    0x42, 0x4d, 0x42, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x28, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x08, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x12, 0x0b, 0x00, 0x00, 0x12, 0x0b, 0x00, 0x00, 0x02, 0x00,
    0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0xf1, 0xf2, 0xf3, 0x80, 0xf4, 0xf5, 0xf6, 0x81, 0x00, 0x00,
    0x00, 0x00
};
static const BYTE test_bmp_8bpp_data[] =
{
    0xf3, 0xf2, 0xf1, 0xff
};

/* 1x1 16bpp bmp image */
static const BYTE test_bmp_16bpp[] =
{
    0x42, 0x4d, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0x28, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x10, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x12, 0x0b, 0x00, 0x00, 0x12, 0x0b, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e, 0x42, 0x00, 0x00, 0x00, 0x00
};
static const BYTE test_bmp_16bpp_data[] =
{
    0x84, 0x84, 0x73, 0xff
};

/* 1x1 24bpp bmp image */
static const BYTE test_bmp_24bpp[] =
{
    0x42, 0x4d, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0x28, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x18, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x12, 0x0b, 0x00, 0x00, 0x12, 0x0b, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x73, 0x84, 0x84, 0x00, 0x00, 0x00
};
static const BYTE test_bmp_24bpp_data[] =
{
    0x84, 0x84, 0x73, 0xff
};

/* 2x2 32bpp XRGB bmp image */
static const BYTE test_bmp_32bpp_xrgb[] =
{
    0x42, 0x4d, 0x46, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0x28, 0x00,
    0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x12, 0x0b, 0x00, 0x00, 0x12, 0x0b, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa0, 0xb0, 0xc0, 0x00, 0xa1, 0xb1, 0xc1, 0x00, 0xa2, 0xb2,
    0xc2, 0x00, 0xa3, 0xb3, 0xc3, 0x00
};
static const BYTE test_bmp_32bpp_xrgb_data[] =
{
    0xc2, 0xb2, 0xa2, 0xff, 0xc3, 0xb3, 0xa3, 0xff, 0xc0, 0xb0, 0xa0, 0xff, 0xc1, 0xb1, 0xa1, 0xff

};

/* 2x2 32bpp ARGB bmp image */
static const BYTE test_bmp_32bpp_argb[] =
{
    0x42, 0x4d, 0x46, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x36, 0x00, 0x00, 0x00, 0x28, 0x00,
    0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x01, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x12, 0x0b, 0x00, 0x00, 0x12, 0x0b, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xa0, 0xb0, 0xc0, 0x00, 0xa1, 0xb1, 0xc1, 0x00, 0xa2, 0xb2,
    0xc2, 0x00, 0xa3, 0xb3, 0xc3, 0x01
};
static const BYTE test_bmp_32bpp_argb_data[] =
{
    0xc2, 0xb2, 0xa2, 0xff, 0xc3, 0xb3, 0xa3, 0xff, 0xc0, 0xb0, 0xa0, 0xff, 0xc1, 0xb1, 0xa1, 0xff

};

/* 1x1 8bpp gray png image */
static const BYTE test_png_8bpp_gray[] =
{
    0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d, 0x49, 0x48, 0x44, 0x52,
    0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x08, 0x00, 0x00, 0x00, 0x00, 0x3a, 0x7e, 0x9b,
    0x55, 0x00, 0x00, 0x00, 0x0a, 0x49, 0x44, 0x41, 0x54, 0x08, 0xd7, 0x63, 0xf8, 0x0f, 0x00, 0x01,
    0x01, 0x01, 0x00, 0x1b, 0xb6, 0xee, 0x56, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae,
    0x42, 0x60, 0x82
};
static const BYTE test_png_8bpp_gray_data[] =
{
    0xff, 0xff, 0xff, 0xff
};

/* 1x1 jpg image */
static const BYTE test_jpg[] =
{
    0xff, 0xd8, 0xff, 0xe0, 0x00, 0x10, 0x4a, 0x46, 0x49, 0x46, 0x00, 0x01, 0x01, 0x01, 0x01, 0x2c,
    0x01, 0x2c, 0x00, 0x00, 0xff, 0xdb, 0x00, 0x43, 0x00, 0x05, 0x03, 0x04, 0x04, 0x04, 0x03, 0x05,
    0x04, 0x04, 0x04, 0x05, 0x05, 0x05, 0x06, 0x07, 0x0c, 0x08, 0x07, 0x07, 0x07, 0x07, 0x0f, 0x0b,
    0x0b, 0x09, 0x0c, 0x11, 0x0f, 0x12, 0x12, 0x11, 0x0f, 0x11, 0x11, 0x13, 0x16, 0x1c, 0x17, 0x13,
    0x14, 0x1a, 0x15, 0x11, 0x11, 0x18, 0x21, 0x18, 0x1a, 0x1d, 0x1d, 0x1f, 0x1f, 0x1f, 0x13, 0x17,
    0x22, 0x24, 0x22, 0x1e, 0x24, 0x1c, 0x1e, 0x1f, 0x1e, 0xff, 0xdb, 0x00, 0x43, 0x01, 0x05, 0x05,
    0x05, 0x07, 0x06, 0x07, 0x0e, 0x08, 0x08, 0x0e, 0x1e, 0x14, 0x11, 0x14, 0x1e, 0x1e, 0x1e, 0x1e,
    0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e,
    0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e,
    0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0x1e, 0xff, 0xc0,
    0x00, 0x11, 0x08, 0x00, 0x01, 0x00, 0x01, 0x03, 0x01, 0x22, 0x00, 0x02, 0x11, 0x01, 0x03, 0x11,
    0x01, 0xff, 0xc4, 0x00, 0x15, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0xff, 0xc4, 0x00, 0x14, 0x10, 0x01, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xc4,
    0x00, 0x14, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0xff, 0xc4, 0x00, 0x14, 0x11, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xda, 0x00, 0x0c, 0x03, 0x01,
    0x00, 0x02, 0x11, 0x03, 0x11, 0x00, 0x3f, 0x00, 0xb2, 0xc0, 0x07, 0xff, 0xd9
};
static const BYTE test_jpg_data[] =
{
    0xff, 0xff, 0xff, 0xff
};

/* 1x1 gif image */
static const BYTE test_gif[] =
{
    0x47, 0x49, 0x46, 0x38, 0x37, 0x61, 0x01, 0x00, 0x01, 0x00, 0x80, 0x00, 0x00, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0x2c, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x02, 0x02, 0x44,
    0x01, 0x00, 0x3b
};
static const BYTE test_gif_data[] =
{
    0xff, 0xff, 0xff, 0xff
};

/* 1x1 tiff image */
static const BYTE test_tiff[] =
{
    0x49, 0x49, 0x2a, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0xfe, 0x00,
    0x04, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x00, 0x01, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x03, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x00, 0x00, 0x02, 0x01, 0x03, 0x00, 0x03, 0x00, 0x00, 0x00, 0xd2, 0x00, 0x00, 0x00, 0x03, 0x01,
    0x03, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x06, 0x01, 0x03, 0x00, 0x01, 0x00,
    0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x0d, 0x01, 0x02, 0x00, 0x1b, 0x00, 0x00, 0x00, 0xd8, 0x00,
    0x00, 0x00, 0x11, 0x01, 0x04, 0x00, 0x01, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x12, 0x01,
    0x03, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x15, 0x01, 0x03, 0x00, 0x01, 0x00,
    0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x16, 0x01, 0x03, 0x00, 0x01, 0x00, 0x00, 0x00, 0x40, 0x00,
    0x00, 0x00, 0x17, 0x01, 0x04, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x1a, 0x01,
    0x05, 0x00, 0x01, 0x00, 0x00, 0x00, 0xf4, 0x00, 0x00, 0x00, 0x1b, 0x01, 0x05, 0x00, 0x01, 0x00,
    0x00, 0x00, 0xfc, 0x00, 0x00, 0x00, 0x1c, 0x01, 0x03, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x00, 0x00, 0x28, 0x01, 0x03, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x08, 0x00, 0x08, 0x00, 0x08, 0x00, 0x2f, 0x68, 0x6f, 0x6d, 0x65, 0x2f, 0x6d, 0x65,
    0x68, 0x2f, 0x44, 0x65, 0x73, 0x6b, 0x74, 0x6f, 0x70, 0x2f, 0x74, 0x65, 0x73, 0x74, 0x2e, 0x74,
    0x69, 0x66, 0x00, 0x00, 0x00, 0x00, 0x00, 0x48, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x48,
    0x00, 0x00, 0x00, 0x01
};
static const BYTE test_tiff_data[] =
{
    0x00, 0x00, 0x00, 0xff
};

/* 1x1 alpha dds image */
static const BYTE test_dds_alpha[] =
{
    0x44, 0x44, 0x53, 0x20, 0x7c, 0x00, 0x00, 0x00, 0x07, 0x10, 0x08, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xff
};
static const BYTE test_dds_alpha_data[] =
{
    0xff
};

/* 1x1 luminance dds image */
static const BYTE test_dds_luminance[] =
{
    0x44, 0x44, 0x53, 0x20, 0x7c, 0x00, 0x00, 0x00, 0x07, 0x10, 0x08, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x82
};
static const BYTE test_dds_luminance_data[] =
{
    0x82, 0x82, 0x82, 0xff
};

/* 1x1 16bpp dds image */
static const BYTE test_dds_16bpp[] =
{
    0x44, 0x44, 0x53, 0x20, 0x7c, 0x00, 0x00, 0x00, 0x07, 0x10, 0x08, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x00, 0x00,
    0xe0, 0x03, 0x00, 0x00, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x0e, 0x42
};
static const BYTE test_dds_16bpp_data[] =
{
    0x84, 0x84, 0x73, 0xff
};

/* 1x1 24bpp dds image */
static const BYTE test_dds_24bpp[] =
{
    0x44, 0x44, 0x53, 0x20, 0x7c, 0x00, 0x00, 0x00, 0x07, 0x10, 0x08, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00,
    0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x70, 0x81, 0x83
};
static const BYTE test_dds_24bpp_data[] =
{
    0x83, 0x81, 0x70, 0xff
};

/* 1x1 32bpp dds image */
static const BYTE test_dds_32bpp[] =
{
    0x44, 0x44, 0x53, 0x20, 0x7c, 0x00, 0x00, 0x00, 0x07, 0x10, 0x08, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00,
    0x00, 0xff, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x10, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x70, 0x81, 0x83, 0xff
};
static const BYTE test_dds_32bpp_data[] =
{
    0x83, 0x81, 0x70, 0xff
};

/* 1x1 64bpp dds image */
static const BYTE test_dds_64bpp[] =
{
    0x44, 0x44, 0x53, 0x20, 0x7c, 0x00, 0x00, 0x00, 0x0f, 0x10, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x83, 0x83, 0x81, 0x81, 0x70, 0x70, 0xff, 0xff
};
static const BYTE test_dds_64bpp_data[] =
{
    0x83, 0x83, 0x81, 0x81, 0x70, 0x70, 0xff, 0xff
};

/* 1x1 96bpp dds image */
static const BYTE test_dds_96bpp[] =
{
    0x44, 0x44, 0x53, 0x20, 0x7c, 0x00, 0x00, 0x00, 0x0f, 0x10, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x44, 0x58, 0x31, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x06, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x84, 0x83, 0x03, 0x3f, 0x82, 0x81, 0x01, 0x3f, 0xe2, 0xe0, 0xe0, 0x3e
};
static const BYTE test_dds_96bpp_data[] =
{
    0x84, 0x83, 0x03, 0x3f, 0x82, 0x81, 0x01, 0x3f, 0xe2, 0xe0, 0xe0, 0x3e
};

/* 1x1 128bpp dds image */
static const BYTE test_dds_128bpp[] =
{
    0x44, 0x44, 0x53, 0x20, 0x7c, 0x00, 0x00, 0x00, 0x0f, 0x10, 0x02, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x74, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x84, 0x83, 0x03, 0x3f, 0x82, 0x81, 0x01, 0x3f, 0xe2, 0xe0, 0xe0, 0x3e, 0x00, 0x00, 0x80, 0x3f
};
static const BYTE test_dds_128bpp_data[] =
{
    0x84, 0x83, 0x03, 0x3f, 0x82, 0x81, 0x01, 0x3f, 0xe2, 0xe0, 0xe0, 0x3e, 0x00, 0x00, 0x80, 0x3f

};

/* 4x4 DXT1 dds image */
static const BYTE test_dds_dxt1[] =
{
    0x44, 0x44, 0x53, 0x20, 0x7c, 0x00, 0x00, 0x00, 0x07, 0x10, 0x08, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x44, 0x58, 0x54, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x2a, 0x31, 0xf5, 0xbc, 0xe3, 0x6e, 0x2a, 0x3a
};
static const BYTE test_dds_dxt1_data[] =
{
    0x2a, 0x31, 0xf5, 0xbc, 0xe3, 0x6e, 0x2a, 0x3a
};

/* 4x4 DXT2 dds image */
static const BYTE test_dds_dxt2[] =
{
    0x44, 0x44, 0x53, 0x20, 0x7c, 0x00, 0x00, 0x00, 0x07, 0x10, 0x02, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x44, 0x58, 0x54, 0x32, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x10, 0x40, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xde, 0xc4, 0x10, 0x2f, 0xbf, 0xff, 0x7b,
    0xff, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x57, 0x53, 0x00, 0x00, 0x52, 0x52, 0x55, 0x55,
    0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xce, 0x59, 0x00, 0x00, 0x54, 0x55, 0x55, 0x55
};
static const BYTE test_dds_dxt2_data[] =
{
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xde, 0xc4, 0x10, 0x2f, 0xbf, 0xff, 0x7b

};

/* 1x3 DXT3 dds image */
static const BYTE test_dds_dxt3[] =
{
    0x44, 0x44, 0x53, 0x20, 0x7c, 0x00, 0x00, 0x00, 0x07, 0x10, 0x0a, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x01, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x44, 0x58, 0x54, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x10, 0x40, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0c, 0x92, 0x38, 0x84, 0x00, 0xff, 0x55, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x53, 0x8b, 0x53, 0x8b, 0x00, 0x00, 0x00, 0x00
};
static const BYTE test_dds_dxt3_data[] =
{
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x4e, 0x92, 0xd6, 0x83, 0x00, 0xaa, 0x55, 0x55

};

/* 4x4 DXT4 dds image */
static const BYTE test_dds_dxt4[] =
{
    0x44, 0x44, 0x53, 0x20, 0x7c, 0x00, 0x00, 0x00, 0x07, 0x10, 0x02, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x44, 0x58, 0x54, 0x34, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x10, 0x40, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd, 0xde, 0xc4, 0x10, 0x2f, 0xbf, 0xff, 0x7b,
    0xff, 0x00, 0x40, 0x02, 0x24, 0x49, 0x92, 0x24, 0x57, 0x53, 0x00, 0x00, 0x52, 0x52, 0x55, 0x55,
    0xff, 0x00, 0x48, 0x92, 0x24, 0x49, 0x92, 0x24, 0xce, 0x59, 0x00, 0x00, 0x54, 0x55, 0x55, 0x55
};
static const BYTE test_dds_dxt4_data[] =
{
    0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfd, 0xde, 0xc4, 0x10, 0x2f, 0xbf, 0xff, 0x7b

};

/* 4x2 DXT5 dds image */
static const BYTE test_dds_dxt5[] =
{
    0x44, 0x44, 0x53, 0x20, 0x7c, 0x00, 0x00, 0x00, 0x07, 0x10, 0x08, 0x00, 0x02, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x44, 0x58, 0x54, 0x35, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x10, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xef, 0x87, 0x0f, 0x78, 0x05, 0x05, 0x50, 0x50
};
static const BYTE test_dds_dxt5_data[] =
{
    0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xef, 0x87, 0x0f, 0x78, 0x05, 0x05, 0x05, 0x05

};

/* 4x4 BC4 dds image */
static const BYTE test_dds_bc4[] =
{
    0x44, 0x44, 0x53, 0x20, 0x7c, 0x00, 0x00, 0x00, 0x07, 0x10, 0x0a, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x42, 0x43, 0x34, 0x55, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x10, 0x40, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xd9, 0x15, 0xbc, 0x41, 0x5b, 0xa3, 0x3d, 0x3a, 0x8f, 0x3d, 0x45, 0x81, 0x20, 0x45, 0x81, 0x20,
    0x6f, 0x6f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
static const BYTE test_dds_bc4_data[] =
{
    0xd9, 0x15, 0xbc, 0x41, 0x5b, 0xa3, 0x3d, 0x3a
};

/* 6x3 BC5 dds image */
static const BYTE test_dds_bc5[] =
{
    0x44, 0x44, 0x53, 0x20, 0x7c, 0x00, 0x00, 0x00, 0x07, 0x10, 0x0a, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x06, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x42, 0x43, 0x35, 0x55, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x10, 0x40, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x9f, 0x28, 0x73, 0xac, 0xd5, 0x80, 0xaa, 0xd5, 0x70, 0x2c, 0x4e, 0xd6, 0x76, 0x1d, 0xd6, 0x76,
    0xd5, 0x0f, 0xc3, 0x50, 0x96, 0xcf, 0x53, 0x96, 0xdf, 0x16, 0xc3, 0x50, 0x96, 0xcf, 0x53, 0x96,
    0x83, 0x55, 0x08, 0x83, 0x30, 0x08, 0x83, 0x30, 0x79, 0x46, 0x31, 0x1c, 0xc3, 0x31, 0x1c, 0xc3,
    0x6d, 0x6d, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x5c, 0x5c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};
static const BYTE test_dds_bc5_data[] =
{
    0x95, 0x35, 0xe2, 0xa3, 0xf5, 0xd2, 0x28, 0x68, 0x65, 0x32, 0x7c, 0x4e, 0xdb, 0xe4, 0x56, 0x0a,
    0xb9, 0x33, 0xaf, 0xf0, 0x52, 0xbe, 0xed, 0x27, 0xb4, 0x2e, 0xa6, 0x60, 0x4e, 0xb6, 0x5d, 0x3f

};

/* 4x4 DXT1 cube map */
static const BYTE test_dds_cube[] =
{
    0x44, 0x44, 0x53, 0x20, 0x7c, 0x00, 0x00, 0x00, 0x07, 0x10, 0x0a, 0x00, 0x04, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x03, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00,
    0x04, 0x00, 0x00, 0x00, 0x44, 0x58, 0x54, 0x31, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x10, 0x40, 0x00,
    0x00, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xf5, 0xa7, 0x08, 0x69, 0x74, 0xc0, 0xbf, 0xd7, 0x32, 0x96, 0x0b, 0x7b, 0xcc, 0x55, 0xcc, 0x55,
    0x0e, 0x84, 0x0e, 0x84, 0x00, 0x00, 0x00, 0x00, 0xf5, 0xa7, 0x08, 0x69, 0x74, 0xc0, 0xbf, 0xd7,
    0x32, 0x96, 0x0b, 0x7b, 0xcc, 0x55, 0xcc, 0x55, 0x0e, 0x84, 0x0e, 0x84, 0x00, 0x00, 0x00, 0x00,
    0xf5, 0xa7, 0x08, 0x69, 0x74, 0xc0, 0xbf, 0xd7, 0x32, 0x96, 0x0b, 0x7b, 0xcc, 0x55, 0xcc, 0x55,
    0x0e, 0x84, 0x0e, 0x84, 0x00, 0x00, 0x00, 0x00, 0xf5, 0xa7, 0x08, 0x69, 0x74, 0xc0, 0xbf, 0xd7,
    0x32, 0x96, 0x0b, 0x7b, 0xcc, 0x55, 0xcc, 0x55, 0x0e, 0x84, 0x0e, 0x84, 0x00, 0x00, 0x00, 0x00,
    0xf5, 0xa7, 0x08, 0x69, 0x74, 0xc0, 0xbf, 0xd7, 0x32, 0x96, 0x0b, 0x7b, 0xcc, 0x55, 0xcc, 0x55,
    0x0e, 0x84, 0x0e, 0x84, 0x00, 0x00, 0x00, 0x00, 0xf5, 0xa7, 0x08, 0x69, 0x74, 0xc0, 0xbf, 0xd7,
    0x32, 0x96, 0x0b, 0x7b, 0xcc, 0x55, 0xcc, 0x55, 0x0e, 0x84, 0x0e, 0x84, 0x00, 0x00, 0x00, 0x00
};
static const BYTE test_dds_cube_data[] =
{
    0xf5, 0xa7, 0x08, 0x69, 0x74, 0xc0, 0xbf, 0xd7
};

/* 1x1 wmp image */
static const BYTE test_wmp[] =
{
    0x49, 0x49, 0xbc, 0x01, 0x20, 0x00, 0x00, 0x00, 0x24, 0xc3, 0xdd, 0x6f, 0x03, 0x4e, 0xfe, 0x4b,
    0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x08, 0x00, 0x01, 0xbc, 0x01, 0x00, 0x10, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x02, 0xbc,
    0x04, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xbc, 0x04, 0x00, 0x01, 0x00,
    0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x81, 0xbc, 0x04, 0x00, 0x01, 0x00, 0x00, 0x00, 0x01, 0x00,
    0x00, 0x00, 0x82, 0xbc, 0x0b, 0x00, 0x01, 0x00, 0x00, 0x00, 0x25, 0x06, 0xc0, 0x42, 0x83, 0xbc,
    0x0b, 0x00, 0x01, 0x00, 0x00, 0x00, 0x25, 0x06, 0xc0, 0x42, 0xc0, 0xbc, 0x04, 0x00, 0x01, 0x00,
    0x00, 0x00, 0x86, 0x00, 0x00, 0x00, 0xc1, 0xbc, 0x04, 0x00, 0x01, 0x00, 0x00, 0x00, 0x92, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x57, 0x4d, 0x50, 0x48, 0x4f, 0x54, 0x4f, 0x00, 0x11, 0x45,
    0xc0, 0x71, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0xc0, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x00, 0xc0,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x08, 0x00, 0x25, 0xff, 0xff, 0x00, 0x00, 0x01,
    0x01, 0xc8, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x01, 0x02, 0x04, 0x10, 0x10, 0xa6, 0x18, 0x8c, 0x21,
    0x00, 0xc4, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x4e, 0x0f, 0x3a, 0x4c, 0x94, 0x9d, 0xba, 0x79, 0xe7, 0x38,
    0x4c, 0xcf, 0x14, 0xc3, 0x43, 0x91, 0x88, 0xfb, 0xdc, 0xe0, 0x7c, 0x34, 0x70, 0x9b, 0x28, 0xa9,
    0x18, 0x74, 0x62, 0x87, 0x8e, 0xe4, 0x68, 0x5f, 0xb9, 0xcc, 0x0e, 0xe1, 0x8c, 0x76, 0x3a, 0x9b,
    0x82, 0x76, 0x71, 0x13, 0xde, 0x50, 0xd4, 0x2d, 0xc2, 0xda, 0x1e, 0x3b, 0xa6, 0xa1, 0x62, 0x7b,
    0xca, 0x1a, 0x85, 0x4b, 0x6e, 0x74, 0xec, 0x60
};
static const BYTE test_wmp_data[] =
{
    0xff, 0xff, 0xff, 0xff
};

static const struct test_image
{
    const BYTE *data;
    unsigned int size;
    const BYTE *expected_data;
    D3DX10_IMAGE_INFO expected_info;
}
test_image[] =
{
    {
        test_bmp_1bpp,       sizeof(test_bmp_1bpp),          test_bmp_1bpp_data,
        {1, 1, 1, 1, 1, 0,   DXGI_FORMAT_R8G8B8A8_UNORM,     D3D10_RESOURCE_DIMENSION_TEXTURE2D, D3DX10_IFF_BMP}
    },
    {
        test_bmp_4bpp,       sizeof(test_bmp_4bpp),          test_bmp_4bpp_data,
        {1, 1, 1, 1, 1, 0,   DXGI_FORMAT_R8G8B8A8_UNORM,     D3D10_RESOURCE_DIMENSION_TEXTURE2D, D3DX10_IFF_BMP}
    },
    {
        test_bmp_8bpp,       sizeof(test_bmp_8bpp),          test_bmp_8bpp_data,
        {1, 1, 1, 1, 1, 0,   DXGI_FORMAT_R8G8B8A8_UNORM,     D3D10_RESOURCE_DIMENSION_TEXTURE2D, D3DX10_IFF_BMP}
    },
    {
        test_bmp_16bpp,      sizeof(test_bmp_16bpp),         test_bmp_16bpp_data,
        {1, 1, 1, 1, 1, 0,   DXGI_FORMAT_R8G8B8A8_UNORM,     D3D10_RESOURCE_DIMENSION_TEXTURE2D, D3DX10_IFF_BMP}
    },
    {
        test_bmp_24bpp,      sizeof(test_bmp_24bpp),         test_bmp_24bpp_data,
        {1, 1, 1, 1, 1, 0,   DXGI_FORMAT_R8G8B8A8_UNORM,     D3D10_RESOURCE_DIMENSION_TEXTURE2D, D3DX10_IFF_BMP}
    },
    {
        test_bmp_32bpp_xrgb, sizeof(test_bmp_32bpp_xrgb),    test_bmp_32bpp_xrgb_data,
        {2, 2, 1, 1, 1, 0,   DXGI_FORMAT_R8G8B8A8_UNORM,     D3D10_RESOURCE_DIMENSION_TEXTURE2D, D3DX10_IFF_BMP}
    },
    {
        test_bmp_32bpp_argb, sizeof(test_bmp_32bpp_argb),    test_bmp_32bpp_argb_data,
        {2, 2, 1, 1, 1, 0,   DXGI_FORMAT_R8G8B8A8_UNORM,     D3D10_RESOURCE_DIMENSION_TEXTURE2D, D3DX10_IFF_BMP}
    },
    {
        test_png_8bpp_gray,  sizeof(test_png_8bpp_gray),     test_png_8bpp_gray_data,
        {1, 1, 1, 1, 1, 0,   DXGI_FORMAT_R8G8B8A8_UNORM,     D3D10_RESOURCE_DIMENSION_TEXTURE2D, D3DX10_IFF_PNG}
    },
    {
        test_jpg,            sizeof(test_jpg),               test_jpg_data,
        {1, 1, 1, 1, 1, 0,   DXGI_FORMAT_R8G8B8A8_UNORM,     D3D10_RESOURCE_DIMENSION_TEXTURE2D, D3DX10_IFF_JPG}
    },
    {
        test_gif,            sizeof(test_gif),               test_gif_data,
        {1, 1, 1, 1, 1, 0,   DXGI_FORMAT_R8G8B8A8_UNORM,     D3D10_RESOURCE_DIMENSION_TEXTURE2D, D3DX10_IFF_GIF}
    },
    {
        test_tiff,           sizeof(test_tiff),              test_tiff_data,
        {1, 1, 1, 1, 1, 0,   DXGI_FORMAT_R8G8B8A8_UNORM,     D3D10_RESOURCE_DIMENSION_TEXTURE2D, D3DX10_IFF_TIFF}
    },
    {
        test_dds_alpha,      sizeof(test_dds_alpha),         test_dds_alpha_data,
        {1, 1, 1, 1, 1, 0,   DXGI_FORMAT_A8_UNORM,           D3D10_RESOURCE_DIMENSION_TEXTURE2D, D3DX10_IFF_DDS}
    },
    {
        test_dds_luminance,  sizeof(test_dds_luminance),     test_dds_luminance_data,
        {1, 1, 1, 1, 1, 0,   DXGI_FORMAT_R8G8B8A8_UNORM,     D3D10_RESOURCE_DIMENSION_TEXTURE2D, D3DX10_IFF_DDS}
    },
    {
        test_dds_16bpp,      sizeof(test_dds_16bpp),         test_dds_16bpp_data,
        {1, 1, 1, 1, 1, 0,   DXGI_FORMAT_R8G8B8A8_UNORM,     D3D10_RESOURCE_DIMENSION_TEXTURE2D, D3DX10_IFF_DDS}
    },
    {
        test_dds_24bpp,      sizeof(test_dds_24bpp),         test_dds_24bpp_data,
        {1, 1, 1, 1, 1, 0,   DXGI_FORMAT_R8G8B8A8_UNORM,     D3D10_RESOURCE_DIMENSION_TEXTURE2D, D3DX10_IFF_DDS}
    },
    {
        test_dds_32bpp,      sizeof(test_dds_32bpp),         test_dds_32bpp_data,
        {1, 1, 1, 1, 1, 0,   DXGI_FORMAT_R8G8B8A8_UNORM,     D3D10_RESOURCE_DIMENSION_TEXTURE2D, D3DX10_IFF_DDS}
    },
    {
        test_dds_64bpp,      sizeof(test_dds_64bpp),         test_dds_64bpp_data,
        {1, 1, 1, 1, 1, 0,   DXGI_FORMAT_R16G16B16A16_UNORM, D3D10_RESOURCE_DIMENSION_TEXTURE2D, D3DX10_IFF_DDS}
    },
    {
        test_dds_96bpp,      sizeof(test_dds_96bpp),         test_dds_96bpp_data,
        {1, 1, 1, 1, 1, 0,   DXGI_FORMAT_R32G32B32_FLOAT,    D3D10_RESOURCE_DIMENSION_TEXTURE2D, D3DX10_IFF_DDS}
    },
    {
        test_dds_128bpp,     sizeof(test_dds_128bpp),        test_dds_128bpp_data,
        {1, 1, 1, 1, 1, 0,   DXGI_FORMAT_R32G32B32A32_FLOAT, D3D10_RESOURCE_DIMENSION_TEXTURE2D, D3DX10_IFF_DDS}
    },
    {
        test_dds_dxt1,       sizeof(test_dds_dxt1),          test_dds_dxt1_data,
        {4, 4, 1, 1, 1, 0,   DXGI_FORMAT_BC1_UNORM,          D3D10_RESOURCE_DIMENSION_TEXTURE2D, D3DX10_IFF_DDS}
    },
    {
        test_dds_dxt2,       sizeof(test_dds_dxt2),          test_dds_dxt2_data,
        {4, 4, 1, 1, 3, 0,   DXGI_FORMAT_BC2_UNORM,          D3D10_RESOURCE_DIMENSION_TEXTURE2D, D3DX10_IFF_DDS}
    },
    {
        test_dds_dxt3,       sizeof(test_dds_dxt3),          test_dds_dxt3_data,
        {1, 3, 1, 1, 2, 0,   DXGI_FORMAT_BC2_UNORM,          D3D10_RESOURCE_DIMENSION_TEXTURE2D, D3DX10_IFF_DDS}
    },
    {
        test_dds_dxt4,       sizeof(test_dds_dxt4),          test_dds_dxt4_data,
        {4, 4, 1, 1, 3, 0,   DXGI_FORMAT_BC3_UNORM,          D3D10_RESOURCE_DIMENSION_TEXTURE2D, D3DX10_IFF_DDS}
    },
    {
        test_dds_dxt5,       sizeof(test_dds_dxt5),          test_dds_dxt5_data,
        {4, 2, 1, 1, 1, 0,   DXGI_FORMAT_BC3_UNORM,          D3D10_RESOURCE_DIMENSION_TEXTURE2D, D3DX10_IFF_DDS}
    },
    {
        test_dds_bc4,        sizeof(test_dds_bc4),           test_dds_bc4_data,
        {4, 4, 1, 1, 3, 0,   DXGI_FORMAT_BC4_UNORM,          D3D10_RESOURCE_DIMENSION_TEXTURE2D, D3DX10_IFF_DDS}
    },
    {
        test_dds_bc5,        sizeof(test_dds_bc5),           test_dds_bc5_data,
        {6, 3, 1, 1, 3, 0,   DXGI_FORMAT_BC5_UNORM,          D3D10_RESOURCE_DIMENSION_TEXTURE2D, D3DX10_IFF_DDS}
    },
    {
        test_dds_cube,       sizeof(test_dds_cube),          test_dds_cube_data,
        {4, 4, 1, 6, 3, 0x4, DXGI_FORMAT_BC1_UNORM,          D3D10_RESOURCE_DIMENSION_TEXTURE2D, D3DX10_IFF_DDS}
    },
    {
        test_wmp,            sizeof(test_wmp),               test_wmp_data,
        {1, 1, 1, 1, 1, 0,   DXGI_FORMAT_R8G8B8A8_UNORM,     D3D10_RESOURCE_DIMENSION_TEXTURE2D, D3DX10_IFF_WMP}
    },
};

static WCHAR temp_dir[MAX_PATH];

static DXGI_FORMAT block_compressed_formats[] =
{
    DXGI_FORMAT_BC1_TYPELESS,  DXGI_FORMAT_BC1_UNORM, DXGI_FORMAT_BC1_UNORM_SRGB,
    DXGI_FORMAT_BC2_TYPELESS,  DXGI_FORMAT_BC2_UNORM, DXGI_FORMAT_BC2_UNORM_SRGB,
    DXGI_FORMAT_BC3_TYPELESS,  DXGI_FORMAT_BC3_UNORM, DXGI_FORMAT_BC3_UNORM_SRGB,
    DXGI_FORMAT_BC4_TYPELESS,  DXGI_FORMAT_BC4_UNORM, DXGI_FORMAT_BC4_SNORM,
    DXGI_FORMAT_BC5_TYPELESS,  DXGI_FORMAT_BC5_UNORM, DXGI_FORMAT_BC5_SNORM,
    DXGI_FORMAT_BC6H_TYPELESS, DXGI_FORMAT_BC6H_UF16, DXGI_FORMAT_BC6H_SF16,
    DXGI_FORMAT_BC7_TYPELESS,  DXGI_FORMAT_BC7_UNORM, DXGI_FORMAT_BC7_UNORM_SRGB
};

static BOOL is_block_compressed(DXGI_FORMAT format)
{
    unsigned int i;

    for (i = 0; i < ARRAY_SIZE(block_compressed_formats); ++i)
        if (format == block_compressed_formats[i])
            return TRUE;

    return FALSE;
}

static unsigned int get_bpp_from_format(DXGI_FORMAT format)
{
    switch (format)
    {
        case DXGI_FORMAT_R32G32B32A32_TYPELESS:
        case DXGI_FORMAT_R32G32B32A32_FLOAT:
        case DXGI_FORMAT_R32G32B32A32_UINT:
        case DXGI_FORMAT_R32G32B32A32_SINT:
            return 128;
        case DXGI_FORMAT_R32G32B32_TYPELESS:
        case DXGI_FORMAT_R32G32B32_FLOAT:
        case DXGI_FORMAT_R32G32B32_UINT:
        case DXGI_FORMAT_R32G32B32_SINT:
            return 96;
        case DXGI_FORMAT_R16G16B16A16_TYPELESS:
        case DXGI_FORMAT_R16G16B16A16_FLOAT:
        case DXGI_FORMAT_R16G16B16A16_UNORM:
        case DXGI_FORMAT_R16G16B16A16_UINT:
        case DXGI_FORMAT_R16G16B16A16_SNORM:
        case DXGI_FORMAT_R16G16B16A16_SINT:
        case DXGI_FORMAT_R32G32_TYPELESS:
        case DXGI_FORMAT_R32G32_FLOAT:
        case DXGI_FORMAT_R32G32_UINT:
        case DXGI_FORMAT_R32G32_SINT:
        case DXGI_FORMAT_R32G8X24_TYPELESS:
        case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:
        case DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS:
        case DXGI_FORMAT_X32_TYPELESS_G8X24_UINT:
        case DXGI_FORMAT_Y416:
        case DXGI_FORMAT_Y210:
        case DXGI_FORMAT_Y216:
            return 64;
        case DXGI_FORMAT_R10G10B10A2_TYPELESS:
        case DXGI_FORMAT_R10G10B10A2_UNORM:
        case DXGI_FORMAT_R10G10B10A2_UINT:
        case DXGI_FORMAT_R11G11B10_FLOAT:
        case DXGI_FORMAT_R8G8B8A8_TYPELESS:
        case DXGI_FORMAT_R8G8B8A8_UNORM:
        case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
        case DXGI_FORMAT_R8G8B8A8_UINT:
        case DXGI_FORMAT_R8G8B8A8_SNORM:
        case DXGI_FORMAT_R8G8B8A8_SINT:
        case DXGI_FORMAT_R16G16_TYPELESS:
        case DXGI_FORMAT_R16G16_FLOAT:
        case DXGI_FORMAT_R16G16_UNORM:
        case DXGI_FORMAT_R16G16_UINT:
        case DXGI_FORMAT_R16G16_SNORM:
        case DXGI_FORMAT_R16G16_SINT:
        case DXGI_FORMAT_R32_TYPELESS:
        case DXGI_FORMAT_D32_FLOAT:
        case DXGI_FORMAT_R32_FLOAT:
        case DXGI_FORMAT_R32_UINT:
        case DXGI_FORMAT_R32_SINT:
        case DXGI_FORMAT_R24G8_TYPELESS:
        case DXGI_FORMAT_D24_UNORM_S8_UINT:
        case DXGI_FORMAT_R24_UNORM_X8_TYPELESS:
        case DXGI_FORMAT_X24_TYPELESS_G8_UINT:
        case DXGI_FORMAT_R9G9B9E5_SHAREDEXP:
        case DXGI_FORMAT_R8G8_B8G8_UNORM:
        case DXGI_FORMAT_G8R8_G8B8_UNORM:
        case DXGI_FORMAT_B8G8R8A8_UNORM:
        case DXGI_FORMAT_B8G8R8X8_UNORM:
        case DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM:
        case DXGI_FORMAT_B8G8R8A8_TYPELESS:
        case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
        case DXGI_FORMAT_B8G8R8X8_TYPELESS:
        case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:
        case DXGI_FORMAT_AYUV:
        case DXGI_FORMAT_Y410:
        case DXGI_FORMAT_YUY2:
            return 32;
        case DXGI_FORMAT_P010:
        case DXGI_FORMAT_P016:
            return 24;
        case DXGI_FORMAT_R8G8_TYPELESS:
        case DXGI_FORMAT_R8G8_UNORM:
        case DXGI_FORMAT_R8G8_UINT:
        case DXGI_FORMAT_R8G8_SNORM:
        case DXGI_FORMAT_R8G8_SINT:
        case DXGI_FORMAT_R16_TYPELESS:
        case DXGI_FORMAT_R16_FLOAT:
        case DXGI_FORMAT_D16_UNORM:
        case DXGI_FORMAT_R16_UNORM:
        case DXGI_FORMAT_R16_UINT:
        case DXGI_FORMAT_R16_SNORM:
        case DXGI_FORMAT_R16_SINT:
        case DXGI_FORMAT_B5G6R5_UNORM:
        case DXGI_FORMAT_B5G5R5A1_UNORM:
        case DXGI_FORMAT_A8P8:
        case DXGI_FORMAT_B4G4R4A4_UNORM:
            return 16;
        case DXGI_FORMAT_NV12:
        case DXGI_FORMAT_420_OPAQUE:
        case DXGI_FORMAT_NV11:
            return 12;
        case DXGI_FORMAT_R8_TYPELESS:
        case DXGI_FORMAT_R8_UNORM:
        case DXGI_FORMAT_R8_UINT:
        case DXGI_FORMAT_R8_SNORM:
        case DXGI_FORMAT_R8_SINT:
        case DXGI_FORMAT_A8_UNORM:
        case DXGI_FORMAT_AI44:
        case DXGI_FORMAT_IA44:
        case DXGI_FORMAT_P8:
        case DXGI_FORMAT_BC2_TYPELESS:
        case DXGI_FORMAT_BC2_UNORM:
        case DXGI_FORMAT_BC2_UNORM_SRGB:
        case DXGI_FORMAT_BC3_TYPELESS:
        case DXGI_FORMAT_BC3_UNORM:
        case DXGI_FORMAT_BC3_UNORM_SRGB:
        case DXGI_FORMAT_BC5_TYPELESS:
        case DXGI_FORMAT_BC5_UNORM:
        case DXGI_FORMAT_BC5_SNORM:
        case DXGI_FORMAT_BC6H_TYPELESS:
        case DXGI_FORMAT_BC6H_UF16:
        case DXGI_FORMAT_BC6H_SF16:
        case DXGI_FORMAT_BC7_TYPELESS:
        case DXGI_FORMAT_BC7_UNORM:
        case DXGI_FORMAT_BC7_UNORM_SRGB:
            return 8;
        case DXGI_FORMAT_BC1_TYPELESS:
        case DXGI_FORMAT_BC1_UNORM:
        case DXGI_FORMAT_BC1_UNORM_SRGB:
        case DXGI_FORMAT_BC4_TYPELESS:
        case DXGI_FORMAT_BC4_UNORM:
        case DXGI_FORMAT_BC4_SNORM:
            return 4;
        case DXGI_FORMAT_R1_UNORM:
            return 1;
        default:
            return 0;
    }
}

static BOOL compare_float(float f, float g, unsigned int ulps)
{
    int x = *(int *)&f;
    int y = *(int *)&g;

    if (x < 0)
        x = INT_MIN - x;
    if (y < 0)
        y = INT_MIN - y;

    if (abs(x - y) > ulps)
        return FALSE;

    return TRUE;
}

static char *get_str_a(const WCHAR *wstr)
{
    static char buffer[MAX_PATH];

    WideCharToMultiByte(CP_ACP, 0, wstr, -1, buffer, sizeof(buffer), NULL, NULL);
    return buffer;
}

static BOOL create_file(const WCHAR *filename, const void *data, unsigned int size, WCHAR *out_path)
{
    WCHAR path[MAX_PATH];
    DWORD written;
    HANDLE file;

    if (!temp_dir[0])
        GetTempPathW(ARRAY_SIZE(temp_dir), temp_dir);
    lstrcpyW(path, temp_dir);
    lstrcatW(path, filename);

    file = CreateFileW(path, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
    if (file == INVALID_HANDLE_VALUE)
        return FALSE;

    if (WriteFile(file, data, size, &written, NULL))
    {
        CloseHandle(file);

        if (out_path)
            lstrcpyW(out_path, path);
        return TRUE;
    }

    CloseHandle(file);
    return FALSE;
}

static BOOL delete_file(const WCHAR *filename)
{
    WCHAR path[MAX_PATH];

    lstrcpyW(path, temp_dir);
    lstrcatW(path, filename);
    return DeleteFileW(path);
}

static ID3D10Device *create_device(void)
{
    ID3D10Device *device;
    HMODULE d3d10_mod = LoadLibraryA("d3d10.dll");
    HRESULT (WINAPI *pD3D10CreateDevice)(IDXGIAdapter *, D3D10_DRIVER_TYPE, HMODULE, UINT, UINT, ID3D10Device **);

    if (!d3d10_mod)
    {
        win_skip("d3d10.dll not present\n");
        return NULL;
    }

    pD3D10CreateDevice = (void *)GetProcAddress(d3d10_mod, "D3D10CreateDevice");
    if (SUCCEEDED(pD3D10CreateDevice(NULL, D3D10_DRIVER_TYPE_HARDWARE, NULL, 0, D3D10_SDK_VERSION, &device)))
        return device;
    if (SUCCEEDED(pD3D10CreateDevice(NULL, D3D10_DRIVER_TYPE_WARP, NULL, 0, D3D10_SDK_VERSION, &device)))
        return device;
    if (SUCCEEDED(pD3D10CreateDevice(NULL, D3D10_DRIVER_TYPE_REFERENCE, NULL, 0, D3D10_SDK_VERSION, &device)))
        return device;

    return NULL;
}

static HMODULE create_resource_module(const WCHAR *filename, const void *data, unsigned int size)
{
    WCHAR resource_module_path[MAX_PATH], current_module_path[MAX_PATH];
    HANDLE resource;
    HMODULE module;
    BOOL ret;

    if (!temp_dir[0])
        GetTempPathW(ARRAY_SIZE(temp_dir), temp_dir);
    lstrcpyW(resource_module_path, temp_dir);
    lstrcatW(resource_module_path, filename);

    GetModuleFileNameW(NULL, current_module_path, ARRAY_SIZE(current_module_path));
    ret = CopyFileW(current_module_path, resource_module_path, FALSE);
    ok(ret, "CopyFileW failed, error %u.\n", GetLastError());
    SetFileAttributesW(resource_module_path, FILE_ATTRIBUTE_NORMAL);

    resource = BeginUpdateResourceW(resource_module_path, TRUE);
    UpdateResourceW(resource, (LPCWSTR)RT_RCDATA, filename, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), (void *)data, size);
    EndUpdateResourceW(resource, FALSE);

    module = LoadLibraryExW(resource_module_path, NULL, LOAD_LIBRARY_AS_DATAFILE);

    return module;
}

static void delete_resource_module(const WCHAR *filename, HMODULE module)
{
    WCHAR path[MAX_PATH];

    FreeLibrary(module);

    lstrcpyW(path, temp_dir);
    lstrcatW(path, filename);
    DeleteFileW(path);
}

static void check_image_info(D3DX10_IMAGE_INFO *image_info, const struct test_image *image, unsigned int line)
{
    ok_(__FILE__, line)(image_info->Width == image->expected_info.Width,
            "Got unexpected Width %u, expected %u.\n",
            image_info->Width, image->expected_info.Width);
    ok_(__FILE__, line)(image_info->Height == image->expected_info.Height,
            "Got unexpected Height %u, expected %u.\n",
            image_info->Height, image->expected_info.Height);
    ok_(__FILE__, line)(image_info->Depth == image->expected_info.Depth,
            "Got unexpected Depth %u, expected %u.\n",
            image_info->Depth, image->expected_info.Depth);
    ok_(__FILE__, line)(image_info->ArraySize == image->expected_info.ArraySize,
            "Got unexpected ArraySize %u, expected %u.\n",
            image_info->ArraySize, image->expected_info.ArraySize);
    ok_(__FILE__, line)(image_info->MipLevels == image->expected_info.MipLevels,
            "Got unexpected MipLevels %u, expected %u.\n",
            image_info->MipLevels, image->expected_info.MipLevels);
    ok_(__FILE__, line)(image_info->MiscFlags == image->expected_info.MiscFlags,
            "Got unexpected MiscFlags %#x, expected %#x.\n",
            image_info->MiscFlags, image->expected_info.MiscFlags);
    ok_(__FILE__, line)(image_info->Format == image->expected_info.Format,
            "Got unexpected Format %#x, expected %#x.\n",
            image_info->Format, image->expected_info.Format);
    ok_(__FILE__, line)(image_info->ResourceDimension == image->expected_info.ResourceDimension,
            "Got unexpected ResourceDimension %u, expected %u.\n",
            image_info->ResourceDimension, image->expected_info.ResourceDimension);
    ok_(__FILE__, line)(image_info->ImageFileFormat == image->expected_info.ImageFileFormat,
            "Got unexpected ImageFileFormat %u, expected %u.\n",
            image_info->ImageFileFormat, image->expected_info.ImageFileFormat);
}

static ID3D10Texture2D *get_texture_readback(ID3D10Texture2D *texture)
{
    D3D10_TEXTURE2D_DESC desc;
    ID3D10Texture2D *readback;
    ID3D10Device *device;
    HRESULT hr;

    ID3D10Texture2D_GetDevice(texture, &device);

    ID3D10Texture2D_GetDesc(texture, &desc);
    desc.Usage = D3D10_USAGE_STAGING;
    desc.BindFlags = 0;
    desc.CPUAccessFlags = D3D10_CPU_ACCESS_READ;

    hr = ID3D10Device_CreateTexture2D(device, &desc, NULL, &readback);
    if (hr != S_OK)
    {
        ID3D10Device_Release(device);
        return NULL;
    }
    ID3D10Device_CopyResource(device, (ID3D10Resource *)readback, (ID3D10Resource *)texture);

    ID3D10Device_Release(device);
    return readback;
}

static void check_resource_info(ID3D10Resource *resource, const struct test_image *image, unsigned int line)
{
    unsigned int expected_mip_levels, expected_width, expected_height, max_dimension;
    D3D10_RESOURCE_DIMENSION resource_dimension;
    D3D10_TEXTURE2D_DESC desc_2d;
    D3D10_TEXTURE3D_DESC desc_3d;
    ID3D10Texture2D *texture_2d;
    ID3D10Texture3D *texture_3d;
    HRESULT hr;

    expected_width = image->expected_info.Width;
    expected_height = image->expected_info.Height;
    if (is_block_compressed(image->expected_info.Format))
    {
        expected_width = (expected_width + 3) & ~3;
        expected_height = (expected_height + 3) & ~3;
    }
    expected_mip_levels = 0;
    max_dimension = max(expected_width, expected_height);
    while (max_dimension)
    {
        ++expected_mip_levels;
        max_dimension >>= 1;
    }

    ID3D10Resource_GetType(resource, &resource_dimension);
    ok(resource_dimension == image->expected_info.ResourceDimension,
            "Got unexpected ResourceDimension %u, expected %u.\n",
             resource_dimension, image->expected_info.ResourceDimension);

    switch (resource_dimension)
    {
        case D3D10_RESOURCE_DIMENSION_TEXTURE2D:
            hr = ID3D10Resource_QueryInterface(resource, &IID_ID3D10Texture2D, (void **)&texture_2d);
            ok(hr == S_OK, "Got unexpected hr %#x.\n",  hr);
            ID3D10Texture2D_GetDesc(texture_2d, &desc_2d);
            ok_(__FILE__, line)(desc_2d.Width == expected_width,
                    "Got unexpected Width %u, expected %u.\n",
                     desc_2d.Width, expected_width);
            ok_(__FILE__, line)(desc_2d.Height == expected_height,
                    "Got unexpected Height %u, expected %u.\n",
                     desc_2d.Height, expected_height);
            ok_(__FILE__, line)(desc_2d.MipLevels == expected_mip_levels,
                    "Got unexpected MipLevels %u, expected %u.\n",
                     desc_2d.MipLevels, expected_mip_levels);
            ok_(__FILE__, line)(desc_2d.ArraySize == image->expected_info.ArraySize,
                    "Got unexpected ArraySize %u, expected %u.\n",
                     desc_2d.ArraySize, image->expected_info.ArraySize);
            ok_(__FILE__, line)(desc_2d.Format == image->expected_info.Format,
                    "Got unexpected Format %u, expected %u.\n",
                     desc_2d.Format, image->expected_info.Format);
            ok_(__FILE__, line)(desc_2d.SampleDesc.Count == 1,
                    "Got unexpected SampleDesc.Count %u, expected %u\n",
                     desc_2d.SampleDesc.Count, 1);
            ok_(__FILE__, line)(desc_2d.SampleDesc.Quality == 0,
                    "Got unexpected SampleDesc.Quality %u, expected %u\n",
                     desc_2d.SampleDesc.Quality, 0);
            ok_(__FILE__, line)(desc_2d.Usage == D3D10_USAGE_DEFAULT,
                    "Got unexpected Usage %u, expected %u\n",
                     desc_2d.Usage, D3D10_USAGE_DEFAULT);
            ok_(__FILE__, line)(desc_2d.BindFlags == D3D10_BIND_SHADER_RESOURCE,
                    "Got unexpected BindFlags %#x, expected %#x\n",
                     desc_2d.BindFlags, D3D10_BIND_SHADER_RESOURCE);
            ok_(__FILE__, line)(desc_2d.CPUAccessFlags == 0,
                    "Got unexpected CPUAccessFlags %#x, expected %#x\n",
                     desc_2d.CPUAccessFlags, 0);
            ok_(__FILE__, line)(desc_2d.MiscFlags == image->expected_info.MiscFlags,
                    "Got unexpected MiscFlags %#x, expected %#x.\n",
                     desc_2d.MiscFlags, image->expected_info.MiscFlags);

            ID3D10Texture2D_Release(texture_2d);
            break;

        case D3D10_RESOURCE_DIMENSION_TEXTURE3D:
            hr = ID3D10Resource_QueryInterface(resource, &IID_ID3D10Texture3D, (void **)&texture_3d);
            ok(hr == S_OK, "Got unexpected hr %#x.\n",  hr);
            ID3D10Texture3D_GetDesc(texture_3d, &desc_3d);
            ok_(__FILE__, line)(desc_3d.Width == expected_width,
                    "Got unexpected Width %u, expected %u.\n",
                     desc_3d.Width, expected_width);
            ok_(__FILE__, line)(desc_3d.Height == expected_height,
                    "Got unexpected Height %u, expected %u.\n",
                     desc_3d.Height, expected_height);
            ok_(__FILE__, line)(desc_3d.Depth == image->expected_info.Depth,
                    "Got unexpected Depth %u, expected %u.\n",
                     desc_3d.Depth, image->expected_info.Depth);
            ok_(__FILE__, line)(desc_3d.MipLevels == expected_mip_levels,
                    "Got unexpected MipLevels %u, expected %u.\n",
                     desc_3d.MipLevels, expected_mip_levels);
            ok_(__FILE__, line)(desc_3d.Format == image->expected_info.Format,
                    "Got unexpected Format %u, expected %u.\n",
                     desc_3d.Format, image->expected_info.Format);
            ok_(__FILE__, line)(desc_3d.Usage == D3D10_USAGE_DEFAULT,
                    "Got unexpected Usage %u, expected %u\n",
                     desc_3d.Usage, D3D10_USAGE_DEFAULT);
            ok_(__FILE__, line)(desc_3d.BindFlags == D3D10_BIND_SHADER_RESOURCE,
                    "Got unexpected BindFlags %#x, expected %#x\n",
                     desc_3d.BindFlags, D3D10_BIND_SHADER_RESOURCE);
            ok_(__FILE__, line)(desc_3d.CPUAccessFlags == 0,
                    "Got unexpected CPUAccessFlags %#x, expected %#x\n",
                     desc_3d.CPUAccessFlags, 0);
            ok_(__FILE__, line)(desc_3d.MiscFlags == image->expected_info.MiscFlags,
                    "Got unexpected MiscFlags %#x, expected %#x.\n",
                     desc_3d.MiscFlags, image->expected_info.MiscFlags);
            ID3D10Texture3D_Release(texture_3d);
            break;

        default:
            break;
    }
}

static void check_resource_data(ID3D10Resource *resource, const struct test_image *image, unsigned int line)
{
    unsigned int width, height, stride, i;
    D3D10_MAPPED_TEXTURE2D map;
    D3D10_TEXTURE2D_DESC desc;
    ID3D10Texture2D *readback;
    BOOL line_match;
    HRESULT hr;

    readback = get_texture_readback((ID3D10Texture2D *)resource);
    ok_(__FILE__, line)(readback != NULL, "Failed to get texture readback.\n");
    if (!readback)
        return;

    ID3D10Texture2D_GetDesc(readback, &desc);
    width = desc.Width;
    height = desc.Height;
    stride = (width * get_bpp_from_format(desc.Format) + 7) / 8;
    if (is_block_compressed(desc.Format))
    {
        stride *= 4;
        height = (height + 3) / 4;
    }

    hr = ID3D10Texture2D_Map(readback, 0, D3D10_MAP_READ, 0, &map);
    ok_(__FILE__, line)(hr == S_OK, "Map failed, hr %#x.\n", hr);
    if (hr != S_OK)
    {
        ID3D10Texture2D_Unmap(readback, 0);
        return;
    }

    for (i = 0; i < height; ++i)
    {
        line_match = !memcmp(image->expected_data + stride * i,
                (BYTE *)map.pData + map.RowPitch * i, stride);
        ok_(__FILE__, line)(line_match, "Data mismatch for line %u.\n", i);
        if (!line_match)
            break;
    }

    ID3D10Texture2D_Unmap(readback, 0);
}

static void test_D3DX10UnsetAllDeviceObjects(void)
{
    static const D3D10_INPUT_ELEMENT_DESC layout_desc[] =
    {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D10_INPUT_PER_VERTEX_DATA, 0},
    };
#if 0
float4 main(float4 pos : POSITION) : POSITION
{
    return pos;
}
#endif
    static const DWORD simple_vs[] =
    {
        0x43425844, 0x66689e7c, 0x643f0971, 0xb7f67ff4, 0xabc48688, 0x00000001, 0x000000d4, 0x00000003,
        0x0000002c, 0x00000060, 0x00000094, 0x4e475349, 0x0000002c, 0x00000001, 0x00000008, 0x00000020,
        0x00000000, 0x00000000, 0x00000003, 0x00000000, 0x00000f0f, 0x49534f50, 0x4e4f4954, 0xababab00,
        0x4e47534f, 0x0000002c, 0x00000001, 0x00000008, 0x00000020, 0x00000000, 0x00000000, 0x00000003,
        0x00000000, 0x0000000f, 0x49534f50, 0x4e4f4954, 0xababab00, 0x52444853, 0x00000038, 0x00010040,
        0x0000000e, 0x0300005f, 0x001010f2, 0x00000000, 0x03000065, 0x001020f2, 0x00000000, 0x05000036,
        0x001020f2, 0x00000000, 0x00101e46, 0x00000000, 0x0100003e,
    };

#if 0
struct gs_out
{
    float4 pos : SV_POSITION;
};

[maxvertexcount(4)]
void main(point float4 vin[1] : POSITION, inout TriangleStream<gs_out> vout)
{
    float offset = 0.1 * vin[0].w;
    gs_out v;

    v.pos = float4(vin[0].x - offset, vin[0].y - offset, vin[0].z, vin[0].w);
    vout.Append(v);
    v.pos = float4(vin[0].x - offset, vin[0].y + offset, vin[0].z, vin[0].w);
    vout.Append(v);
    v.pos = float4(vin[0].x + offset, vin[0].y - offset, vin[0].z, vin[0].w);
    vout.Append(v);
    v.pos = float4(vin[0].x + offset, vin[0].y + offset, vin[0].z, vin[0].w);
    vout.Append(v);
}
#endif
    static const DWORD simple_gs[] =
    {
        0x43425844, 0x000ee786, 0xc624c269, 0x885a5cbe, 0x444b3b1f, 0x00000001, 0x0000023c, 0x00000003,
        0x0000002c, 0x00000060, 0x00000094, 0x4e475349, 0x0000002c, 0x00000001, 0x00000008, 0x00000020,
        0x00000000, 0x00000000, 0x00000003, 0x00000000, 0x00000f0f, 0x49534f50, 0x4e4f4954, 0xababab00,
        0x4e47534f, 0x0000002c, 0x00000001, 0x00000008, 0x00000020, 0x00000000, 0x00000001, 0x00000003,
        0x00000000, 0x0000000f, 0x505f5653, 0x5449534f, 0x004e4f49, 0x52444853, 0x000001a0, 0x00020040,
        0x00000068, 0x0400005f, 0x002010f2, 0x00000001, 0x00000000, 0x02000068, 0x00000001, 0x0100085d,
        0x0100285c, 0x04000067, 0x001020f2, 0x00000000, 0x00000001, 0x0200005e, 0x00000004, 0x0f000032,
        0x00100032, 0x00000000, 0x80201ff6, 0x00000041, 0x00000000, 0x00000000, 0x00004002, 0x3dcccccd,
        0x3dcccccd, 0x00000000, 0x00000000, 0x00201046, 0x00000000, 0x00000000, 0x05000036, 0x00102032,
        0x00000000, 0x00100046, 0x00000000, 0x06000036, 0x001020c2, 0x00000000, 0x00201ea6, 0x00000000,
        0x00000000, 0x01000013, 0x05000036, 0x00102012, 0x00000000, 0x0010000a, 0x00000000, 0x0e000032,
        0x00100052, 0x00000000, 0x00201ff6, 0x00000000, 0x00000000, 0x00004002, 0x3dcccccd, 0x00000000,
        0x3dcccccd, 0x00000000, 0x00201106, 0x00000000, 0x00000000, 0x05000036, 0x00102022, 0x00000000,
        0x0010002a, 0x00000000, 0x06000036, 0x001020c2, 0x00000000, 0x00201ea6, 0x00000000, 0x00000000,
        0x01000013, 0x05000036, 0x00102012, 0x00000000, 0x0010000a, 0x00000000, 0x05000036, 0x00102022,
        0x00000000, 0x0010001a, 0x00000000, 0x06000036, 0x001020c2, 0x00000000, 0x00201ea6, 0x00000000,
        0x00000000, 0x01000013, 0x05000036, 0x00102032, 0x00000000, 0x00100086, 0x00000000, 0x06000036,
        0x001020c2, 0x00000000, 0x00201ea6, 0x00000000, 0x00000000, 0x01000013, 0x0100003e,
    };

#if 0
float4 main(float4 color : COLOR) : SV_TARGET
{
    return color;
}
#endif
    static const DWORD simple_ps[] =
    {
        0x43425844, 0x08c2b568, 0x17d33120, 0xb7d82948, 0x13a570fb, 0x00000001, 0x000000d0, 0x00000003,
        0x0000002c, 0x0000005c, 0x00000090, 0x4e475349, 0x00000028, 0x00000001, 0x00000008, 0x00000020,
        0x00000000, 0x00000000, 0x00000003, 0x00000000, 0x00000f0f, 0x4f4c4f43, 0xabab0052, 0x4e47534f,
        0x0000002c, 0x00000001, 0x00000008, 0x00000020, 0x00000000, 0x00000000, 0x00000003, 0x00000000,
        0x0000000f, 0x545f5653, 0x45475241, 0xabab0054, 0x52444853, 0x00000038, 0x00000040, 0x0000000e,
        0x03001062, 0x001010f2, 0x00000000, 0x03000065, 0x001020f2, 0x00000000, 0x05000036, 0x001020f2,
        0x00000000, 0x00101e46, 0x00000000, 0x0100003e,
    };

    D3D10_VIEWPORT tmp_viewport[D3D10_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE];
    ID3D10ShaderResourceView *tmp_srv[D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT];
    ID3D10ShaderResourceView *srv[D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT];
    ID3D10RenderTargetView *tmp_rtv[D3D10_SIMULTANEOUS_RENDER_TARGET_COUNT];
    RECT tmp_rect[D3D10_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE];
    ID3D10SamplerState *tmp_sampler[D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT];
    ID3D10RenderTargetView *rtv[D3D10_SIMULTANEOUS_RENDER_TARGET_COUNT];
    ID3D10Texture2D *rt_texture[D3D10_SIMULTANEOUS_RENDER_TARGET_COUNT];
    ID3D10Buffer *cb[D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT];
    ID3D10Buffer *tmp_buffer[D3D10_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
    ID3D10SamplerState *sampler[D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT];
    ID3D10Buffer *buffer[D3D10_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
    unsigned int offset[D3D10_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
    unsigned int stride[D3D10_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT];
    ID3D10Buffer *so_buffer[D3D10_SO_BUFFER_SLOT_COUNT];
    ID3D10InputLayout *tmp_input_layout, *input_layout;
    ID3D10DepthStencilState *tmp_ds_state, *ds_state;
    ID3D10BlendState *tmp_blend_state, *blend_state;
    ID3D10RasterizerState *tmp_rs_state, *rs_state;
    ID3D10Predicate *tmp_predicate, *predicate;
    D3D10_SHADER_RESOURCE_VIEW_DESC srv_desc;
    ID3D10DepthStencilView *tmp_dsv, *dsv;
    D3D10_PRIMITIVE_TOPOLOGY topology;
    D3D10_TEXTURE2D_DESC texture_desc;
    ID3D10GeometryShader *tmp_gs, *gs;
    D3D10_DEPTH_STENCIL_DESC ds_desc;
    ID3D10VertexShader *tmp_vs, *vs;
    D3D10_SAMPLER_DESC sampler_desc;
    D3D10_QUERY_DESC predicate_desc;
    ID3D10PixelShader *tmp_ps, *ps;
    D3D10_RASTERIZER_DESC rs_desc;
    D3D10_BUFFER_DESC buffer_desc;
    D3D10_BLEND_DESC blend_desc;
    ID3D10Texture2D *ds_texture;
    unsigned int sample_mask;
    unsigned int stencil_ref;
    unsigned int count, i;
    float blend_factor[4];
    ID3D10Device *device;
    BOOL predicate_value;
    DXGI_FORMAT format;
    ULONG refcount;
    HRESULT hr;

    if (!(device = create_device()))
    {
        skip("Failed to create device, skipping tests.\n");
        return;
    }

    buffer_desc.ByteWidth = 1024;
    buffer_desc.Usage = D3D10_USAGE_DEFAULT;
    buffer_desc.BindFlags = D3D10_BIND_CONSTANT_BUFFER;
    buffer_desc.CPUAccessFlags = 0;
    buffer_desc.MiscFlags = 0;

    for (i = 0; i < D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT; ++i)
    {
        hr = ID3D10Device_CreateBuffer(device, &buffer_desc, NULL, &cb[i]);
        ok(SUCCEEDED(hr), "Failed to create buffer, hr %#x.\n", hr);
    }

    buffer_desc.BindFlags = D3D10_BIND_VERTEX_BUFFER | D3D10_BIND_INDEX_BUFFER | D3D10_BIND_SHADER_RESOURCE;

    for (i = 0; i < D3D10_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT; ++i)
    {
        hr = ID3D10Device_CreateBuffer(device, &buffer_desc, NULL, &buffer[i]);
        ok(SUCCEEDED(hr), "Failed to create buffer, hr %#x.\n", hr);

        stride[i] = (i + 1) * 4;
        offset[i] = (i + 1) * 16;
    }

    buffer_desc.BindFlags = D3D10_BIND_STREAM_OUTPUT;

    for (i = 0; i < D3D10_SO_BUFFER_SLOT_COUNT; ++i)
    {
        hr = ID3D10Device_CreateBuffer(device, &buffer_desc, NULL, &so_buffer[i]);
        ok(SUCCEEDED(hr), "Failed to create buffer, hr %#x.\n", hr);
    }

    srv_desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    srv_desc.ViewDimension = D3D10_SRV_DIMENSION_BUFFER;
    U(srv_desc).Buffer.ElementOffset = 0;
    U(srv_desc).Buffer.ElementWidth = 64;

    for (i = 0; i < D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT; ++i)
    {
        hr = ID3D10Device_CreateShaderResourceView(device,
                (ID3D10Resource *)buffer[i % D3D10_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT], &srv_desc, &srv[i]);
        ok(SUCCEEDED(hr), "Failed to create shader resource view, hr %#x.\n", hr);
    }

    sampler_desc.Filter = D3D10_FILTER_MIN_MAG_MIP_LINEAR;
    sampler_desc.AddressU = D3D10_TEXTURE_ADDRESS_CLAMP;
    sampler_desc.AddressV = D3D10_TEXTURE_ADDRESS_CLAMP;
    sampler_desc.AddressW = D3D10_TEXTURE_ADDRESS_CLAMP;
    sampler_desc.MipLODBias = 0.0f;
    sampler_desc.MaxAnisotropy = 16;
    sampler_desc.ComparisonFunc = D3D10_COMPARISON_NEVER;
    sampler_desc.BorderColor[0] = 0.0f;
    sampler_desc.BorderColor[1] = 0.0f;
    sampler_desc.BorderColor[2] = 0.0f;
    sampler_desc.BorderColor[3] = 0.0f;
    sampler_desc.MinLOD = 0.0f;
    sampler_desc.MaxLOD = 16.0f;

    for (i = 0; i < D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT; ++i)
    {
        sampler_desc.MinLOD = (float)i;

        hr = ID3D10Device_CreateSamplerState(device, &sampler_desc, &sampler[i]);
        ok(SUCCEEDED(hr), "Failed to create sampler state, hr %#x.\n", hr);
    }

    hr = ID3D10Device_CreateVertexShader(device, simple_vs, sizeof(simple_vs), &vs);
    ok(SUCCEEDED(hr), "Failed to create vertex shader, hr %#x.\n", hr);

    hr = ID3D10Device_CreateGeometryShader(device, simple_gs, sizeof(simple_gs), &gs);
    ok(SUCCEEDED(hr), "Failed to create geometry shader, hr %#x.\n", hr);

    hr = ID3D10Device_CreatePixelShader(device, simple_ps, sizeof(simple_ps), &ps);
    ok(SUCCEEDED(hr), "Failed to create pixel shader, hr %#x.\n", hr);

    hr = ID3D10Device_CreateInputLayout(device, layout_desc, ARRAY_SIZE(layout_desc), simple_vs,
            sizeof(simple_vs), &input_layout);
    ok(SUCCEEDED(hr), "Failed to create input layout, hr %#x.\n", hr);

    blend_desc.AlphaToCoverageEnable = FALSE;
    blend_desc.BlendEnable[0] = FALSE;
    blend_desc.BlendEnable[1] = FALSE;
    blend_desc.BlendEnable[2] = FALSE;
    blend_desc.BlendEnable[3] = FALSE;
    blend_desc.BlendEnable[4] = FALSE;
    blend_desc.BlendEnable[5] = FALSE;
    blend_desc.BlendEnable[6] = FALSE;
    blend_desc.BlendEnable[7] = FALSE;
    blend_desc.SrcBlend = D3D10_BLEND_ONE;
    blend_desc.DestBlend = D3D10_BLEND_ZERO;
    blend_desc.BlendOp = D3D10_BLEND_OP_ADD;
    blend_desc.SrcBlendAlpha = D3D10_BLEND_ONE;
    blend_desc.DestBlendAlpha = D3D10_BLEND_ZERO;
    blend_desc.BlendOpAlpha = D3D10_BLEND_OP_ADD;
    blend_desc.RenderTargetWriteMask[0] = D3D10_COLOR_WRITE_ENABLE_ALL;
    blend_desc.RenderTargetWriteMask[1] = D3D10_COLOR_WRITE_ENABLE_ALL;
    blend_desc.RenderTargetWriteMask[2] = D3D10_COLOR_WRITE_ENABLE_ALL;
    blend_desc.RenderTargetWriteMask[3] = D3D10_COLOR_WRITE_ENABLE_ALL;
    blend_desc.RenderTargetWriteMask[4] = D3D10_COLOR_WRITE_ENABLE_ALL;
    blend_desc.RenderTargetWriteMask[5] = D3D10_COLOR_WRITE_ENABLE_ALL;
    blend_desc.RenderTargetWriteMask[6] = D3D10_COLOR_WRITE_ENABLE_ALL;
    blend_desc.RenderTargetWriteMask[7] = D3D10_COLOR_WRITE_ENABLE_ALL;

    hr = ID3D10Device_CreateBlendState(device, &blend_desc, &blend_state);
    ok(SUCCEEDED(hr), "Failed to create blend state, hr %#x.\n", hr);

    ds_desc.DepthEnable = TRUE;
    ds_desc.DepthWriteMask = D3D10_DEPTH_WRITE_MASK_ALL;
    ds_desc.DepthFunc = D3D10_COMPARISON_LESS;
    ds_desc.StencilEnable = FALSE;
    ds_desc.StencilReadMask = D3D10_DEFAULT_STENCIL_READ_MASK;
    ds_desc.StencilWriteMask = D3D10_DEFAULT_STENCIL_WRITE_MASK;
    ds_desc.FrontFace.StencilFailOp = D3D10_STENCIL_OP_KEEP;
    ds_desc.FrontFace.StencilDepthFailOp = D3D10_STENCIL_OP_KEEP;
    ds_desc.FrontFace.StencilPassOp = D3D10_STENCIL_OP_KEEP;
    ds_desc.FrontFace.StencilFunc = D3D10_COMPARISON_ALWAYS;
    ds_desc.BackFace.StencilFailOp = D3D10_STENCIL_OP_KEEP;
    ds_desc.BackFace.StencilDepthFailOp = D3D10_STENCIL_OP_KEEP;
    ds_desc.BackFace.StencilPassOp = D3D10_STENCIL_OP_KEEP;
    ds_desc.BackFace.StencilFunc = D3D10_COMPARISON_ALWAYS;

    hr = ID3D10Device_CreateDepthStencilState(device, &ds_desc, &ds_state);
    ok(SUCCEEDED(hr), "Failed to create depthstencil state, hr %#x.\n", hr);

    texture_desc.Width = 512;
    texture_desc.Height = 512;
    texture_desc.MipLevels = 1;
    texture_desc.ArraySize = 1;
    texture_desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    texture_desc.SampleDesc.Count = 1;
    texture_desc.SampleDesc.Quality = 0;
    texture_desc.Usage = D3D10_USAGE_DEFAULT;
    texture_desc.BindFlags = D3D10_BIND_RENDER_TARGET;
    texture_desc.CPUAccessFlags = 0;
    texture_desc.MiscFlags = 0;

    for (i = 0; i < D3D10_SIMULTANEOUS_RENDER_TARGET_COUNT; ++i)
    {
        hr = ID3D10Device_CreateTexture2D(device, &texture_desc, NULL, &rt_texture[i]);
        ok(SUCCEEDED(hr), "Failed to create texture, hr %#x.\n", hr);
    }

    texture_desc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    texture_desc.BindFlags = D3D10_BIND_DEPTH_STENCIL;

    hr = ID3D10Device_CreateTexture2D(device, &texture_desc, NULL, &ds_texture);
    ok(SUCCEEDED(hr), "Failed to create texture, hr %#x.\n", hr);

    for (i = 0; i < D3D10_SIMULTANEOUS_RENDER_TARGET_COUNT; ++i)
    {
        hr = ID3D10Device_CreateRenderTargetView(device, (ID3D10Resource *)rt_texture[i], NULL, &rtv[i]);
        ok(SUCCEEDED(hr), "Failed to create rendertarget view, hr %#x.\n", hr);
    }

    hr = ID3D10Device_CreateDepthStencilView(device, (ID3D10Resource *)ds_texture, NULL, &dsv);
    ok(SUCCEEDED(hr), "Failed to create depthstencil view, hr %#x.\n", hr);

    for (i = 0; i < D3D10_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE; ++i)
    {
        SetRect(&tmp_rect[i], i, i * 2, i + 1, (i + 1) * 2);

        tmp_viewport[i].TopLeftX = i * 3;
        tmp_viewport[i].TopLeftY = i * 4;
        tmp_viewport[i].Width = 3;
        tmp_viewport[i].Height = 4;
        tmp_viewport[i].MinDepth = i * 0.01f;
        tmp_viewport[i].MaxDepth = (i + 1) * 0.01f;
    }

    rs_desc.FillMode = D3D10_FILL_SOLID;
    rs_desc.CullMode = D3D10_CULL_BACK;
    rs_desc.FrontCounterClockwise = FALSE;
    rs_desc.DepthBias = 0;
    rs_desc.DepthBiasClamp = 0.0f;
    rs_desc.SlopeScaledDepthBias = 0.0f;
    rs_desc.DepthClipEnable = TRUE;
    rs_desc.ScissorEnable = FALSE;
    rs_desc.MultisampleEnable = FALSE;
    rs_desc.AntialiasedLineEnable = FALSE;

    hr = ID3D10Device_CreateRasterizerState(device, &rs_desc, &rs_state);
    ok(SUCCEEDED(hr), "Failed to create rasterizer state, hr %#x.\n", hr);

    predicate_desc.Query = D3D10_QUERY_OCCLUSION_PREDICATE;
    predicate_desc.MiscFlags = 0;

    hr = ID3D10Device_CreatePredicate(device, &predicate_desc, &predicate);
    ok(SUCCEEDED(hr), "Failed to create predicate, hr %#x.\n", hr);

    ID3D10Device_VSSetConstantBuffers(device, 0, D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT, cb);
    ID3D10Device_VSSetShaderResources(device, 0, D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT, srv);
    ID3D10Device_VSSetSamplers(device, 0, D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT, sampler);
    ID3D10Device_VSSetShader(device, vs);

    ID3D10Device_GSSetConstantBuffers(device, 0, D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT, cb);
    ID3D10Device_GSSetShaderResources(device, 0, D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT, srv);
    ID3D10Device_GSSetSamplers(device, 0, D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT, sampler);
    ID3D10Device_GSSetShader(device, gs);

    ID3D10Device_PSSetConstantBuffers(device, 0, D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT, cb);
    ID3D10Device_PSSetShaderResources(device, 0, D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT, srv);
    ID3D10Device_PSSetSamplers(device, 0, D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT, sampler);
    ID3D10Device_PSSetShader(device, ps);

    ID3D10Device_IASetVertexBuffers(device, 0, D3D10_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT, buffer, stride, offset);
    ID3D10Device_IASetIndexBuffer(device, buffer[0], DXGI_FORMAT_R32_UINT, offset[0]);
    ID3D10Device_IASetInputLayout(device, input_layout);
    ID3D10Device_IASetPrimitiveTopology(device, D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

    blend_factor[0] = 0.1f;
    blend_factor[1] = 0.2f;
    blend_factor[2] = 0.3f;
    blend_factor[3] = 0.4f;
    ID3D10Device_OMSetBlendState(device, blend_state, blend_factor, 0xff00ff00);
    ID3D10Device_OMSetDepthStencilState(device, ds_state, 3);
    ID3D10Device_OMSetRenderTargets(device, D3D10_SIMULTANEOUS_RENDER_TARGET_COUNT, rtv, dsv);

    ID3D10Device_RSSetScissorRects(device, D3D10_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE, tmp_rect);
    ID3D10Device_RSSetViewports(device, D3D10_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE, tmp_viewport);
    ID3D10Device_RSSetState(device, rs_state);

    ID3D10Device_SOSetTargets(device, D3D10_SO_BUFFER_SLOT_COUNT, so_buffer, offset);

    ID3D10Device_SetPredication(device, predicate, TRUE);

    hr = D3DX10UnsetAllDeviceObjects(device);
    ok(SUCCEEDED(hr), "D3DX10UnsetAllDeviceObjects() failed, %#x.\n", hr);

    ID3D10Device_VSGetConstantBuffers(device, 0, D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT, tmp_buffer);
    for (i = 0; i < D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT; ++i)
    {
        ok(!tmp_buffer[i], "Got unexpected constant buffer %p in slot %u.\n", tmp_buffer[i], i);
    }
    ID3D10Device_VSGetShaderResources(device, 0, D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT, tmp_srv);
    for (i = 0; i < D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT; ++i)
    {
        ok(!tmp_srv[i], "Got unexpected shader resource view %p in slot %u.\n", tmp_srv[i], i);
    }
    ID3D10Device_VSGetSamplers(device, 0, D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT, tmp_sampler);
    for (i = 0; i < D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT; ++i)
    {
        ok(!tmp_sampler[i], "Got unexpected sampler %p in slot %u.\n", tmp_sampler[i], i);
    }
    ID3D10Device_VSGetShader(device, &tmp_vs);
    ok(!tmp_vs, "Got unexpected vertex shader %p.\n", tmp_vs);

    ID3D10Device_GSGetConstantBuffers(device, 0, D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT, tmp_buffer);
    for (i = 0; i < D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT; ++i)
    {
        ok(!tmp_buffer[i], "Got unexpected constant buffer %p in slot %u.\n", tmp_buffer[i], i);
    }
    ID3D10Device_GSGetShaderResources(device, 0, D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT, tmp_srv);
    for (i = 0; i < D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT; ++i)
    {
        ok(!tmp_srv[i], "Got unexpected shader resource view %p in slot %u.\n", tmp_srv[i], i);
    }
    ID3D10Device_GSGetSamplers(device, 0, D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT, tmp_sampler);
    for (i = 0; i < D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT; ++i)
    {
        ok(!tmp_sampler[i], "Got unexpected sampler %p in slot %u.\n", tmp_sampler[i], i);
    }
    ID3D10Device_GSGetShader(device, &tmp_gs);
    ok(!tmp_gs, "Got unexpected geometry shader %p.\n", tmp_gs);

    ID3D10Device_PSGetConstantBuffers(device, 0, D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT, tmp_buffer);
    for (i = 0; i < D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT; ++i)
    {
        ok(!tmp_buffer[i], "Got unexpected constant buffer %p in slot %u.\n", tmp_buffer[i], i);
    }
    ID3D10Device_PSGetShaderResources(device, 0, D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT, tmp_srv);
    for (i = 0; i < D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT; ++i)
    {
        ok(!tmp_srv[i], "Got unexpected shader resource view %p in slot %u.\n", tmp_srv[i], i);
    }
    ID3D10Device_PSGetSamplers(device, 0, D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT, tmp_sampler);
    for (i = 0; i < D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT; ++i)
    {
        ok(!tmp_sampler[i], "Got unexpected sampler %p in slot %u.\n", tmp_sampler[i], i);
    }
    ID3D10Device_PSGetShader(device, &tmp_ps);
    ok(!tmp_ps, "Got unexpected pixel shader %p.\n", tmp_ps);

    ID3D10Device_IAGetVertexBuffers(device, 0, D3D10_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT, tmp_buffer, stride, offset);
    for (i = 0; i < D3D10_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT; ++i)
    {
        ok(!tmp_buffer[i], "Got unexpected vertex buffer %p in slot %u.\n", tmp_buffer[i], i);
        ok(!stride[i], "Got unexpected stride %u in slot %u.\n", stride[i], i);
        ok(!offset[i], "Got unexpected offset %u in slot %u.\n", offset[i], i);
    }
    ID3D10Device_IAGetIndexBuffer(device, tmp_buffer, &format, offset);
    ok(!tmp_buffer[0], "Got unexpected index buffer %p.\n", tmp_buffer[0]);
    ok(format == DXGI_FORMAT_R32_UINT, "Got unexpected index buffer format %#x.\n", format);
    ok(!offset[0], "Got unexpected index buffer offset %u.\n", offset[0]);
    ID3D10Device_IAGetInputLayout(device, &tmp_input_layout);
    ok(!tmp_input_layout, "Got unexpected input layout %p.\n", tmp_input_layout);
    ID3D10Device_IAGetPrimitiveTopology(device, &topology);
    ok(topology == D3D10_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP, "Got unexpected primitive topology %#x.\n", topology);

    ID3D10Device_OMGetBlendState(device, &tmp_blend_state, blend_factor, &sample_mask);
    ok(!tmp_blend_state, "Got unexpected blend state %p.\n", tmp_blend_state);
    ok(blend_factor[0] == 0.0f && blend_factor[1] == 0.0f
            && blend_factor[2] == 0.0f && blend_factor[3] == 0.0f,
            "Got unexpected blend factor {%.8e, %.8e, %.8e, %.8e}.\n",
            blend_factor[0], blend_factor[1], blend_factor[2], blend_factor[3]);
    ok(sample_mask == 0, "Got unexpected sample mask %#x.\n", sample_mask);
    ID3D10Device_OMGetDepthStencilState(device, &tmp_ds_state, &stencil_ref);
    ok(!tmp_ds_state, "Got unexpected depth stencil state %p.\n", tmp_ds_state);
    ok(!stencil_ref, "Got unexpected stencil ref %u.\n", stencil_ref);
    ID3D10Device_OMGetRenderTargets(device, D3D10_SIMULTANEOUS_RENDER_TARGET_COUNT, tmp_rtv, &tmp_dsv);
    for (i = 0; i < D3D10_SIMULTANEOUS_RENDER_TARGET_COUNT; ++i)
    {
        ok(!tmp_rtv[i], "Got unexpected render target view %p in slot %u.\n", tmp_rtv[i], i);
    }
    ok(!tmp_dsv, "Got unexpected depth stencil view %p.\n", tmp_dsv);

    ID3D10Device_RSGetScissorRects(device, &count, NULL);
    ok(count == D3D10_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE,
            "Got unexpected scissor rect count %u.\n", count);
    memset(tmp_rect, 0x55, sizeof(tmp_rect));
    count = D3D10_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE;
    ID3D10Device_RSGetScissorRects(device, &count, tmp_rect);
    for (i = 0; i < D3D10_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE; ++i)
    {
        ok(tmp_rect[i].left == i
                && tmp_rect[i].top == i * 2
                && tmp_rect[i].right == i + 1
                && tmp_rect[i].bottom == (i + 1) * 2,
                "Got unexpected scissor rect %s in slot %u.\n",
                wine_dbgstr_rect(&tmp_rect[i]), i);
    }
    ID3D10Device_RSGetViewports(device, &count, NULL);
    ok(count == D3D10_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE,
            "Got unexpected viewport count %u.\n", count);
    memset(tmp_viewport, 0x55, sizeof(tmp_viewport));
    count = D3D10_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE;
    ID3D10Device_RSGetViewports(device, &count, tmp_viewport);
    for (i = 0; i < D3D10_VIEWPORT_AND_SCISSORRECT_OBJECT_COUNT_PER_PIPELINE; ++i)
    {
        ok(tmp_viewport[i].TopLeftX == i * 3
                    && tmp_viewport[i].TopLeftY == i * 4
                    && tmp_viewport[i].Width == 3
                    && tmp_viewport[i].Height == 4
                    && compare_float(tmp_viewport[i].MinDepth, i * 0.01f, 16)
                    && compare_float(tmp_viewport[i].MaxDepth, (i + 1) * 0.01f, 16),
                    "Got unexpected viewport {%d, %d, %u, %u, %.8e, %.8e} in slot %u.\n",
                    tmp_viewport[i].TopLeftX, tmp_viewport[i].TopLeftY, tmp_viewport[i].Width,
                    tmp_viewport[i].Height, tmp_viewport[i].MinDepth, tmp_viewport[i].MaxDepth, i);
    }
    ID3D10Device_RSGetState(device, &tmp_rs_state);
    ok(!tmp_rs_state, "Got unexpected rasterizer state %p.\n", tmp_rs_state);

    ID3D10Device_SOGetTargets(device, D3D10_SO_BUFFER_SLOT_COUNT, tmp_buffer, offset);
    for (i = 0; i < D3D10_SO_BUFFER_SLOT_COUNT; ++i)
    {
        ok(!tmp_buffer[i], "Got unexpected stream output %p in slot %u.\n", tmp_buffer[i], i);
        ok(offset[i] == ~0u, "Got unexpected stream output offset %u in slot %u.\n", offset[i], i);
    }

    ID3D10Device_GetPredication(device, &tmp_predicate, &predicate_value);
    ok(!tmp_predicate, "Got unexpected predicate %p.\n", tmp_predicate);
    ok(!predicate_value, "Got unexpected predicate value %#x.\n", predicate_value);

    ID3D10Predicate_Release(predicate);
    ID3D10RasterizerState_Release(rs_state);
    ID3D10DepthStencilView_Release(dsv);
    ID3D10Texture2D_Release(ds_texture);

    for (i = 0; i < D3D10_SIMULTANEOUS_RENDER_TARGET_COUNT; ++i)
    {
        ID3D10RenderTargetView_Release(rtv[i]);
        ID3D10Texture2D_Release(rt_texture[i]);
    }

    ID3D10DepthStencilState_Release(ds_state);
    ID3D10BlendState_Release(blend_state);
    ID3D10InputLayout_Release(input_layout);
    ID3D10VertexShader_Release(vs);
    ID3D10GeometryShader_Release(gs);
    ID3D10PixelShader_Release(ps);

    for (i = 0; i < D3D10_COMMONSHADER_SAMPLER_SLOT_COUNT; ++i)
    {
        ID3D10SamplerState_Release(sampler[i]);
    }

    for (i = 0; i < D3D10_COMMONSHADER_INPUT_RESOURCE_SLOT_COUNT; ++i)
    {
        ID3D10ShaderResourceView_Release(srv[i]);
    }

    for (i = 0; i < D3D10_SO_BUFFER_SLOT_COUNT; ++i)
    {
        ID3D10Buffer_Release(so_buffer[i]);
    }

    for (i = 0; i < D3D10_IA_VERTEX_INPUT_RESOURCE_SLOT_COUNT; ++i)
    {
        ID3D10Buffer_Release(buffer[i]);
    }

    for (i = 0; i < D3D10_COMMONSHADER_CONSTANT_BUFFER_API_SLOT_COUNT; ++i)
    {
        ID3D10Buffer_Release(cb[i]);
    }

    refcount = ID3D10Device_Release(device);
    ok(!refcount, "Device has %u references left.\n", refcount);
}

static void test_D3DX10CreateAsyncMemoryLoader(void)
{
    ID3DX10DataLoader *loader;
    SIZE_T size;
    DWORD data;
    HRESULT hr;
    void *ptr;

    hr = D3DX10CreateAsyncMemoryLoader(NULL, 0, NULL);
    ok(hr == E_FAIL, "Got unexpected hr %#x.\n", hr);

    hr = D3DX10CreateAsyncMemoryLoader(NULL, 0, &loader);
    ok(hr == E_FAIL, "Got unexpected hr %#x.\n", hr);

    hr = D3DX10CreateAsyncMemoryLoader(&data, 0, &loader);
    ok(hr == S_OK, "Got unexpected hr %#x.\n", hr);

    size = 100;
    hr = ID3DX10DataLoader_Decompress(loader, &ptr, &size);
    ok(hr == S_OK, "Got unexpected hr %#x.\n", hr);
    ok(ptr == &data, "Got data pointer %p, original %p.\n", ptr, &data);
    ok(!size, "Got unexpected data size.\n");

    /* Load() is no-op. */
    hr = ID3DX10DataLoader_Load(loader);
    ok(hr == S_OK, "Got unexpected hr %#x.\n", hr);

    hr = ID3DX10DataLoader_Destroy(loader);
    ok(hr == S_OK, "Got unexpected hr %#x.\n", hr);

    data = 0;
    hr = D3DX10CreateAsyncMemoryLoader(&data, sizeof(data), &loader);
    ok(hr == S_OK, "Got unexpected hr %#x.\n", hr);

    /* Load() is no-op. */
    hr = ID3DX10DataLoader_Load(loader);
    ok(hr == S_OK, "Got unexpected hr %#x.\n", hr);

    hr = ID3DX10DataLoader_Decompress(loader, &ptr, &size);
    ok(hr == S_OK, "Got unexpected hr %#x.\n", hr);
    ok(ptr == &data, "Got data pointer %p, original %p.\n", ptr, &data);
    ok(size == sizeof(data), "Got unexpected data size.\n");

    hr = ID3DX10DataLoader_Destroy(loader);
    ok(hr == S_OK, "Got unexpected hr %#x.\n", hr);
}

static void test_D3DX10CreateAsyncFileLoader(void)
{
    static const WCHAR test_filename[] = L"asyncloader.data";
    static const char test_data1[] = "test data";
    static const char test_data2[] = "more test data";
    ID3DX10DataLoader *loader;
    WCHAR path[MAX_PATH];
    SIZE_T size;
    HRESULT hr;
    void *ptr;
    BOOL ret;

    hr = D3DX10CreateAsyncFileLoaderA(NULL, NULL);
    ok(hr == E_FAIL, "Got unexpected hr %#x.\n", hr);

    hr = D3DX10CreateAsyncFileLoaderA(NULL, &loader);
    ok(hr == E_FAIL, "Got unexpected hr %#x.\n", hr);

    hr = D3DX10CreateAsyncFileLoaderA("nonexistentfilename", &loader);
    ok(hr == S_OK, "Got unexpected hr %#x.\n", hr);

    hr = ID3DX10DataLoader_Decompress(loader, &ptr, &size);
    ok(hr == E_FAIL, "Got unexpected hr %#x.\n", hr);

    hr = ID3DX10DataLoader_Load(loader);
    ok(hr == D3D10_ERROR_FILE_NOT_FOUND, "Got unexpected hr %#x.\n", hr);

    hr = ID3DX10DataLoader_Decompress(loader, &ptr, &size);
    ok(hr == E_FAIL, "Got unexpected hr %#x.\n", hr);

    hr = ID3DX10DataLoader_Destroy(loader);
    ok(hr == S_OK, "Got unexpected hr %#x.\n", hr);

    /* Test file sharing using dummy empty file. */
    create_file(test_filename, test_data1, sizeof(test_data1), path);

    hr = D3DX10CreateAsyncFileLoaderW(path, &loader);
    ok(SUCCEEDED(hr), "Failed to create file loader, hr %#x.\n", hr);

    ret = delete_file(test_filename);
    ok(ret, "DeleteFile() failed, ret %d, error %d.\n", ret, GetLastError());

    /* File was removed before Load(). */
    hr = ID3DX10DataLoader_Load(loader);
    ok(hr == D3D10_ERROR_FILE_NOT_FOUND, "Load() returned unexpected result, hr %#x.\n", hr);

    /* Create it again. */
    create_file(test_filename, test_data1, sizeof(test_data1), NULL);
    hr = ID3DX10DataLoader_Load(loader);
    ok(SUCCEEDED(hr), "Load() failed, hr %#x.\n", hr);

    /* Already loaded. */
    hr = ID3DX10DataLoader_Load(loader);
    ok(SUCCEEDED(hr), "Load() failed, hr %#x.\n", hr);

    ret = delete_file(test_filename);
    ok(ret, "DeleteFile() failed, ret %d, error %d.\n", ret, GetLastError());

    /* Already loaded, file removed. */
    hr = ID3DX10DataLoader_Load(loader);
    ok(hr == D3D10_ERROR_FILE_NOT_FOUND, "Load() returned unexpected result, hr %#x.\n", hr);

    /* Decompress still works. */
    ptr = NULL;
    hr = ID3DX10DataLoader_Decompress(loader, &ptr, &size);
    ok(SUCCEEDED(hr), "Decompress() failed, hr %#x.\n", hr);
    ok(ptr != NULL, "Got unexpected ptr %p.\n", ptr);
    ok(size == sizeof(test_data1), "Got unexpected decompressed size.\n");
    if (size == sizeof(test_data1))
        ok(!memcmp(ptr, test_data1, size), "Got unexpected file data.\n");

    /* Create it again, with different data. */
    create_file(test_filename, test_data2, sizeof(test_data2), NULL);

    hr = ID3DX10DataLoader_Load(loader);
    ok(SUCCEEDED(hr), "Load() failed, hr %#x.\n", hr);

    ptr = NULL;
    hr = ID3DX10DataLoader_Decompress(loader, &ptr, &size);
    ok(SUCCEEDED(hr), "Decompress() failed, hr %#x.\n", hr);
    ok(ptr != NULL, "Got unexpected ptr %p.\n", ptr);
    ok(size == sizeof(test_data2), "Got unexpected decompressed size.\n");
    if (size == sizeof(test_data2))
        ok(!memcmp(ptr, test_data2, size), "Got unexpected file data.\n");

    hr = ID3DX10DataLoader_Destroy(loader);
    ok(SUCCEEDED(hr), "Destroy() failed, hr %#x.\n", hr);

    ret = delete_file(test_filename);
    ok(ret, "DeleteFile() failed, ret %d, error %d.\n", ret, GetLastError());
}

static void test_D3DX10CreateAsyncResourceLoader(void)
{
    ID3DX10DataLoader *loader;
    HRESULT hr;

    hr = D3DX10CreateAsyncResourceLoaderA(NULL, NULL, NULL);
    ok(hr == E_FAIL, "Got unexpected hr %#x.\n", hr);

    hr = D3DX10CreateAsyncResourceLoaderA(NULL, NULL, &loader);
    ok(hr == D3DX10_ERR_INVALID_DATA, "Got unexpected hr %#x.\n", hr);

    hr = D3DX10CreateAsyncResourceLoaderA(NULL, "noname", &loader);
    ok(hr == D3DX10_ERR_INVALID_DATA, "Got unexpected hr %#x.\n", hr);

    hr = D3DX10CreateAsyncResourceLoaderW(NULL, NULL, NULL);
    ok(hr == E_FAIL, "Got unexpected hr %#x.\n", hr);

    hr = D3DX10CreateAsyncResourceLoaderW(NULL, NULL, &loader);
    ok(hr == D3DX10_ERR_INVALID_DATA, "Got unexpected hr %#x.\n", hr);

    hr = D3DX10CreateAsyncResourceLoaderW(NULL, L"noname", &loader);
    ok(hr == D3DX10_ERR_INVALID_DATA, "Got unexpected hr %#x.\n", hr);
}

static void test_get_image_info(void)
{
    static const WCHAR test_resource_name[] = L"resource.data";
    static const WCHAR test_filename[] = L"image.data";
    D3DX10_IMAGE_INFO image_info;
    HMODULE resource_module;
    WCHAR path[MAX_PATH];
    unsigned int i;
    DWORD dword;
    HRESULT hr;

    CoInitialize(NULL);

    hr = D3DX10GetImageInfoFromMemory(test_image[0].data, 0, NULL, &image_info, NULL);
    ok(hr == E_FAIL, "Got unexpected hr %#x.\n", hr);
    hr = D3DX10GetImageInfoFromMemory(NULL, test_image[0].size, NULL, &image_info, NULL);
    ok(hr == E_FAIL, "Got unexpected hr %#x.\n", hr);
    hr = D3DX10GetImageInfoFromMemory(&dword, sizeof(dword), NULL, &image_info, NULL);
    ok(hr == E_FAIL, "Got unexpected hr %#x.\n", hr);

    for (i = 0; i < ARRAY_SIZE(test_image); ++i)
    {
        winetest_push_context("Test %u", i);

        hr = D3DX10GetImageInfoFromMemory(test_image[i].data, test_image[i].size, NULL, &image_info, NULL);
        ok(hr == S_OK, "Got unexpected hr %#x.\n", hr);
        if (hr == S_OK)
            check_image_info(&image_info, test_image + i, __LINE__);

        winetest_pop_context();
    }

    hr = D3DX10GetImageInfoFromFileW(NULL, NULL, &image_info, NULL);
    ok(hr == E_FAIL, "Got unexpected hr %#x.\n", hr);
    hr = D3DX10GetImageInfoFromFileW(L"deadbeaf", NULL, &image_info, NULL);
    ok(hr == D3D10_ERROR_FILE_NOT_FOUND, "Got unexpected hr %#x.\n", hr);
    hr = D3DX10GetImageInfoFromFileA(NULL, NULL, &image_info, NULL);
    ok(hr == E_FAIL, "Got unexpected hr %#x.\n", hr);
    hr = D3DX10GetImageInfoFromFileA("deadbeaf", NULL, &image_info, NULL);
    ok(hr == D3D10_ERROR_FILE_NOT_FOUND, "Got unexpected hr %#x.\n", hr);

    for (i = 0; i < ARRAY_SIZE(test_image); ++i)
    {
        winetest_push_context("Test %u", i);
        create_file(test_filename, test_image[i].data, test_image[i].size, path);

        hr = D3DX10GetImageInfoFromFileW(path, NULL, &image_info, NULL);
        ok(hr == S_OK, "Got unexpected hr %#x.\n", hr);
        if (hr == S_OK)
            check_image_info(&image_info, test_image + i, __LINE__);

        hr = D3DX10GetImageInfoFromFileA(get_str_a(path), NULL, &image_info, NULL);
        ok(hr == S_OK, "Got unexpected hr %#x.\n", hr);
        if (hr == S_OK)
            check_image_info(&image_info, test_image + i, __LINE__);

        delete_file(test_filename);
        winetest_pop_context();
    }


    /* D3DX10GetImageInfoFromResource tests */

    hr = D3DX10GetImageInfoFromResourceW(NULL, NULL, NULL, &image_info, NULL);
    ok(hr == D3DX10_ERR_INVALID_DATA, "Got unexpected hr %#x.\n", hr);
    hr = D3DX10GetImageInfoFromResourceW(NULL, L"deadbeaf", NULL, &image_info, NULL);
    ok(hr == D3DX10_ERR_INVALID_DATA, "Got unexpected hr %#x.\n", hr);
    hr = D3DX10GetImageInfoFromResourceA(NULL, NULL, NULL, &image_info, NULL);
    ok(hr == D3DX10_ERR_INVALID_DATA, "Got unexpected hr %#x.\n", hr);
    hr = D3DX10GetImageInfoFromResourceA(NULL, "deadbeaf", NULL, &image_info, NULL);
    ok(hr == D3DX10_ERR_INVALID_DATA, "Got unexpected hr %#x.\n", hr);

    for (i = 0; i < ARRAY_SIZE(test_image); ++i)
    {
        winetest_push_context("Test %u", i);
        resource_module = create_resource_module(test_resource_name, test_image[i].data, test_image[i].size);

        hr = D3DX10GetImageInfoFromResourceW(resource_module, test_resource_name, NULL, &image_info, NULL);
        ok(hr == S_OK, "Got unexpected hr %#x.\n", hr);
        if (hr == S_OK)
            check_image_info(&image_info, test_image + i, __LINE__);

        hr = D3DX10GetImageInfoFromResourceA(resource_module, get_str_a(test_resource_name), NULL, &image_info, NULL);
        ok(hr == S_OK, "Got unexpected hr %#x.\n", hr);
        if (hr == S_OK)
            check_image_info(&image_info, test_image + i, __LINE__);

        delete_resource_module(test_resource_name, resource_module);
        winetest_pop_context();
    }

    CoUninitialize();
}

static void test_create_texture(void)
{
    ID3D10Resource *resource;
    ID3D10Device *device;
    unsigned int i;
    HRESULT hr;

    device = create_device();
    if (!device)
    {
        skip("Failed to create device, skipping tests.\n");
        return;
    }

    CoInitialize(NULL);

    /* D3DX10CreateTextureFromMemory tests */

    resource = (ID3D10Resource *)0xdeadbeef;
    hr = D3DX10CreateTextureFromMemory(device, NULL, 0, NULL, NULL, &resource, NULL);
    todo_wine
    ok(hr == E_FAIL, "Got unexpected hr %#x.\n", hr);
    ok(resource == (ID3D10Resource *)0xdeadbeef, "Got unexpected resource %p.\n", resource);

    resource = (ID3D10Resource *)0xdeadbeef;
    hr = D3DX10CreateTextureFromMemory(device, NULL, sizeof(test_bmp_1bpp), NULL, NULL, &resource, NULL);
    todo_wine
    ok(hr == E_FAIL, "Got unexpected hr %#x.\n", hr);
    ok(resource == (ID3D10Resource *)0xdeadbeef, "Got unexpected resource %p.\n", resource);

    resource = (ID3D10Resource *)0xdeadbeef;
    hr = D3DX10CreateTextureFromMemory(device, test_bmp_1bpp, 0, NULL, NULL, &resource, NULL);
    todo_wine
    ok(hr == E_FAIL, "Got unexpected hr %#x.\n", hr);
    ok(resource == (ID3D10Resource *)0xdeadbeef, "Got unexpected resource %p.\n", resource);

    resource = (ID3D10Resource *)0xdeadbeef;
    hr = D3DX10CreateTextureFromMemory(device, test_bmp_1bpp, sizeof(test_bmp_1bpp) - 1, NULL, NULL, &resource, NULL);
    todo_wine
    ok(hr == E_FAIL, "Got unexpected hr %#x.\n", hr);
    ok(resource == (ID3D10Resource *)0xdeadbeef, "Got unexpected resource %p.\n", resource);

    for (i = 0; i < ARRAY_SIZE(test_image); ++i)
    {
        winetest_push_context("Test %u", i);

        hr = D3DX10CreateTextureFromMemory(device, test_image[i].data, test_image[i].size, NULL, NULL, &resource, NULL);
        todo_wine
        ok(hr == S_OK, "Got unexpected hr %#x.\n", hr);
        if (hr == S_OK)
        {
            check_resource_info(resource, test_image + i, __LINE__);
            check_resource_data(resource, test_image + i, __LINE__);
            ID3D10Resource_Release(resource);
        }

        winetest_pop_context();
    }

    CoUninitialize();

    ID3D10Device_Release(device);
}

START_TEST(d3dx10)
{
    test_D3DX10UnsetAllDeviceObjects();
    test_D3DX10CreateAsyncMemoryLoader();
    test_D3DX10CreateAsyncFileLoader();
    test_D3DX10CreateAsyncResourceLoader();
    test_get_image_info();
    test_create_texture();
}
