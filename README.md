# Minishell

Welcome to Minishell! This project focuses on creating a simple shell program capable of executing commands, handling environment variables, and managing input/output redirection. By implementing this project, you'll deepen your understanding of Unix systems, process management, and command-line interfaces.

## Table of Contents

1. [Introduction](#introduction)
2. [Usage](#usage)
3. [Features](#features)
4. [Building](#building)
5. [Contributing](#contributing)
6. [Credits](#credits)

## Introduction

Minishell is a simplified version of a Unix shell, capable of interpreting and executing user commands. It provides a command-line interface for interacting with the operating system and running programs. Minishell supports various features such as command execution, environment variable handling, input/output redirection, and simple built-in commands.

## Usage

To use Minishell, follow these steps:

1. Clone the repository:

    ```bash
    git clone https://github.com/yourusername/minishell.git
    ```

2. Build the program:

    ```bash
    make
    ```

3. Run Minishell:

    ```bash
    ./minishell
    ```

4. Enter commands at the prompt and press Enter to execute them.

## Features

Minishell supports the following features:

- Execution of external commands
- Environment variable handling
- Input/output redirection (`<`, `>`, `>>`)
- Pipeline commands (`|`)
- Command history using arrow keys
- Basic built-in commands (e.g., `cd`, `echo`, `env`, `exit`)

## Building

To build Minishell, simply run:

```bash
make
```

## Contributing
Contributions are welcome! If you find any bugs or have suggestions for improvement, please open an issue or submit a pull request on GitHub.

## Credits
This project was created by adrgonza for the libft project at 42Madrid.
