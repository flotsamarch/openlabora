set(sources
    src/Renderer.cpp
    src/game/Plot.cpp
    src/game/LandPurchaseMarker.cpp
    src/game/Playfield.cpp
    src/game/Location.cpp
    src/state/State.cpp
    src/state/gs/GameState.cpp
    src/state/ui/UiState.cpp
    src/state/ui/UISCommon.cpp
    src/state/gs/GSMainMenu.cpp
    src/state/ui/UISMainMenu.cpp
    src/state/gs/GSCommon.cpp
    src/state/gs/GSDuel.cpp
    src/state/ui/UISDuel.cpp
    src/Application.cpp
)

set(exe_sources
        src/main.cpp
        ${sources}
)

set(headers
    include/game/ISelectable.hpp
    include/game/IEntity.hpp
    include/game/Entity.hpp
    include/game/Plot.hpp
    include/game/Tile.hpp
    include/game/SelectableEntity.hpp
    include/game/LandPurchaseMarker.hpp
    include/game/Playfield.hpp
    include/game/Location.hpp
    include/resource/ResourceManager.hpp
    include/resource/IResourceManager.hpp
    include/IRenderer.hpp
    include/Renderer.hpp
    include/state/State.hpp
    include/state/AppStateDefs.hpp
    include/state/gs/IGameState.hpp
    include/state/gs/GameState.hpp
    include/state/gs/GSMainMenu.hpp
    include/state/gs/GSFinal.hpp
    include/state/gs/GSCommon.hpp
    include/state/gs/GSDuel.hpp
    include/state/ui/IUiState.hpp
    include/state/ui/UiState.hpp
    include/state/ui/UISCommon.hpp
    include/state/ui/UISMainMenu.hpp
    include/state/ui/UISFinal.hpp
    include/state/ui/UISDuel.hpp
    include/IApplication.hpp
    include/Application.hpp
)

set(test_sources
  src/ApplicationTests.cpp
  src/LocationTests.cpp
  src/PlayfieldTests.cpp
)
