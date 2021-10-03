set(sources
    src/application.cpp
    src/state/State.cpp
    src/state/TestState.cpp
)

set(exe_sources
        src/main.cpp
        ${sources}
)

set(headers
    include/application.hpp
    include/state/GameState.hpp
    include/state/State.hpp
    include/state/StateFinal.hpp
    include/state/TestState.hpp
)

set(test_sources
  src/tmp_test.cpp
)
