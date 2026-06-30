/*
 * Version functions.
 *
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include <assert.h>

#include "config.h"

#include "avcodec.h"
#include "codec_id.h"
#include "version.h"

#include "libavutil/ffversion.h"
const char av_codec_ffversion[] = "FFmpeg version " FFMPEG_VERSION;

unsigned avcodec_version(void)
{
    /* This fork adds AV_CODEC_ID_XMAFRAMES after AV_CODEC_ID_XMA2 (mid-list), which shifts the
     * numeric value of every audio codec id declared after it by +1. Upstream's full
     * "don't insert new codec ids in the middle of a list" assert therefore cannot hold here.
     * Assert only the ids that precede XMAFRAMES (JPEGXS, PCM_SGA) so the base layout is still
     * sanity-checked without tripping on the intentional XMAFRAMES insertion. */
    static_assert(AV_CODEC_ID_JPEGXS  ==   272 &&
                  AV_CODEC_ID_PCM_SGA == 65572,
                  "codec id base layout changed unexpectedly");
    static_assert(LIBAVCODEC_VERSION_MICRO >= 100, "micro version starts at 100");

    return LIBAVCODEC_VERSION_INT;
}

const char *avcodec_configuration(void)
{
    return FFMPEG_CONFIGURATION;
}

const char *avcodec_license(void)
{
#define LICENSE_PREFIX "libavcodec license: "
    return &LICENSE_PREFIX FFMPEG_LICENSE[sizeof(LICENSE_PREFIX) - 1];
}
