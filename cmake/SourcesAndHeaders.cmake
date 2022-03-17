set(sources
    # Gameplay classes
    src/Game/Plot.cpp
    src/Game/ExpansionMarker.cpp
    src/Game/MarkerManager.cpp
    src/Game/Playfield.cpp
    src/Game/Location.cpp
    # Game states
    src/GameState/Views/GameView.cpp
    src/GameState/Views/GVMainMenu.cpp
    src/GameState/Views/GVDuel.cpp
    src/GameState/Controllers/GameController.cpp
    src/GameState/Controllers/GCMainMenu.cpp
    src/GameState/Controllers/GCDuel.cpp
    # GUI
    # src/GUI/ExpansionWindow.cpp
)

set(exe_sources
        src/main.cpp
        ${sources}
)

set(headers
    # Gameplay classes
    include/Game/Selectable.hpp
    include/Game/IEntity.hpp
    include/Game/Entity.hpp
    include/Game/Plot.hpp
    include/Game/Tile.hpp
    include/Game/SelectableEntity.hpp
    include/Game/ExpansionMarker.hpp
    include/Game/MarkerManager.hpp
    include/Game/Playfield.hpp
    include/Game/Location.hpp
    # Game states
    include/GameState/Model.hpp
    include/GameState/Views/GameView.hpp
    include/GameState/Views/GVFinal.hpp
    include/GameState/Views/GVMainMenu.hpp
    include/GameState/Views/GVDuel.hpp
    include/GameState/Controllers/GameController.hpp
    include/GameState/Controllers/GCFinal.hpp
    include/GameState/Controllers/GCMainMenu.hpp
    include/GameState/Controllers/GCDuel.hpp
    # GUI
    # include/GUI/Utility.hpp
    include/GUI/ClickableArea.hpp
    # include/GUI/ExpansionWindow.hpp
    # Game systems
    include/Misc/PtrView.hpp
    include/AppState/AppState.hpp
    include/AppState/StateIds.hpp
    include/AppState/Transitions.hpp
    include/resource/ResourceManager.hpp
    include/resource/IResourceManager.hpp
    include/Renderer.hpp
    include/IApplication.hpp
    include/Application.hpp
)

set(test_sources
  src/ApplicationTests.cpp
  src/LocationTests.cpp
  src/PlayfieldTests.cpp
)
