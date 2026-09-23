# cpp_game

A 2D game written in modern C++ with [SDL3](https://libsdl.org), built lesson by lesson
following [Lazy Foo' Productions' SDL3 tutorials](https://lazyfoo.net/tutorials/SDL3/).

> Status: early development. The actual game is still to be decided.

## Tech stack

| Area        | Choice                    |
|-------------|---------------------------|
| Language    | C++20                     |
| Media       | SDL3                      |
| Build       | CMake + Ninja             |
| Compiler    | GCC (MSYS2 UCRT64)        |
| CI          | GitHub Actions            |

## Building

### Prerequisites

- A C++20 compiler (developed with GCC from [MSYS2](https://www.msys2.org) UCRT64)
- CMake 3.25+
- Ninja

SDL3 is downloaded and built automatically by CMake on first configure. No manual install is needed.

### Build and run

```bash
cmake --preset debug          # configure (first run fetches SDL3)
cmake --build --preset debug  # compile
./build/debug/game.exe        # run
```

Use the `release` preset for an optimized build.

In VS Code, install the **C/C++** and **CMake Tools** extensions; the
workspace settings make CMake Tools use these same presets.

## Contributing

- `main` is always buildable; all work goes through pull requests.
- Branch names: `feat/…`, `fix/…`, `build/…`, `ci/…`, `docs/…`, `chore/…`.
  e.g. `feat: render player sprite`.
- Format C++ with `clang-format` (config in `.clang-format`) before committing.
