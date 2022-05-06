#ifndef IRESOURCEMANAGERMOCK_HPP_
#define IRESOURCEMANAGERMOCK_HPP_

#include <gmock/gmock.h>
#include <string_view>
#include <filesystem>
#include "Resource/IResourceManager.hpp"

namespace Test
{

class IResourceManagerMock final : public OpenLabora::IResourceManager
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

} // namespace Test

#endif // IRESOURCEMANAGERMOCK_HPP_
