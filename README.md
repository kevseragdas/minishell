*This project has been created as part of the 42 curriculum by ztaskula, kagdas.*

# Minishell

## Description

Minishell is a simplified Bash-like shell developed as part of the 42 curriculum.  
The purpose of this project is to understand how a real Unix shell works internally by recreating its core functionalities from scratch in C.

This project focuses on:
- process management
- pipes
- redirections
- parsing
- environment variables
- signal handling
- file descriptor management

Instead of only using a shell, Minishell allows us to understand what actually happens behind the terminal when a command is executed.

For example:
- How does `ls` work?
- How are pipes connected?
- How does `$USER` expand?
- What happens after pressing `Ctrl-C`?
- How does heredoc work internally?

One of the biggest challenges was separating:
- **Built-in commands**
- **External commands**

Built-ins are executed directly inside the shell process, while external commands require:
- searching inside `PATH`
- creating child processes with `fork()`
- executing binaries using `execve()`

The project also includes:
- a lexer and parser system
- environment variable expansion
- heredoc support
- signal management
- history support using `readline`
- complete pipe and redirection handling

---

# Features

## Command Execution

### Built-in Commands
Implemented built-ins:
- `echo`
- `cd`
- `pwd`
- `export`
- `unset`
- `env`
- `exit`

### External Commands
Execution using:
- absolute paths
- relative paths
- environment `PATH`

---

## Interactive Prompt & History

- Interactive shell prompt
- Command history using `readline`
- Arrow-key navigation support

---

## Smart Expander

Supports:
- environment variable expansion (`$USER`)
- exit status expansion (`$?`)

Example:

```bash
echo $USER
echo $?
```

---

## Lexing & Parsing

The shell analyzes user input using a lexer/parser system.

Supports:
- tokenization
- syntax validation
- quote handling
- command structure generation

Quote handling:
- single quotes `'`
- double quotes `"`

---

## Redirections & Pipes

Supported redirections:

| Operator | Description |
|----------|-------------|
| `<` | Input redirection |
| `>` | Output redirection |
| `>>` | Append redirection |
| `<<` | Heredoc |

Pipe support:

```bash
ls -la | grep minishell | wc -l
```

---

## Signal Management

Bash-like signal behavior:

| Signal | Behavior |
|--------|----------|
| `Ctrl-C` | Displays new prompt |
| `Ctrl-D` | Exits shell |
| `Ctrl-\` | Ignored in interactive mode |

---

# Architecture

| Module | Directory | Responsibility |
|--------|-----------|----------------|
| Parser | `parse/` | Lexing, parsing, syntax checks |
| Executor | `execute/` | Pipes, execution, process management |
| Builtins | `builtin/` | Built-in commands |
| Libft | `libft/` | Helper functions |

---

# Team Contributions

## Zehra Taşkulak — `ztaskula`

Implemented:
- Built-in functions
- Execute system
- Pipe management
- Fork & process handling
- External command execution

---

## Kevser Ağdaş — `kagdas`

Implemented:
- Lexer
- Parser
- Heredoc system
- Redirections
- Signal handling

---

# Instructions

## Prerequisites

Requirements:
- Linux / macOS
- `cc`
- `make`
- Readline library

### Ubuntu / Debian

```bash
sudo apt-get install libreadline-dev
```

### macOS

```bash
brew install readline
```

---

# Compilation

Compile the project:

```bash
make
```

Other rules:

```bash
make clean
make fclean
make re
```

---

# Execution

Run Minishell:

```bash
./minishell
```

Prompt:

```bash
minishell$
```

---

# Example Usage

## Simple Command

```bash
minishell$ echo "Hello Minishell"
Hello Minishell
```

---

## Pipes

```bash
minishell$ ls -la | grep .c | wc -l
25
```

---

## Redirections

```bash
minishell$ echo "hello" > file.txt
minishell$ cat file.txt
hello
```

Append mode:

```bash
minishell$ echo "42" >> file.txt
```

---

## Environment Variables

```bash
minishell$ export NAME="minishell"
minishell$ echo $NAME
minishell
```

Unset variable:

```bash
minishell$ unset NAME
```

---

## Heredoc

```bash
minishell$ cat << EOF
> hello
> world
> EOF
hello
world
```

---

## Quotes

### Single Quotes

```bash
minishell$ echo '$USER'
$USER
```

### Double Quotes

```bash
minishell$ echo "$USER"
kagdas
```

---

## Exit Status

```bash
minishell$ ls /wrongpath
No such file or directory

minishell$ echo $?
1
```

---

# Internal Workflow

Command execution flow:

1. Input is read using `readline`
2. Lexer tokenizes input
3. Parser validates syntax
4. Variables are expanded
5. Redirections are prepared
6. Pipes are created
7. Child processes are forked
8. Commands execute using `execve`
9. Exit status is stored

---

# Memory Management

Special care was taken to avoid:
- memory leaks
- fd leaks
- zombie processes

Testing tools:
- `valgrind`
- manual stress tests
- multiple pipe/redirection tests

---

# Challenges

Most difficult parts of the project:
- multiple pipe management
- heredoc behavior
- signal handling
- quote parsing
- environment expansion
- fd leak prevention
- process synchronization
- parser design

---

# System Calls Used

Main functions used:

```c
fork
execve
pipe
dup
dup2
waitpid
signal
sigaction
open
close
read
write
```

---

# Resources

## Documentation

GNU Bash Manual  
https://www.gnu.org/software/bash/manual/

Linux Man Pages  
https://man7.org/linux/man-pages/

Readline Documentation  
https://tiswww.case.edu/php/chet/readline/rltop.html

---

## Tutorials & Articles

Build Your Own Shell  
https://github.com/tokenrove/build-your-own-shell

Write a Shell in C  
https://danishpraka.sh/posts/write-a-shell/

---

# AI Usage

AI tools were used for:
- researching shell architecture
- understanding process management
- analyzing signal behavior
- discussing parser logic
- generating test cases
- preparing documentation

No generated code was copied directly without understanding and rewriting it manually.

---

# Authors

## Zehra Taşkulak (`ztaskula`)
Executor Team

## Kevser Ağdaş (`kagdas`)
Parser Team

---

*Built at 42 Istanbul*