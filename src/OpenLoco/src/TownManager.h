#pragma once

#include "Engine/Limits.h"
#include "Town.h"
#include <OpenLoco/Core/LocoFixedVector.hpp>
#include <array>
#include <optional>

namespace OpenLoco::TownManager
{
    void reset();
    FixedVector<Town, Limits::kMaxTowns> towns();
    Town* get(TownId id);
    std::optional<std::pair<TownId, uint8_t>> getClosestTownAndDensity(const World::Pos2& loc);
    void update();
    void updateLabels();
    void updateMonthly();
    Town* sub_497DC1(const World::Pos2& loc, uint32_t population, uint32_t populationCapacity, int16_t rating, int16_t numBuildings);
    void resetBuildingsInfluence();
    void registerHooks();
}
