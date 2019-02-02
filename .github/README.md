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
* Selectable strength of computer opponent.
* Intelligent move search algorithms with efficient, modern C++.

A paragraph or two about project motivation and overall design.

## Requirements

* A Linux/UNIX system
* C++ 11
* CMake
* Git
* Boost Library

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

4. Run the program:

   ```shell
   $ ./cpp-dots-and-boxes
   ```

## Full Usage / Options

```
<cut and paste help menu here>
```

## Examples

* Run with some option:

   ```shell
   $ ./cpp-dots-and-boxes -d
   ```

* Run with some other option:

   ```shell
   $ ./cpp-dots-and-boxes -rt
   ```

## Design

A paragraph or two about architecture.

<img src="readme_assets/design_diagram.svg" width="100%" height="400" alt="Design Diagram">

## Source Code Layout

```
├─┬ cpp-dots-and-boxes/
│ ├─┬ src/
│ │ ├─┬ somea/
│ │ │ ├── Hello.cpp
│ │ │ └── Hello.hpp
│ │ ├─┬ someb/
│ │ │ ├── Goodbye.cpp
│ │ │ └── Goodbye.hpp
│ │ └── main.cpp
│ ├─┬ tests/
│ │ ├─┬ unit_tests/
│ │ │ └── Goodbye_test.cpp
│ │ └── doctest_testharness.cpp
│ ├─┬ third_party/
│ │ └─┬ doctest/
│ │   └── doctest.h
│ ├── .project_config
│ ├── .vimrc
│ ├── smart-build.sh
│ └── CMakeLists.txt
```

## Contributing

* Feel free to report a bug or propose a feature by opening a new
  [Issue](https://github.com/digimokan/cpp-dots-and-boxes/issues).
* Follow the project's [Contributing](CONTRIBUTING.md) guidelines.
* Respect the project's [Code Of Conduct](CODE_OF_CONDUCT.md).

