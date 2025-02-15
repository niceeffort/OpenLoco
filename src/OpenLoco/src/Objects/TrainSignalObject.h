#pragma once

#include "Object.h"
#include "Types.hpp"
#include <OpenLoco/Core/EnumFlags.hpp>
#include <OpenLoco/Core/Span.hpp>
#include <vector>

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

    enum class TrainSignalObjectFlags : uint16_t
    {
        none = 0U,
        isLeft = 1U << 0,
        hasLights = 1U << 1,
    };
    OPENLOCO_ENABLE_ENUM_OPERATORS(TrainSignalObjectFlags);

    namespace TrainSignal::ImageIds
    {
        constexpr uint32_t redLights = 80;
        constexpr uint32_t redLights2 = 88;
        constexpr uint32_t greenLights = 96;
        constexpr uint32_t greenLights2 = 104;
    }
#pragma pack(push, 1)
    struct TrainSignalObject
    {
        static constexpr auto kObjectType = ObjectType::trackSignal;

        string_id name;
        TrainSignalObjectFlags flags; // 0x02
        uint8_t animationSpeed;       // 0x04
        uint8_t numFrames;            // 0x05
        int16_t costFactor;           // 0x06
        int16_t sellCostFactor;       // 0x08
        uint8_t costIndex;            // 0x0A
        uint8_t var_0B;
        uint16_t var_0C;
        uint32_t image;        // 0x0E
        uint8_t numCompatible; // 0x12
        uint8_t mods[7];       // 0x13
        uint16_t designedYear; // 0x1A
        uint16_t obsoleteYear; // 0x1C

        bool validate() const;
        void load(const LoadedObjectHandle& handle, stdx::span<const std::byte> data, ObjectManager::DependentObjects*);
        void unload();
        void drawPreviewImage(Gfx::RenderTarget& rt, const int16_t x, const int16_t y) const;
        constexpr bool hasFlags(TrainSignalObjectFlags flagsToTest) const
        {
            return (flags & flagsToTest) != TrainSignalObjectFlags::none;
        }
    };
#pragma pack(pop)
    static_assert(sizeof(TrainSignalObject) == 0x1E);

    const std::vector<uint8_t> signalFrames2State = { 1, 2, 3, 3, 3, 3, 3, 3, 2, 1, 0, 0, 0, 0, 0 };
    const std::vector<uint8_t> signalFrames3State = { 1, 2, 3, 3, 3, 3, 3, 3, 3, 4, 5, 6, 6, 6, 6, 6, 6, 6, 6, 5, 4, 3, 2, 1, 0, 0, 0, 0, 0, 0, 0 };
    const std::vector<uint8_t> signalFrames4State = { 1, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 5, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 7, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    static const std::vector<std::vector<uint8_t>> signalFrames = {
        signalFrames2State,
        signalFrames3State,
        signalFrames4State,
    };
}
