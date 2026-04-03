*This project has been created as part of the 42 curriculum by ssivilay, tdelmas2.*

## Description

Minishell is a simplified Unix shell written in C. It replicates core features of bash, including command execution, pipes, redirections, environment variable expansion, and built-in commands. The project covers process management with `fork`/`execve`, file descriptor manipulation, signal handling, and lexical analysis/parsing of user input.

### Features

- **Built-in commands:** `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- **Pipes** (`|`) to chain commands
- **Redirections:** input (`<`), output (`>`), append (`>>`), here-document (`<<`)
- **Environment variable expansion** (`$VAR`, `$?`)
- **Quote handling:** single quotes (literal) and double quotes (with expansion)
- **Signal handling:** `Ctrl+C`, `Ctrl+\`, `Ctrl+D`
- **Command history** via readline

## Instructions

### Build & Run

```bash
make        # Build the project
./minishell # Launch the shell
```

### Other make rules

| Command      | Description                              |
|--------------|------------------------------------------|
| `make clean` | Remove object files                      |
| `make fclean`| Remove object files and the executable   |
| `make re`    | Full rebuild                             |
| `make val`   | Run with valgrind (memory leak checking) |

## Resources

My peers for explaning the concept and their punctual advice when needed

Use of AI :
- To better understand the subject and the Shell concepts
- To receive general advice on the code structure
- To help identify logical errors, edge cases or misunderstandings in the behavior of the algorithm
- To assist in writing this README file and correct English