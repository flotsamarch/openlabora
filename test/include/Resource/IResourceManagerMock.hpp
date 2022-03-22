#ifndef IRESOURCEMANAGERMOCK_HPP_
#define IRESOURCEMANAGERMOCK_HPP_

#include <gmock/gmock.h>
#include <string_view>
#include "Resource/IResourceManager.hpp"

namespace Test
{

class IResourceManagerMock final : public OpenLabora::IResourceManager
{
public:
    using Ptr = std::shared_ptr<IResourceManagerMock>;

    MOCK_METHOD(const sf::Texture&, GetTextureByName, (std::string_view),
                (const, override));
};

} // namespace Test

#endif // IRESOURCEMANAGERMOCK_HPP_
