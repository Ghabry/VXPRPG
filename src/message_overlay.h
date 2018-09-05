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

#ifndef EP_MESSAGE_OVERLAY_H
#define EP_MESSAGE_OVERLAY_H

#include <deque>
#include <string>
#include "color.h"
#include "drawable.h"
#include "tone.h"

class MessageOverlayItem {
public:
	MessageOverlayItem(const std::string& text, Color color);

	std::string text;
	Color color;
	bool hidden;
	int repeat_count;
};

/**
 * MessageOverlay class.
 * Displays notifications during the game session.
 */
class MessageOverlay : public Drawable {
public:
	MessageOverlay();
	~MessageOverlay() override;

	void Draw() override;

	int GetZ() const override;

	DrawableType GetType() const override;

	bool IsGlobal() const override;

	void Update();

	void AddMessage(const std::string& message, Color color);

	void SetShowAll(bool show_all);

private:
	bool IsAnyMessageVisible() const;

	DrawableType type;

	BitmapRef bitmap;
	BitmapRef black;

	int z;
	int ox;
	int oy;

	int text_height;
	int message_max;

	std::deque<MessageOverlayItem> messages;
	/** Last message added to the console before linebreak processing */
	std::string last_message;

	bool dirty;

	int counter;

	bool show_all;
};

#endif
