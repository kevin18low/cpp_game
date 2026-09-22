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

_Build instructions will be added along with the build system._

## Contributing

- `main` is always buildable; all work goes through pull requests.
- Branch names: `feat/…`, `fix/…`, `build/…`, `ci/…`, `docs/…`, `chore/…`.
- Commit messages follow [Conventional Commits](https://www.conventionalcommits.org/),
  e.g. `feat: render player sprite`.
- Format C++ with `clang-format` (config in `.clang-format`) before committing.
