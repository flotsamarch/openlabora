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
