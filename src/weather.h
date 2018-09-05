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

#ifndef EP_WEATHER_H
#define EP_WEATHER_H

// Headers
#include <string>
#include "drawable.h"
#include "system.h"

/**
 * Renders the weather effects.
 */
class Weather : public Drawable {
public:
	Weather();
	~Weather() override;

	void Draw() override;
	void Update();

	int GetZ() const override;
	DrawableType GetType() const override;

	Tone GetTone() const;
	void SetTone(Tone tone);

private:
	void DrawRain();
	void DrawSnow();
	void DrawFog();
	void DrawSandstorm();

	static const int z = Priority_Weather;
	static const DrawableType type = TypeWeather;

	BitmapRef weather_surface;
	BitmapRef snow_bitmap;
	BitmapRef rain_bitmap;

	Tone tone_effect;

	bool dirty;
};

#endif
