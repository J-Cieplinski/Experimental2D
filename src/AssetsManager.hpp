#pragma once

#include <map>
#include <cassert>
#include "util.hpp"
#define assertm(exp, msg) assert(((void)msg, exp))


template <typename Identifier, typename AssetType>
class AssetsManager {
    public:
        void loadAsset(const char* path, Identifier id);

        const AssetType& getAsset(Identifier id) const;
        AssetType& getAsset(Identifier id);
    private:
        std::map<Identifier, std::unique_ptr<AssetType>> assets_;
};

template<typename Identifier, typename AssetType>
void AssetsManager<Identifier, AssetType>::loadAsset(const char *path, Identifier id) {
    auto asset = std::make_unique<AssetType>();
    assert(asset->loadFromFile(path));
    assets_[id] = std::move(asset);
}

template<typename Identifier, typename AssetType>
const AssetType &AssetsManager<Identifier, AssetType>::getAsset(Identifier id) const {
    auto found = assets_.find(id);
    auto msg = "No file " << id;
    assertm(found != assets_.end(), msg);

    return *found->second;
}

template<typename Identifier, typename AssetType>
AssetType &AssetsManager<Identifier, AssetType>::getAsset(Identifier id) {
    auto found = assets_.find(id);
    auto msg = "No file " << id;
    assertm(found != assets_.end(), msg);

    return *found->second;
}
