# OpenLabora
OpenLabora is a C++20 open source digital adaptation of the [Ora et Labora](https://lookout-spiele.de/en/games/ora.html) boardgame by Uwe Rosenberg.

The game is developed by me as a portfolio project and mainly serves an educational purpose.

## Table of Contents
* [Table of Contents](#table-of-contents)
* [Build](#build)
  * [Dependencies](#dependencies)
  * [Requirements](#requirements)
  * [Build Guide](#build-guide)
    * [Windows and MSVC](#windows-and-msvc)
    * [Other](#other)
* [Tests](#tests)
* [Contributing](#contributing)
* [License](#license)

## Build
Currently I'm only building for x64 Windows with MSVC compiler. However no dependencies are Windows-specific and the code portability is always considered, so the project should build just fine on Linux / Mac or any other OS. If you encounter any problems with non-Windows platforms please create an issue.

### Dependencies
Dependencies are managed with CMake FetchContent module, so this section just provides information on what libraries must be available on the target platform and to give credit to the authors.
* [SFML](https://github.com/SFML/SFML) v.2.5.1
* [TGUI](https://github.com/texus/TGUI) v.0.9.5
* [Gtest](https://github.com/google/googletest) master

### Requirements
* Compiler with C++20 support
* [CMake](https://github.com/Kitware/CMake) v.3.24 or newer

### Build guide

#### Windows and MSVC
1. Download and install project dependencies. Ensure `[path to CMake]/bin` is in your `PATH` environment variable
2. Use cmd, PowerShell or any other terminal of your choice to clone the repository:
`git clone https://github.com/flotsamarch/openlabora` or download sources as zip
3. Enter project directory `cd openlabora`
3. Create build directory: `mkdir build/ && cd build`
4. Configure with `cmake ..`
5. Build: `cmake --build . -- /p:Configuration=[Debug or Release]` or just open `OpenLabora.sln` and build with Visual Studio
6. After successful build executable should be present in `build/bin/[Debug or Release]/`

#### Other platforms
Currently the dependency management only works for Windows. CMake should be able to find the installed dependencies via find_package module, but at the moment I cannot guarantee that the project builds. This problem is planned to be solved once I switch to using new GUI library.

## Tests
Even though unit testing is generally considered a bad practice in videogame industry I wanted my project to be done right in a classic software engineering way. To run tests execute the following command in the `build/` directory:
`ctest -C [Debug or Release] --test-dir .\test\`

## Contributing
This is a solo project and I would rather it stays that way. Aside from that any suggestions on improvement as well as bug reports are appreciated.

## License
<div>
    <a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License</a>.
</div>
