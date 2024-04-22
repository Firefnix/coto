# Coto - Abstract Additive Quantum Decision Diagrams

[![Build Status (GitHub Actions)](https://github.com/Firefnix/coto/workflows/CMake%20Tests/badge.svg)](https://github.com/Firefnix/coto/actions?query=workflow%3A"CMake%20Tests")
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
-  `ref` References, code or case studies that can be used as examples
-  `src` Source code (`.cpp` C++ files, not headers)
-  `test` Test code (`.cpp` C++ files)