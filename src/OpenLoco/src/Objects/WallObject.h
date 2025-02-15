#pragma once

#include "Object.h"
#include "Types.hpp"
#include <OpenLoco/Core/Span.hpp>

namespace OpenLoco
{
    namespace ObjectManager
    {
        struct DependentObjects;
    }
    namespace Gfx
    {
        struct RenderTarget;
    }

#pragma pack(push, 1)
    struct WallObject
    {
        static constexpr auto kObjectType = ObjectType::wall;

        string_id name;
        uint32_t sprite; // 0x02
        uint8_t var_06;
        uint8_t flags; // 0x07
        uint8_t var_08;
        uint8_t var_09;

        // 0x004C4AF0
        bool validate() const { return true; }
        void load(const LoadedObjectHandle& handle, stdx::span<const std::byte> data, ObjectManager::DependentObjects*);
        void unload();
        void drawPreviewImage(Gfx::RenderTarget& rt, const int16_t x, const int16_t y) const;
    };
#pragma pack(pop)
    static_assert(sizeof(WallObject) == 0xA);
}
