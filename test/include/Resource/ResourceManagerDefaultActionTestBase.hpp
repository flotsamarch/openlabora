#ifndef RESOURCEMANAGERDEFAULTACTIONTESTBASE_HPP_
#define RESOURCEMANAGERDEFAULTACTIONTESTBASE_HPP_

#include "ResourceManagerMock.hpp"

namespace test
{

class ResourceManagerDefaultActionTestBase : public ::testing::Test
{
    using ResourceMgr = testing::NiceMock<ResourceManagerMock>;
    using ResourceMgrPtr = std::shared_ptr<ResourceMgr>;
    std::filesystem::path mPath{};

protected:
    sf::Texture mTexture{};
    ResourceMgrPtr mResourceMgr{ std::make_shared<ResourceMgr>(mPath) };

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

} // namespace test

#endif // RESOURCEMANAGERDEFAULTACTIONTESTBASE_HPP_
