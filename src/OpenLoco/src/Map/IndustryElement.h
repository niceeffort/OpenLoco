#pragma once

#include "TileElementBase.h"

namespace OpenLoco
{
    struct Industry;
}

namespace OpenLoco::World
{
#pragma pack(push, 1)

    struct IndustryElement : public TileElementBase
    {
        static constexpr ElementType kElementType = ElementType::industry;

    private:
        IndustryId _industryId;
        uint8_t _5;
        uint16_t _6;

    public:
        // var_4
        IndustryId industryId() const { return _industryId; }
        Industry* industry() const;
        // var_6_07C0
        uint8_t buildingType() const;
        uint8_t rotation() const { return _type & 0x3; }
        // var_5_03
        uint8_t sequenceIndex() const;
        // var_5_E0
        uint8_t sectionProgress() const;
        void setSectionProgress(uint8_t val);

        Colour var_6_F800() const;
        // This has two uses. When under construction it is the number of completed sections. Otherwise its animation sequence related
        uint8_t var_6_003F() const;
        void setVar_6_003F(uint8_t val);

        bool isConstructed() const { return _type & 0x80; }
        void setIsConstructed(bool val);

        bool update(const World::Pos2& loc);
    };
#pragma pack(pop)
    static_assert(sizeof(IndustryElement) == kTileElementSize);

    struct Animation;
    bool updateIndustryAnimation1(const Animation& anim);
    bool updateIndustryAnimation2(const Animation& anim);
}
