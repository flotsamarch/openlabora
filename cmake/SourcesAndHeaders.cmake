set(sources
    src/state/StateMachine.cpp
    src/state/gs/GSMainMenu.cpp
    src/Application.cpp
)

set(exe_sources
        src/main.cpp
        ${sources}
)

set(headers
    include/state/StateMachine.hpp
    include/state/gs/GameState.hpp
    include/state/gs/GSMainMenu.hpp
    include/state/gs/GSFinal.hpp
    include/state/gs/GSTest.hpp
    include/Application.hpp
)

set(test_sources
  src/StateMachineTests.cpp
)
