// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
//
// OpenLabora (c) by Flotsamarch (https://github.com/flotsamarch)
//
// This work is licensed under the Creative Commons
// Attribution-NonCommercial-ShareAlike 4.0 International License.
//
// You should have received a copy of the license along with this
// work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.
//
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

#ifndef PLOTACQUISITIONMARKER_HPP_
#define PLOTACQUISITIONMARKER_HPP_

#include "ECS/Registry.hpp"
#include "Game/Plot.hpp"

namespace open_labora
{

namespace plot_acquisition_marker
{

using TextureIds = std::span<const std::string_view>;

inline static const Color kHalfTransparent{ 255, 255, 255, 200 };

constexpr float kMarkerOverlapFactor = 1.f / 3.f;

Entity create(RegistryRef,
              lot::Type,
              bool does_add_to_top,
              IResourceManager::Ptr);

void initilizeSpriteComponent(Entity marker, IResourceManager::Ptr);

constexpr TextureIds getTextures(lot::Type lot_type);

void setPosition(Entity marker, const Vector2f&);

lot::Type getLotType(Entity marker);

void setInteractiveRect(Entity marker,
                        const Vector2f& offset,
                        const Vector2f& size);

Vector2f getSize(lot::Type);

// ------------------ ADD TEXTURE ID FOR EACH MARKER HERE ----------------------
constexpr std::string_view kCoastalMarkerTextureName = "coastal_marker";
constexpr std::string_view kCentralMarkerTextureName = "central_marker";
constexpr std::string_view kCentralAltMarkerTextureName = "central_alt_marker";
constexpr std::string_view kMountainMarkerTextureName = "mountain_marker";

// ----------------------- GROUP TEXTURE IDS BY LOT TYPE -----------------------
constexpr std::array kCoastalMarkerTextureNames
{ kCoastalMarkerTextureName };

constexpr std::array kCentralMarkerTextureNames
{ kCentralMarkerTextureName, kCentralAltMarkerTextureName };

constexpr std::array kMountainMarkerTextureNames
{ kMountainMarkerTextureName };

// -------------------- MAP TEXTURE ID GROUPS TO LOT TYPES ---------------------
constexpr EnumMap<lot::Type, TextureIds> kTextureIdsMap
{
    { lot::Type::Coastal, { kCoastalMarkerTextureNames } },
    { lot::Type::Central, { kCentralMarkerTextureNames } },
    { lot::Type::Mountain, { kMountainMarkerTextureNames } },
};

constexpr TextureIds getTextures(lot::Type lot_type)
{
    return kTextureIdsMap[lot_type];
}

} // namespace plot_acquisition_marker

} // namespace open_labora

#endif // PLOTACQUISITIONMARKER_HPP_
