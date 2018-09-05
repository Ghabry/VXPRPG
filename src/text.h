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

#ifndef EP_TEXT_H
#define EP_TEXT_H

#include "system.h"
#include "font.h"
#include <string>

namespace Text {
	/** TextDraw alignment options. */
	enum Alignment {
		AlignLeft,
		AlignCenter,
		AlignRight
	};

	void Draw(Bitmap& dest, int x, int y, int color, FontRef font, std::string const& text, Text::Alignment align = Text::AlignLeft);

	/**
	 * Draws text using the specified color on dest
	 */
	void Draw(Bitmap& dest, int x, int y, Color color, FontRef font, std::string const& text);
}
#endif
