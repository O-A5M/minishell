# Minishell

A simplified UNIX shell implementation built in C, developed as part of the 42 School curriculum.  
This project replicates essential features of a real shell like `bash`, including command parsing, execution, and environment variable handling.

## 🧠 Project Purpose

The goal of **minishell** is to deepen understanding of:
- Process creation & management
- File descriptors & redirections
- Signals
- Environment handling
- Command parsing and tokenization

## ⚙️ Features

- Built-in commands: `cd`, `echo`, `env`, `exit`, `export`, `pwd`, `unset`
- Pipes (`|`) to connect commands
- Redirections: `>`, `>>`, `<`, `<<` (heredoc)
- Environment variables expansion (`$VAR`)
- Quoting (single `'` and double `"`)
- Signal handling (Ctrl+C, Ctrl+D, Ctrl+\\)
- Error messages and return codes
- Command execution from system path (`PATH`)

## 📦 Installation

Clone the repository and compile:

```bash
git clone https://github.com/your-username/minishell.git
cd minishell
make
