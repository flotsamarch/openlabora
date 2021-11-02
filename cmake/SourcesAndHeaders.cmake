set(sources
    src/Renderer.cpp
    src/state/StateMachine.cpp
    src/state/gs/GSMainMenu.cpp
    src/state/ui/UISMainMenu.cpp
    src/Application.cpp
)

set(exe_sources
        src/main.cpp
        ${sources}
)

set(headers
    include/Renderer.hpp
    include/state/StateMachine.hpp
    include/state/BaseState.hpp
    include/state/gs/GameState.hpp
    include/state/gs/GSMainMenu.hpp
    include/state/gs/GSFinal.hpp
    include/state/gs/GSTest.hpp
    include/state/ui/UiState.hpp
    include/state/ui/UISMainMenu.hpp
    include/state/ui/UISFinal.hpp
    include/state/ui/UISTest.hpp
    include/Application.hpp
)

set(test_sources
  src/StateMachineTests.cpp
)
