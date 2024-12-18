# Coto - Abstract Additive Quantum Decision Diagrams

[![GitHub](https://img.shields.io/badge/GitHub-%23121011.svg?logo=github&logoColor=white)](#)
[![GitHub Actions](https://img.shields.io/badge/GitHub_Actions-2088FF?logo=github-actions&logoColor=white)](#)
[![Build Status (GitHub Actions)](https://github.com/Firefnix/coto/workflows/CMake%20Tests/badge.svg)](https://github.com/Firefnix/coto/actions?query=workflow%3A"CMake%20Tests")
[![C++](https://img.shields.io/badge/C++-%2300599C.svg?logo=c%2B%2B&logoColor=white)](#)
<a href="https://gitmoji.dev">
  <img
    src="https://img.shields.io/badge/gitmoji-%20😜%20😍-FFDD67.svg?style=flat-square"
    alt="Gitmoji"
  />
</a>

Theoretical research, experiments and implementation of _abstract additive quantum decision diagrams_, as part of a student research project.

## Repository architecture

Presentation of this repository's main directories:
-  `.github/workflows` GitHub actions continuous integration (CI) configuration files. Runs the unit tests that are in the `test` directory and marked as ready for testing in `CMakeLists.txt`
-  `archives` Legacy documents or code, that still should be indexed
-  `doc` Theory documents (basically, LaTeX)
-  `include` Code header files (`.h` C++ files)
-  `presentation` Final presentation (in French for now, an English version will be available afterwards)
-  `ref` References, code or case studies that can be used as examples
-  `report` Final report (in French for now, an English version will be available afterwards)
-  `src` Source code (`.cpp` C++ files, not headers)
-  `test` Test code (`.cpp` C++ files)
