/*
 * This file is part of VXPRPG and based on the same file of EasyRPG Player.
 *
 * VXPRPG Player is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * VXPRPG Player is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with VXPRPG Player. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef EP_IMAGE_PNG_H
#define EP_IMAGE_PNG_H

#include "system.h"
#ifdef SUPPORT_PNG

#include <cstdio>
#include <ostream>

namespace ImagePNG {
	bool ReadPNG(FILE* stream, const void* buffer, bool transparent, int& width, int& height, void*& pixels);
	bool WritePNG(std::ostream& os, uint32_t width, uint32_t height, uint32_t* data);
}

#endif // SUPPORT_PNG
#endif
