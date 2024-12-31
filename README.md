
# Minishell

## Overview

Minishell is a simple UNIX shell that mimics the behavior of the standard shell (sh) with basic features, including command execution, environment variable handling, and built-in commands. This project aims to provide a deeper understanding of how a shell works by implementing core functionalities from scratch.

## Features

- Command execution
- Built-in commands (`cd`, `echo`, `exit`, etc.)
- Environment variable handling
- Process management (forking, executing commands, handling pipes)
- Support for input/output redirection
- Error handling for invalid commands and syntax

## Requirements

- C programming language
- POSIX-compliant operating system (Linux, macOS, etc.)
- GCC or Clang compiler

## Installation

To compile and run the minishell, follow these steps:

1. Clone the repository:
   ```bash
   git clone https://github.com/mkatfi/minishell.git
   ```

2. Navigate into the project directory:
   ```bash
   cd minishell
   ```

3. Compile the project using `make`:
   ```bash
   make
   ```

4. Run the shell:
   ```bash
   ./minishell
   ```

## Usage

Once the shell is running, you can enter commands just like you would in a regular shell. Some basic commands include:

- `cd <directory>`: Change the current directory.
- `echo <text>`: Print text to the terminal.
- `exit`: Exit the minishell.

Example:
```bash
$ ./minishell
minishell> echo Hello, world!
Hello, world!
minishell> cd /path/to/directory
minishell> exit
```
