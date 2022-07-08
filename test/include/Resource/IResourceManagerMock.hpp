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

#ifndef IRESOURCEMANAGERMOCK_HPP_
#define IRESOURCEMANAGERMOCK_HPP_

#include <gmock/gmock.h>
#include <string_view>
#include <filesystem>
#include "Resource/IResourceManager.hpp"

namespace test
{

class IResourceManagerMock : public open_labora::IResourceManager
{
public:
    using Ptr = std::shared_ptr<IResourceManagerMock>;

    IResourceManagerMock(const std::filesystem::path&) {};

    MOCK_METHOD(const sf::Texture&, GetTextureOrDefault, (std::string_view),
                (const, override));

    MOCK_METHOD(IResourceManager::OptionalTextureRef, GetTexture,
                (std::string_view), (const, override));

    MOCK_METHOD(const sf::Texture&, RegisterTexture,
                (std::string_view, const sf::Texture&), (override));
};

} // namespace test

#endif // IRESOURCEMANAGERMOCK_HPP_
