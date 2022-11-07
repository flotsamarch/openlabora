set(sources
    # Components
    # Gameplay classes
    # src/Game/ExpansionMarker.cpp
    # src/Game/MarkerController.cpp
    src/Game/Lot.cpp
    src/Game/LotDeque.cpp
    # src/Game/Location.cpp
    # Gameplay systems
    src/Game/Systems/PlayfieldSystem.cpp
    # Game states
    src/GameState/Final.cpp
    src/GameState/MainMenu.cpp
    src/GameState/Duel.cpp
    # GUI
    # src/GUI/ExpansionInterface.cpp
    # src/GUI/ExpansionWindow.cpp
    # Game systems
    src/Input/Input.cpp
    src/Resource/ResourceManager.cpp
)

set(exe_sources
        src/main.cpp
        ${sources}
)

set(headers
    # Components
    include/Game/Components/PositionComponent.hpp
    include/Game/Components/DynamicTextureComponent.hpp
    include/Game/Components/SpriteComponent.hpp
    include/Game/Components/SelectableComponent.hpp
    include/Game/Components/SignalComponent.hpp
    include/Game/Components/InteractionAreaComponent.hpp
    include/Game/Components/LotDequeComponent.hpp
    # Gameplay classes
    include/Game/Signal.hpp
    include/Game/Tile.hpp
    include/Game/Lot.hpp
    include/Game/Plot.hpp
    include/Game/LotDeque.hpp
    # include/Game/Location.hpp
    # Gameplay systems
    include/Game/Systems/PlayfieldSystem.hpp
    # Game states
    include/GameState/Views/ViewConcept.hpp
    include/GameState/ViewToViewModelBinding.hpp
    include/GameState/Views/EscapeMenuView.hpp
    include/GameState/ViewModels/EscapeMenuViewModel.hpp
    include/GameState/Views/DrawableView.hpp
    include/GameState/ViewModels/DrawableViewModel.hpp
    include/GameState/FinalFwd.hpp
    include/GameState/Final.hpp
    include/GameState/MainMenuFwd.hpp
    include/GameState/MainMenu.hpp
    include/GameState/DuelFwd.hpp
    include/GameState/Duel.hpp
    include/GameState/GameController.hpp
    include/GameState/Model.hpp
    # GUI
    # include/GUI/Subviews/SubviewInitializer.hpp
    # include/GUI/Subviews/ExpansionSubview.hpp
    # include/GUI/ExpansionWindow.hpp
    # Misc
    include/Misc/RangeWrapper.hpp
    include/Misc/PtrView.hpp
    include/Misc/EnumMap.hpp
    include/Misc/UID.hpp
    include/Misc/CommonTypedefs.hpp
    include/Misc/IterableEnumUtilities.hpp
    # ECS
    include/ECS/MassAssignComponents.hpp
    include/ECS/Entity.hpp
    include/ECS/System.hpp
    include/ECS/Feature.hpp
    include/ECS/Registry.hpp
    include/ECS/Predicates.hpp
    # Game systems
    include/LibTypedefs.hpp
    include/Input/Input.hpp
    include/ApplicationState/ApplicationState.hpp
    include/Resource/ResourceManager.hpp
    include/Resource/IResourceManager.hpp
    include/IGameWindow.hpp
    include/GameWindow.hpp
    include/Renderer.hpp
    include/ApplicationState/ApplicationContext.hpp
    include/Application.hpp
)

set(test_sources
    # GUI
    # src/GUI/ExpansionWindowTests.cpp
    # Misc
    src/Misc/PtrViewTests.cpp
    src/Misc/RangeWrapperTests.cpp
    src/Misc/EnumMapTests.cpp
    src/Misc/UIDTests.cpp
    src/Misc/TupleUtilsTests.cpp
    src/Misc/IterableEnumUtilitiesTests.cpp
    # ECS
    src/ECS/EntityTests.cpp
    src/ECS/MassAssignComponentsTests.cpp
    src/ECS/FeatureTests.cpp
    src/ECS/SystemTests.cpp
    src/ECS/RegistryTests.cpp
    # Game systems
    src/Input/InputTests.cpp
    src/ApplicationState/ApplicationStateTests.cpp
    src/ApplicationTests.cpp
    src/GameState/GameControllerTests.cpp
    src/GameState/GameStateTests.cpp
    src/GameState/ModelTests.cpp
    # Game Views
    src/GameState/Views/CameraViewTests.cpp
    src/GameState/Views/EscapeMenuViewTests.cpp
    # Game states
    src/GameState/FinalStateTests.cpp
    src/GameState/MainMenuTests.cpp
    src/GameState/DuelTests.cpp
    # Components
    src/Game/Components/PositionComponentTests.cpp
    src/Game/Components/LotDequeComponentTests.cpp
    src/Game/Components/DynamicTextureComponentTests.cpp
    src/Game/Components/SelectableComponentTests.cpp
    src/Game/Components/SignalComponentTests.cpp
    src/Game/Components/InteractionAreaComponentTests.cpp
    # src/Game/Components/ExpansionMarkerComponentTests.cpp
    # Gameplay classes
    src/RendererTests.cpp
    src/Game/TileTests.cpp
    src/Game/LotTests.cpp
    src/Game/LotDequeTests.cpp
    src/Game/PlotTests.cpp
    # src/Game/ExpansionMarkerTests.cpp
    # Gameplay systems
    src/Game/Systems/PlayfieldSystemTests.cpp
)
