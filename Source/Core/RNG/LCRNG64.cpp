/*
 * This file is part of PokéFinder
 * Copyright (C) 2017-2023 by Admiral_Fish, bumba, and EzPzStreamz
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include "LCRNG64.hpp"

template <class RNG>
static consteval JumpTable64 computeJumpTable64()
{
    JumpTable64 table;
    table.add[0] = RNG::getAdd();
    table.mult[0] = RNG::getMult();

    for (int i = 1; i < 32; i++)
    {
        table.add[i] = table.add[i - 1] * (table.mult[i - 1] + 1);
        table.mult[i] = table.mult[i - 1] * table.mult[i - 1];
    }

    return table;
}

constexpr JumpTable64 BWRNGTable = computeJumpTable64<BWRNG>();
constexpr JumpTable64 BWRNGRTable = computeJumpTable64<BWRNGR>();
