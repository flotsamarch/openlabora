#ifndef RESOURCEMANAGERDEFAULTACTIONTESTBASE_HPP_
#define RESOURCEMANAGERDEFAULTACTIONTESTBASE_HPP_

#include "IResourceManagerMock.hpp"

namespace Test
{

class ResourceManagerDefaultActionTestBase : public ::testing::Test
{
    using ResourceMgr = IResourceManagerMock;
    std::filesystem::path mPath{};
    sf::Texture mTexture{};

protected:
    ResourceMgr::Ptr mResourceMgr{ std::make_shared<ResourceMgr>(mPath) };

public:
    ResourceManagerDefaultActionTestBase(const sf::Texture& texture)
        : mTexture{ texture }
    {
        ON_CALL(*mResourceMgr, GetTexture)
            .WillByDefault(::testing::Return(mTexture));

        ON_CALL(*mResourceMgr, GetTextureOrDefault)
            .WillByDefault(::testing::ReturnRef(mTexture));
    }

    ResourceManagerDefaultActionTestBase()
        : ResourceManagerDefaultActionTestBase(sf::Texture{}) {};
};

} // namespace Test

#endif // RESOURCEMANAGERDEFAULTACTIONTESTBASE_HPP_
