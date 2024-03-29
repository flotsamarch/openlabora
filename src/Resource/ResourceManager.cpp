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

#include <cassert>
#include <filesystem>
#include <iostream>
#include <sstream>
#include "Resource/ResourceManager.hpp"
#include "LibTypedefs.hpp"

namespace open_labora
{

ResourceManager::ResourceManager(const std::filesystem::path& current_path)
{
    if (!current_path.has_parent_path()) {
        throw std::runtime_error(kMalformedCommandLine.data());
    }

    auto path = current_path.parent_path();
    auto dir = std::filesystem::directory_entry();

    for (int count = 0; path.has_parent_path(); ++count) {
        dir = std::filesystem::directory_entry(path / kResourceDirectoryName);
        if (dir.is_directory()) {
            break;
        }

        if (count > 3) {
            throw std::runtime_error(kNoResourceDirectory.data());
        }

        path = path.parent_path();
    }

    auto suffix = std::string_view(".png");

    for (auto&& file : std::filesystem::directory_iterator{ dir }) {
        if (!file.is_regular_file()) {
            continue;
        }

        auto filepath = file.path().string();

        if (filepath.substr(filepath.size() - suffix.size()) == suffix) {
            auto filename = file.path().filename().string();
            auto texture_name =
                filename.substr(0, filename.size() - suffix.size());
            auto texture = Texture{};

            if (!texture.loadFromFile(file.path().string())) {
                // TODO: Exception safety pass
                auto message = std::stringstream{ kLoadErrorFormat.data() };
                message << filename;
                throw std::runtime_error{ message.str() };
            }

            mTextures[texture_name] = texture;
        }
    }
}

std::optional<std::reference_wrapper<const Texture>>
ResourceManager::GetTexture(std::string_view name) const
{
    auto str = std::string{ name };
    auto&& result = mTextures.find(str);

    if (result == mTextures.end()) {
        return {};
    }

    return { mTextures.find(str)->second };
}

const Texture&
ResourceManager::GetTextureOrDefault(std::string_view name) const
{
    auto str = std::string{ name };
    auto&& result = mTextures.find(str);

    if (result == mTextures.end()) {
        return mTextures.find("coin")->second;
    }
    return mTextures.find(str)->second;
}

const Texture& ResourceManager::StoreTexture(std::string_view name,
                                             const Texture& texture)
{
    auto result = mTextures.insert_or_assign(std::string{ name }, texture);
    return result.first->second;
};

} // namespace open_labora
