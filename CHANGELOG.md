# Changelog

## [3.0.0] Major Release 22nd February 2025
This release introduces API-breaking changes. Upgrading to ``v3.0.0`` is recommended.

- Added support for users to defined custom names for vertices and edges. 
- Optimized Storage, Replaced ``std::map`` with ``std::unordered_map`` in **GraphMatrix** and **MixedGraphMatrix**.
- Enhanced Vertex Management, ``addVertex`` in **GraphMatrix** and MixedGraphMatrix now supports variadic arguments for more flexible vertex creation.
- Cycle Detection, Introduced ``isCyclic()`` method in **GraphMatrix** to check for cycles in the graph.
- Custom Hashing Support, Added template specializations for hashing custom vertices and edges, ensuring better compatibility with ``std::unordered_map``.
- Improved Example Code, Fixed and updated all examples in the ``/examples`` folder to align with API changes.
- Expanded Test Suite: Added more test cases and enhanced Appledore's test framework for better tests coverage.
- Linting on all files using ``clang-format``.

## [2.1.0] - Released: 24th January 2025
### Minor Release
- Fixed ``removeVertex`` method in ``MixedGraph.h``
- Added comprehensive test suite with each defined unit tests for ``GraphMatrix.hpp`` 

## [2.0.0] - Released: 19th January 2025
### Major Release
- Added CMakeLists.txt for automated compiling of examples.
- Changed file structure moved from ``.h`` to ``.hpp`` for header files extension
- Added ``GraphEdge`` to inherit custom vertex types such as ``class`` and ``struct`` to inherit from. Provides pre built overloads for ``std::map`` comparison
- Fixed duplicated instances of tag structures in ``GraphMatrix.h``
- Improved File structure
- Added ``MatrixRepresentation`` class in ``MatrixRep.hpp``. The ``MatrixRepresentation`` class serves as a parent for both ``GraphMatrix`` and ``MixedGraphMatrix`` classes to share common resouces.


## [1.0.0] - Released: 28th December 2024
- Minor feature updates
- Added versioning
