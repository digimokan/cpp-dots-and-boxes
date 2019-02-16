# cpp-dots-and-boxes

Linux/UNIX command-line dots and boxes game with intelligent AI, written in C++.

[![Release](https://img.shields.io/github/release/digimokan/cpp-dots-and-boxes.svg?label=release)](https://github.com/digimokan/cpp-dots-and-boxes/releases/latest "Latest Release Notes")
[![License](https://img.shields.io/badge/license-MIT-blue.svg?label=license)](LICENSE.txt "Project License")
[![Build Status](https://img.shields.io/travis/com/digimokan/cpp-dots-and-boxes/master.svg?label=linux+build)](https://travis-ci.com/digimokan/cpp-dots-and-boxes "Build And Test Results From Master Branch")

## Table Of Contents

* [Motivation](#motivation)
* [Features](#features)
* [Requirements](#requirements)
* [Quick Start](#quick-start)
* [Full Usage / Options](#full-usage--options)
* [Examples](#examples)
* [Design](#design)
* [Source Code Layout](#source-code-layout)
* [Contributing](#contributing)

## Motivation

Play on the command-line against the computer in a game of dots and boxes. Use
efficient underlying composable data structures. Allow for varying board sizes
and play options. Implement computer's move search with intelligent AI.

## Features

* Intuitive UI.
* Selectable AI search algorithms.
* Non-recursive minimax and alpha-beta search implementations.
* Custom search-depth specification.

## Requirements

* A Linux/UNIX system
* C++ 17
* CMake
* Git

## Quick Start

1. Clone project into a local project directory:

   ```shell
   $ git clone https://github.com/digimokan/cpp-dots-and-boxes.git
   ```

2. Change to the local project directory:

   ```shell
   $ cd cpp-dots-and-boxes
   ```

3. Build the program:

   ```shell
   $ ./third_party/smart-build/src/smart-build.sh --build-type-release
   ```

4. Play against the computer (with default settings):

   ```shell
   $ ./cpp-dots-and-boxes
   ```

5. Sample starting game-play input/output:

```
  A B C D E F G
A ·   ·   ·   ·
B
C ·   ·   ·   ·
D
E ·   ·   ·   ·
F
G ·   ·   ·   ·

Last Line Marked:         Player 1 Score: 0
Player To Act:      1     Player C Score: 0

Ent [ROW][COL] to mark, or # for box vals: #

  1  1  5
  1  4  5
  3  1  1

Ent [ROW][COL] to mark, or # for box vals: ed

  A B C D E F G
A · ― ·   ·   ·
B
C ·   ·   ·   ·
D
E ·   · ― ·   ·
F
G ·   ·   ·   ·

Last Line Marked:  AB     Player 1 Score: 0
Player To Act:      1     Player C Score: 0

Ent [ROW][COL] to mark, or # for box vals:
```

## Full Usage / Options

```
USAGE
  ./dots-and-boxes  -h
  ./dots-and-boxes  [-b <n>]  [-c|-r]  [-s <n>]  [-m|-a]
OPTIONS
  -h, --help
      print this help message
  -b <n>, --board-dimensions=<n>
      play on an n x n board (default 3 x 3)
  -c, --const-box-score
      use constant box scoring (each box is worth 1 point)
  -r, --random-box-score
      use random box scoring (each box is worth random 1-5 points)
  -s <n>, --max-search-depth=<n>
      have AI search n-moves-deep (default 2-moves-deep)
  -m, --minimax-search
      have AI search with minimax algorithm (default)
  -a, --alpha-beta-minimax-search
      have AI search with alpha-beta minimax algorithm
```

## Examples

* Play on a 5 x 5 board, using random box score values:

   ```shell
   $ ./cpp-dots-and-boxes -b 5 -r
   ```

* Play on a 4 x 4 board against an AI that uses the alpha-beta search algorithm:

   ```shell
   $ ./cpp-dots-and-boxes -b 4 -a
   ```

* Play against an AI that uses alpha-beta search to max search depth 5

   ```shell
   $ ./cpp-dots-and-boxes --max-search-depth=5 --alpha-beta-minimax-search
   ```

## Design

[Video Tour Of Program Architecture](https://youtu.be/MnQp4u84Ecc)

## Source Code Layout

```
├─┬ cpp-dots-and-boxes/
│ │
│ ├─┬ src/
│ │ ├── Board/            # dots-and-boxes board: marked lines, marked boxes
│ │ ├── CmdLineProcessor/ # process command-line options
│ │ ├── GameRunner/       # run a dots and boxes game
│ │ ├── MoveFinder/       # core minimax and alpha-beta algorithm logic
│ │ ├── Score/            # calc a player's score for a given board
│ │ ├── SearchNode/       # search tree node: has board, score, alpha/beta
│ │ ├── Utils/            # utility functions
│ │ └── main.cpp          # main program entry point
│ │
│ ├─┬ tests/
│ │ ├── unit_tests/             # unit test for each class and its methods
│ │ ├── doctest_testharness.cpp # configures the unit tester (doctest)
│ │ └── test_runner.sh          # one-line driver to smart-build the program
│ │
│ ├─┬ third_party/
│ │ ├── doctest/                # the unit-tester
│ │ └── smart-build             # the building/testing utility
│ │
│ ├── .project_config           # smart-build compilation/build config
│ └── CMakeLists.txt            # CMake build config
```

## Contributing

* Feel free to report a bug or propose a feature by opening a new
  [Issue](https://github.com/digimokan/cpp-dots-and-boxes/issues).
* Follow the project's [Contributing](CONTRIBUTING.md) guidelines.
* Respect the project's [Code Of Conduct](CODE_OF_CONDUCT.md).

