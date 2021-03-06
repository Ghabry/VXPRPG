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

#ifndef EP_MAIN_DATA_H
#define EP_MAIN_DATA_H

// Headers
#include <string>

/**
 * Main Data namespace.
 */
class Game_Player;
class Game_Screen;
class Game_Party;
class Game_EnemyParty;

namespace Main_Data {
	void Init();
	void Cleanup();

	const std::string& GetProjectPath();
	void SetProjectPath(const std::string& path);

	const std::string& GetSavePath();
	void SetSavePath(const std::string& path);
}

#endif
