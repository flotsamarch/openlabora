set(sources
    # Components
    src/Game/Components/PlayfieldComponent.cpp
    # Gameplay classes
    src/Game/Tile.cpp
    src/Game/Plot.cpp
    src/Game/Playfield.cpp
    # src/Game/ExpansionMarker.cpp
    # src/Game/MarkerManager.cpp
    # src/Game/Location.cpp
    # Game states
    src/GameState/Views/GameView.cpp
    src/GameState/Views/GVMainMenu.cpp
    src/GameState/Views/GVDuel.cpp
    src/GameState/Controllers/GameController.cpp
    src/GameState/Controllers/GCMainMenu.cpp
    src/GameState/Controllers/GCDuel.cpp
    # GUI
    # src/GUI/ExpansionWindow.cpp
    # Game systems
    src/Resource/ResourceManager.cpp
)

set(exe_sources
        src/main.cpp
        ${sources}
)

set(headers
    # Components
    include/Game/Components/ImmobileComponent.hpp
    include/Game/Components/PositionComponent.hpp
    include/Game/Components/TextureContainerComponent.hpp
    include/Game/Components/SpriteComponent.hpp
    include/Game/Components/PlayfieldComponent.hpp
    include/Game/Components/PlotComponent.hpp
    # Gameplay classes
    include/Game/Tile.hpp
    include/Game/Plot.hpp
    include/Game/Playfield.hpp
    # include/Game/Selectable.hpp
    # include/Game/IEntity.hpp
    # include/Game/Entity.hpp
    # include/Game/SelectableEntity.hpp
    # include/Game/ExpansionMarker.hpp
    # include/Game/MarkerManager.hpp
    # include/Game/Location.hpp
    # Game states
    include/GameState/Model/Common.hpp
    include/GameState/Model/Model.hpp
    include/GameState/Model/NoModel.hpp
    include/GameState/Views/GameView.hpp
    include/GameState/Views/GVFinal.hpp
    include/GameState/Views/GVMainMenu.hpp
    include/GameState/Views/GVDuel.hpp
    include/GameState/Controllers/GameController.hpp
    include/GameState/Controllers/GCFinal.hpp
    include/GameState/Controllers/GCMainMenu.hpp
    include/GameState/Controllers/GCDuel.hpp
    # GUI
    # include/GUI/ClickableArea.hpp
    # include/GUI/ExpansionWindow.hpp
    # Misc
    include/Misc/RangeWrapper.hpp
    include/Misc/PtrView.hpp
    include/Misc/EnumMap.hpp
    include/Misc/UID.hpp
    # Game systems
    include/ECS/ComponentContainer.hpp
    include/ECS/Entity.hpp
    include/AppState/AppState.hpp
    include/AppState/AppStateDefs.hpp
    include/AppState/StateIds.hpp
    include/AppState/Transitions.hpp
    include/Resource/ResourceManager.hpp
    include/Resource/IResourceManager.hpp
    include/GameWindow.hpp
    include/Renderer.hpp
    include/IApplication.hpp
    include/Application.hpp
)

set(test_sources
    # src/ApplicationTests.cpp
    src/RendererTests.cpp
    src/Misc/PtrViewTests.cpp
    src/Game/TileTests.cpp
    # src/Game/PlotTests.cpp
)
