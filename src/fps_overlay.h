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

#ifndef EP_FPS_OVERLAY_H
#define EP_FPS_OVERLAY_H

#include <deque>
#include <string>
#include "drawable.h"
#include "rect.h"

/**
 * FpsOverlay class.
 * Shows current FPS and the speedup indicator.
 */
class FpsOverlay : public Drawable {
public:
	FpsOverlay();
	~FpsOverlay() override;

	void Draw() override;

	int GetZ() const override;

	DrawableType GetType() const override;

	bool IsGlobal() const override;

	void Update();

	/**
	 * Returns the value the FPS counter had when ResetCounter() was called.
	 *
	 * @return fps counter value
	 */
	int GetFps() const;

	/**
	 * Returns the value the UPS counter had when ResetCounter() was called.
	 *
	 * @return ups counter value
	 */
	int GetUps() const;

	/**
	 * Increments the FPS counter by one.
	 */
	void AddFrame();

	/**
	 * Increments the UPS (updates) counter by one.
	 */
	void AddUpdate();

	/**
	 * Resets FPS and UPS counter to 0.
	 */
	void ResetCounter();

	/**
	 * Formats a string containing FPS.
	 *
	 * @return fps string
	 */
	std::string GetFpsString() const;

private:
	DrawableType type;

	BitmapRef fps_bitmap;
	BitmapRef speedup_bitmap;

	int z;

	bool fps_dirty = false;
	bool speedup_dirty = false;

	/** Frames per second */
	int fps = 0;
	int last_fps = 0;
	/** Logic updates per second */
	int ups = 0;
	int last_ups = 0;

	/** Rect to draw on screen */
	Rect fps_rect;
	Rect speedup_rect;

	int last_speed_mod = 1;
};

#endif
