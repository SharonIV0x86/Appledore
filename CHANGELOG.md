# Changelog
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
