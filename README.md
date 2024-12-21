# FuzzyMatcher

A lightweight C++ fuzzy string matching library that provides fast and flexible fuzzy search functionality.

## Features

- Fuzzy string matching with scoring system
- Case-sensitive and case-insensitive matching support
- Special scoring for:
  - Consecutive character matches
  - First letter matches
  - Camel case boundaries
  - Extension starts
  - Directory separators
  - Word separators (space, underscore)
- Position tracking of matched characters
- Unicode support through wide strings

## Installation

Just include the FuzzyMatcher.h and FuzzyMatcher.cpp files in your project.

## Usage

```cpp
#include "FuzzyMatcher.h"

// Create a matcher with a search pattern
FuzzyMatcher matcher(L"ptr");

// Score a target string
std::vector<size_t> positions;
int score = matcher.ScoreMatch(L"MyPointer", &positions);

// positions will contain the indices of matched characters
// score will indicate how well the string matches the pattern
```

## Scoring System

The matching algorithm takes into account the following matching patterns:

- Basic character matches
- Case-sensitive matches
- First letter matches
- Consecutive character matches
- File extension boundaries (after '.')
- Directory separator matches (after '\')
- Word separator matches (after space or underscore)
- Camel case word boundaries

A higher score indicates a better match quality.

## Requirements

- C++17 or later
- Compiler with wide string support

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.
