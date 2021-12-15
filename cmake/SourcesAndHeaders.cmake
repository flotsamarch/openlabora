set(sources
    src/game/Playfield.cpp
    src/game/Location.cpp
    src/state/State.cpp
    src/state/gs/GameState.cpp
    src/state/ui/UiState.cpp
    src/state/ui/UISEscapeMenu.cpp
    src/state/gs/GSMainMenu.cpp
    src/state/ui/UISMainMenu.cpp
    src/state/gs/GSDuelHotSeat.cpp
    src/state/ui/UISDuelHotSeat.cpp
    src/Application.cpp
)

set(exe_sources
        src/main.cpp
        ${sources}
)

set(headers
    include/game/Playfield.hpp
    include/game/Location.hpp
    include/game/PlayfieldInitArray.hpp
    include/resource/ResourceManager.hpp
    include/resource/IResourceManager.hpp
    include/IRenderer.hpp
    include/Renderer.hpp
    include/GUI/IDesktop.hpp
    include/GUI/Desktop.hpp
    include/state/State.hpp
    include/state/AppStateDefs.hpp
    include/state/ILogicState.hpp
    include/state/gs/IGameState.hpp
    include/state/gs/GameState.hpp
    include/state/gs/GSMainMenu.hpp
    include/state/gs/GSDuelHotSeat.hpp
    include/state/gs/GSFinal.hpp
    include/state/ui/IUiState.hpp
    include/state/ui/UiState.hpp
    include/state/ui/UISEscapeMenu.hpp
    include/state/ui/UISMainMenu.hpp
    include/state/ui/UISFinal.hpp
    include/state/ui/UISDuelHotSeat.hpp
    include/IApplication.hpp
    include/Application.hpp
)

set(test_sources
  src/ApplicationTests.cpp
  src/LocationTests.cpp
  src/PlayfieldTests.cpp
)
