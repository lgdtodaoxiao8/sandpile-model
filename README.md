# Sandpile Model (Abelian Sandpile)

A C++ command-line tool that simulates the [Abelian sandpile model](https://en.wikipedia.org/wiki/Abelian_sandpile_model)
and renders each state as a BMP image. The grid grows dynamically as the sand topples and
spreads, so the output size adapts to the simulation.

## What it does

- Reads an initial grid state from a TSV file (tab-separated values)
- Runs the sandpile toppling rule until the system stabilizes
- Dynamically resizes the grid as sand spreads beyond the original bounds
- Saves states as BMP images (final state, or every N iterations)

## Command-line arguments

| Flag | Long form   | Description                                   |
|------|-------------|-----------------------------------------------|
| `-i` | `--input`   | Input TSV file with the initial grid          |
| `-o` | `--output`  | Output directory for the generated BMP images |
| `-m` | `--max`     | Maximum number of iterations                  |
| `-f` | `--freq`    | Save an image every N iterations (0 = final only) |


## What this shows

- Working in C++ with files, dynamic 2D grids, and manual memory/layout control
- Implementing a real algorithm from a spec, not a tutorial
- Writing a binary file format (BMP) by hand
- Building a proper CLI with arguments

## Build & run

```bash
# with CMake
cmake -B build && cmake --build build
./build/sandpile --input start.tsv --output ./out --max 1000
```
