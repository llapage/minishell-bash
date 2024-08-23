Overview

This project is a simplified shell, similar to bash, implemented in C for macOS and linux with "make linux" thanks to the makefile. The shell provides basic command execution and supports a variety of built-in commands, input/output redirection, and pipe handling.

Features

Basic Command Execution: Execute common commands like ls, echo, pwd, etc.
Built-in Commands: Supports cd, export, unset, env, exit, and echo.
Piping: Allows chaining of commands with pipes (e.g., ls | grep shell).
Redirections:
Input Redirection: Supports < to read input from files.
Output Redirection: Supports > and >> for overwriting or appending to files.
Signal Handling: Handles CTRL+C, CTRL+D, and CTRL+\\ similar to bash.
Environment Variables: Manage environment variables with export and unset.
Exit Status: The shell returns the exit status of the last executed command.
Wildcards.
