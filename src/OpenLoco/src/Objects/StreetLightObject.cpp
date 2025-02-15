#include "StreetLightObject.h"
#include "Drawing/SoftwareDrawingEngine.h"
#include "Graphics/Gfx.h"
#include "ObjectImageTable.h"
#include "ObjectManager.h"
#include "ObjectStringTable.h"
#include <OpenLoco/Interop/Interop.hpp>
#include <cassert>

namespace OpenLoco
{
    // TODO: This should only be definined in the ObjectSelectionWindow header
    static constexpr uint8_t kDescriptionRowHeight = 10;

    // 0x00477F69
    void StreetLightObject::drawPreviewImage(Gfx::RenderTarget& rt, const int16_t x, const int16_t y) const
    {
        Ui::Point imgPosition = Ui::Point{ x, y } - Ui::Point{ 20, 1 };
        auto& drawingCtx = Gfx::getDrawingEngine().getDrawingContext();
        for (auto i = 0; i < 3; i++)
        {
            auto imageId = (i * 4) + image;
            drawingCtx.drawImage(&rt, imgPosition.x - 14, imgPosition.y, imageId + 2);
            drawingCtx.drawImage(&rt, imgPosition.x, imgPosition.y - 7, imageId);
            imgPosition.x += 20;
            imgPosition.y += kDescriptionRowHeight;
        }
    }

    // 0x00477F19
    void StreetLightObject::load(const LoadedObjectHandle& handle, stdx::span<const std::byte> data, ObjectManager::DependentObjects*)
    {
        auto remainingData = data.subspan(sizeof(StreetLightObject));

        // Load object name string
        auto strRes = ObjectManager::loadStringTable(remainingData, handle, 0);
        name = strRes.str;
        remainingData = remainingData.subspan(strRes.tableLength);
        // Load images
        auto imageRes = ObjectManager::loadImageTable(remainingData);
        image = imageRes.imageOffset;

        // Ensure we've loaded the entire object
        assert(remainingData.size() == imageRes.tableLength);
    }

    // 0x00477F52
    void StreetLightObject::unload()
    {
        name = 0;
        image = 0;
    }
}
