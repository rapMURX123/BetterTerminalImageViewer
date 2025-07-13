/*
 * Copyright (c) 2025 Stefan Haustein, Aaron Liu and rapMURX123
 *
 * This program is free software: you may copy, redistribute and/or modify it
 * under the terms of (at your option) either the Apache License, Version 2.0,
 * or the GNU General Public License as published by the Free Software Foundation,
 * version 3, or any later version.
 *
 * This file is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 *
 * For details, see either
 *   https://www.apache.org/licenses/LICENSE-2.0 for the Apache License, Version 2.0,
 * or
 *   https://www.gnu.org/licenses/gpl-3.0.en.html for the GNU GPL, version 3.
 *
 * Note that this code includes the CImg library,
 * which is licensed under either
 *   CeCILL 2.0 (https://spdx.org/licenses/CECILL-2.0.html)
 *   (close to GPL and compatible with it) or
 *   CeCILL-C (https://spdx.org/licenses/CECILL-C)
 *   (close to LGPL and compatible with Apache).
 *
 * This project is a fork of Terminal Image Viewer (tiv) by Stefan Haustein.
 * The fork is maintained by rapMURX123 and distributed under the same licensing terms.
 */


#ifndef TIV_LIB_H
#define TIV_LIB_H


#include <array>
#include <functional>

// Implementation of flag representation for flags in the main() method
constexpr int FLAG_FG = 1;
constexpr int FLAG_BG = 2;
constexpr int FLAG_MODE_256 = 4;   // Limit colors to 256-color mode
constexpr int FLAG_24BIT = 8;      // 24-bit color mode
constexpr int FLAG_NOOPT = 16;     // Only use the same half-block character
constexpr int FLAG_TELETEXT = 32;  // Use teletext characters


// Color saturation value steps from 0 to 255
constexpr int COLOR_STEP_COUNT = 6;
constexpr int COLOR_STEPS[COLOR_STEP_COUNT] = {0, 0x5f, 0x87, 0xaf, 0xd7, 0xff};

// Grayscale saturation value steps from 0 to 255
constexpr int GRAYSCALE_STEP_COUNT = 24;
constexpr int GRAYSCALE_STEPS[GRAYSCALE_STEP_COUNT] = {
    0x08, 0x12, 0x1c, 0x26, 0x30, 0x3a, 0x44, 0x4e, 0x58, 0x62, 0x6c, 0x76,
    0x80, 0x8a, 0x94, 0x9e, 0xa8, 0xb2, 0xbc, 0xc6, 0xd0, 0xda, 0xe4, 0xee};


typedef std::function<unsigned long(int, int)> GetPixelFunction;

unsigned char get_channel(unsigned long rgb, int index);

int clamp_byte(int value);

int best_index(int value, const int STEPS[], int count);

double sqr(double n);

/**
 * @brief Struct to represent a character to be drawn.
 * @param fgColor RGB
 * @param bgColor RGB
 * @param codePoint The code point of the character to be drawn.
 */
struct CharData {
    std::array<int, 3> fgColor = std::array<int, 3>{0, 0, 0};
    std::array<int, 3> bgColor = std::array<int, 3>{0, 0, 0};
    int codePoint;
};

// Return a CharData struct with the given code point and corresponding averag
// fg and bg colors.
CharData createCharData(GetPixelFunction get_pixel, int x0, int y0,
                        int codepoint, int pattern);

/**
 * @brief Find the best character and colors
 * for a 4x8 part of the image at the given position
 *
 * @param image
 * @param x0
 * @param y0
 * @param flags
 * @return CharData
 */
CharData findCharData(GetPixelFunction get_pixel, int x0, int y0,
                      const int &flags);

#endif 
