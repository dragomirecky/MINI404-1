/*
	IPCIndicator.h - Simple LED visualizer for IPC

	Copyright 2020 VintagePC <https://github.com/vintagepc/> as part of MK404
    Adapted for Mini404 in 2021

 	This file is part of MINI404.

	MINI404 is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	MINI404 is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with MINI404.  If not, see <http://www.gnu.org/licenses/>.
 */


#pragma once

#include "Util.h"            // for hexColor_t
#include <atomic>
#include <cstdint>          // for uint32_t, uint8_t

class IPCIndicator
{
public:
	// Creates a new LED with RGBA color (A ignored) uiHexColor and char label chrLabel
	IPCIndicator(char chrLabel);
	// Draws the LED
	void Draw();

	inline void SetValue(uint8_t value) { m_uiBrightness = value; }

	inline void SetLabel(char label) { m_chrLabel = label;}

	inline void SetColor(uint32_t color) { m_Color = hexColor_t(color); }

private:
	// Value changed callback.
	hexColor_t m_Color = hexColor_t(0x00FF0000);
	char m_chrLabel = ' ';
	std::atomic_uint8_t m_uiBrightness = {0};
	bool m_bInvert = false;
};
