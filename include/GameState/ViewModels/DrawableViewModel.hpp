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

#ifndef DRAWABLEVIEWMODEL_HPP_
#define DRAWABLEVIEWMODEL_HPP_

#include "Misc/PtrView.hpp"
#include "ECS/Entity.hpp"
#include "Game/Components/SpriteComponent.hpp"
#include "Game/Systems/PlayfieldSystem.hpp"

namespace open_labora
{

template<class TModel>
class DrawableViewModel final
{
    PtrView<TModel> mModel;

public:
    DrawableViewModel(PtrView<TModel> model)
        : mModel{ model }
    {
    }

    void FillDrawableContainer()
    {
        auto&& registry = mModel->GetRegistry();
        registry.HandleEvent(DrawEvent{});

        auto fill = [&model = mModel] (Entity, const SpriteComponent& sprite)
        {
            model->AddDrawableObject(sprite.GetDrawableObject());
        };

        registry.template ForEachComponent<SpriteComponent>(fill);
    }
};

} // namespace open_labora

#endif // DRAWABLEVIEWMODEL_HPP_
