# minishell
A basic shell written in C

Minishell is a mini Unix shell implemented in C, designed to replicate core functionalities of the **/bin/bash shell**. This project was a crucial part of the 42 school curriculum, testing both technical and collaborative skills.

From handling user input to executing system commands, this shell covers:

- Custom Prompt built with the readline library.

- Command Parsing including:

    - **Tokenization** of input (respecting quotes and special characters).
    - Construction of an **execution tree** to manage operator precedence and nesting.

- Command Execution:

    - **Built-in command** handling (cd, echo, pwd, export, unset, env, exit).
    - **Execution of system binaries** found via the PATH variable.
    - Support for I/O **redirections** (<, >, <<, >>).
    - Full pipe (|) and **multi-pipe** chaining between commands.
    - **Expansion** of environment variables and special symbols like $?.


***Technical Challenges***

- Managing process creation and synchronization using **fork(), execve(), pipe(), and dup2()**.

- **Custom signal** handling for Ctrl+C, Ctrl+D, and Ctrl+\.

- Implementing a mini shell from scratch with careful memory management (**no leaks**).

- Respecting Bash-like behavior with edge cases and **proper error handling**.



***Human Experience***

This project wasn't just about coding a shell — it was also a **key moment in the curriculum** and a **first real teamwork** experience.

- First time working as a team on a **complex codebase**.

- Learning to divide responsibilities, **merge code**, and resolve Git conflicts.

- Making joint technical decisions, **communicating ideas clearly**, and developing shared conventions.

- Discovering the workflow with Git branches, pull requests, and **real project collaboration practices**.

***What I did here***

For this project, I was mainly responsible for the **execution logic, including the implementation of built-in commands and the full execution pipeline (handling redirections, pipes, and multiple processes)**. Looking back at my code today, I can clearly see **many things I would improve** — in terms of structure, optimization, and clarity.

It was also the first large-scale project of the 42 common core, and the first time working as a team on something this complex. In retrospect, I would definitely **organize the collaboration better**, especially regarding task division and Git workflow. But as they say, there's a first time for everything — and despite the challenges, I’m proud to say I survived what many call _“minihell”_, a turning point that tests **motivation, discipline, and teamwork.**

⚠️ NB: This project was developed and tested exclusively on macOS. Compatibility with Linux or other Unix systems is not guaranteed.
