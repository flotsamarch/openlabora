set(sources
    # Components
    # src/Game/Components/PlayfieldComponent.cpp
    # Gameplay classes
    # src/Game/Tile.cpp
    # src/Game/Plot.cpp
    # src/Game/Playfield.cpp
    # src/Game/ExpansionMarker.cpp
    # src/Game/MarkerController.cpp
    # src/Game/Location.cpp
    # Game states
    src/GameState/Final.cpp
    src/GameState/MainMenu.cpp
    src/GameState/Duel.cpp
    # src/GameState/Views/GVDuel.cpp
    # src/GameState/Controllers/GCDuel.cpp
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
    # include/Game/Components/ImmobileComponent.hpp
    # include/Game/Components/PositionComponent.hpp
    # include/Game/Components/TextureContainerComponent.hpp
    # include/Game/Components/SpriteComponent.hpp
    # include/Game/Components/PlayfieldComponent.hpp
    # include/Game/Components/PlotComponent.hpp
    # include/Game/Components/EffectiveInteractionAreaComponent.hpp
    # include/Game/Components/SelectableComponent.hpp
    # include/Game/Components/SignalComponent.hpp
    # include/Game/Components/ExpansionMarkerComponent.hpp
    # Gameplay classes
    # include/Game/Tile.hpp
    # include/Game/Plot.hpp
    # include/Game/Playfield.hpp
    # include/Game/Signal.hpp
    # include/Game/ExpansionMarker.hpp
    # include/Game/MarkerController.hpp
    # include/Game/Location.hpp
    # Game states
    include/GameState/Views/ViewConcept.hpp
    include/GameState/ViewToViewModelBinding.hpp
    include/GameState/Views/EscapeMenuView.hpp
    include/GameState/ViewModels/EscapeMenuViewModel.hpp
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
    # Game Views
    src/GameState/Views/CameraViewTests.cpp
    src/GameState/Views/EscapeMenuViewTests.cpp
    # Game states
    src/GameState/FinalStateTests.cpp
    src/GameState/MainMenuTests.cpp
    src/GameState/DuelTests.cpp
    # Components
    # src/Game/Components/PlotComponentTests.cpp
    # src/Game/Components/PlayfieldComponentTests.cpp
    # src/Game/Components/EffectiveInteractionAreaComponentTests.cpp
    # src/Game/Components/SelectableComponentTests.cpp
    # src/Game/Components/SignalComponentTests.cpp
    # src/Game/Components/ExpansionMarkerComponentTests.cpp
    # Gameplay classes
    src/RendererTests.cpp
    # src/Game/TileTests.cpp
    # src/Game/PlotTests.cpp
    # src/Game/PlayfieldTests.cpp
    # src/Game/ExpansionMarkerTests.cpp
)
