# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/)
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

---

## [Unreleased]

### Added
- Support for basic tensor operations (addition, multiplication, indexing).
- Device abstraction for CPU (future GPU support planned).
- Engine for executing tensor operations efficiently.
- Version tracking for library.
- Unit tests and smoke tests for tensor functionality.

### Changed
- N/A

### Fixed
- N/A

---

## [0.1.0] - 2026-03-13

### Added
- Initial release of Vix AI Tensor library.
- Core classes:
  - `Tensor` for multi-dimensional arrays.
  - `Device` to manage CPU computation context.
  - `Engine` for executing operations on tensors.
- Library CMake build with:
  - Build tests option
  - Warnings configuration
  - Installation support
- Export targets for `find_package()` integration.
- Example smoke test (`tests/smoke.cpp`) to verify basic functionality.

### Changed
- N/A

### Fixed
- N/A
