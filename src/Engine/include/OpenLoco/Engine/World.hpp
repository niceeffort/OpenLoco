#pragma once

#include "Types.hpp"
#include <OpenLoco/Math/Vector.hpp>

namespace OpenLoco::World
{
    constexpr coord_t kTileSize = 32;
    constexpr coord_t kMapRows = 384;
    constexpr coord_t kMapColumns = 384;
    constexpr coord_t kMapPitch = 512;
    constexpr coord_t kMapHeight = kMapRows * kTileSize;
    constexpr coord_t kMapWidth = kMapColumns * kTileSize;
    constexpr int32_t kMapSize = kMapColumns * kMapRows;
    constexpr int16_t kMicroZStep = 16;       // e.g. SurfaceElement::water is a microZ
    constexpr int16_t kMicroToSmallZStep = 4; // e.g. for comparisons between water and baseZ
    constexpr int16_t kSmallZStep = 4;        // e.g. TileElement::baseZ is a smallZ
    using SmallZ = uint8_t;
    using MicroZ = uint8_t;

    constexpr coord_t tileFloor(coord_t coord)
    {
        return coord & (kTileSize - 1);
    }

    using Pos2 = Math::Vector::TVector2<coord_t, 1>;
    using Pos3 = Math::Vector::TVector3<coord_t, 1>;
    using TilePos2 = Math::Vector::TVector2<coord_t, kTileSize>;

    // Until interop is removed this is a requirement.
    static_assert(sizeof(Pos2) == 4);
    static_assert(sizeof(Pos3) == 6);
    static_assert(sizeof(TilePos2) == 4);

    constexpr bool validCoord(const coord_t coord)
    {
        return (coord >= 0) && (coord < kMapWidth);
    }

    constexpr bool validTileCoord(const coord_t coord)
    {
        return (coord >= 0) && (coord < kMapColumns);
    }

    constexpr bool validCoords(const Pos2& coords)
    {
        return validCoord(coords.x) && validCoord(coords.y);
    }

    constexpr bool validCoords(const TilePos2& coords)
    {
        return validTileCoord(coords.x) && validTileCoord(coords.y);
    }

    // drawing coordinates validation differs from general valid coordinate validation
    constexpr bool drawableCoord(const coord_t coord)
    {
        return (coord >= (World::kTileSize - 1)) && (coord < (World::kMapWidth - World::kTileSize));
    }

    constexpr bool drawableCoords(const Pos2& coords)
    {
        return drawableCoord(coords.x) && drawableCoord(coords.y);
    }
}
