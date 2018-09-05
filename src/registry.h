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

#ifndef EP_REGISTRY_H
#define EP_REGISTRY_H

// Headers
#include <string>
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
enum HKEY {
	HKEY_LOCAL_MACHINE,
	HKEY_CURRENT_USER
};
#endif
enum REGVIEW {
	NATIVE,
	KEY64,
	KEY32
};

/**
 * Registry namespace
 */
namespace Registry {
	/**
	 * Reads string value.
	 */
	std::string ReadStrValue(HKEY hkey, std::string const& key, std::string const& val, REGVIEW view = NATIVE);

	/**
	 * Reads binary value.
	 */
	int ReadBinValue(HKEY hkey, std::string const& key, std::string const& val, unsigned char* bin, REGVIEW view = NATIVE);
}

#endif
