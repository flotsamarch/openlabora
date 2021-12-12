#ifndef RESOURCEMANAGERMOCK_HPP_
#define RESOURCEMANAGERMOCK_HPP_

#include <gmock/gmock.h>
#include "resource/IResourceManager.hpp"

namespace Test
{

class ResourceManagerMock : public IResourceManager
{
public:
    MOCK_METHOD(const sf::Texture&, GetTextureByName, (std::string_view),
                (const, override));
};

}

#endif // RESOURCEMANAGERMOCK_HPP_
