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

#ifndef RESOURCEMANAGERMOCK_HPP_
#define RESOURCEMANAGERMOCK_HPP_

#include <gmock/gmock.h>
#include <string_view>
#include <filesystem>
#include "Resource/IResourceManager.hpp"

namespace test
{

namespace ol = open_labora;

class ResourceManagerMock : public ol::IResourceManager
{
public:
    using Ptr = std::shared_ptr<ResourceManagerMock>;

    ResourceManagerMock() = default;
    ResourceManagerMock(const std::filesystem::path&) {};

    MOCK_METHOD(const ol::Texture&, GetTextureOrDefault, (std::string_view),
                (const, override));

    MOCK_METHOD(IResourceManager::OptionalTextureRef, GetTexture,
                (std::string_view), (const, override));

    MOCK_METHOD(const ol::Texture&, RegisterTexture,
                (std::string_view, const ol::Texture&), (override));
};

} // namespace test

#endif // RESOURCEMANAGERMOCK_HPP_
