# ArgParser

A lightweight C++ library for parsing command-line arguments

## Overview

ArgParser is a lightweight C++ library for parsing command-line arguments, designed to handle strings, integers, booleans, and custom types. It supports flexible argument configurations, including short and long names, default values, multi-value arguments, positional arguments, and flags. The library is built to pass the provided GoogleTest suite and includes additional functionality for robust command-line parsing.

## Features

- **Flexible Argument Parsing**: Supports string, integer, and boolean arguments with optional short names (e.g., -p) and long names (e.g., --param1).

- **Default and Required Arguments**: Configurable default values and mandatory arguments with validation.

- **Multi-Value Arguments**: Handles multiple values for a single argument with optional minimum count enforcement.

- **Positional Arguments**: Supports arguments without flags, parsed by position.

- **Flags**: Boolean flags with default values and storage options.

- **Help System**: Built-in --help/-h flag to display usage information.

- **Dynamic Parsing**: Allows re-parsing with conditional argument additions based on prior parse results.

- **Type-Safe Storage**: Stores parsed values directly into user-provided variables or retrieves them via getter methods.

- **Extensible**: Easily extended to support custom argument types.

The library provides a simple API for defining and parsing command-line arguments. Below is an example of how to use ArgParse

## Usage

The library provides a simple API for defining and parsing command-line arguments.

- Examples of usage via terminal:

```
./bin/ArgParser --help
./bin/ArgParser 1 2 3 4 --sum   
./bin/ArgParser 20 100 3 --mult  
./bin/ArgParser --sum 1 2 3 4
./bin/ArgParser -n 4 1 2 3 --sum
```

- Example of usage via main.cpp: 

```
#include <lib/ArgParser.h>
using namespace ArgumentParser;

int main(int argc, char* argv[]) {
    ArgParser parser("MyApp");
    std::string input;
    std::vector<int> numbers;
    bool flag = false;

    parser.AddStringArgument('i', "input", "Input file path").StoreValue(input);
    parser.AddIntArgument('n', "numbers", "List of numbers").MultiValue(1).Positional().StoreValues(numbers);
    parser.AddFlag('f', "flag", "Enable feature").StoreValue(flag);
    parser.AddHelp('h', "help", "Show usage");

    if (!parser.Parse(argv, argc)) {
        std::cout << "Parsing failed" << std::endl;
        return 1;
    }

    if (parser.Help()) {
        std::cout << parser.HelpDescription() << std::endl;
        return 0;
    }

    std::cout << "Input: " << input << ", Flag: " << flag << ", Numbers: ";
    for (int n : numbers) std::cout << n << " ";
    std::cout << std::endl;

    return 0;
}
```

## Supported functionality

The library meets all requirements from the provided GoogleTest suite, including:

| Feature                  | Description |
|--------------------------|-------------|
| String Arguments         | Parses strings with long (--param1=value) or short (-p=value) names. |
| Integer Arguments        | Parses integers (e.g., --param1=100500). |
| Boolean Flags            | Supports flags (e.g., --flag1 or -f) with default values and storage. |
| Default Values           | Returns default values if arguments are not provided. |
| Required Arguments       | Fails parsing if mandatory arguments are missing. |
| Multi-Value Arguments    | Parses multiple values for an argument with optional minimum count. |
| Positional Arguments     | Parses arguments by position without flags. |
| Combined Parsing         | Handles mixed positional and named arguments. |
| Repeated Parsing         | Supports re-parsing with dynamically added arguments based on prior results. |
| Help System              | Generates a help message with argument descriptions via --help or -h. |

## Implementation

- **Architecture**: Modular design with a single ArgParser class, extensible for additional types and functionality.

- **Testing**: Passes all provided GoogleTest cases and includes additional tests for edge cases and custom features.

- **Error Handling**: Validates argument presence, type correctness, and minimum value counts for multi-value arguments.

- **Extensibility**: Easily supports new argument types by extending the parser's internal storage and parsing logic.