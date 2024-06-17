#!/bin/bash

# Count the number of lines in a file
git ls-files | cat Makefile include/*.h libft/*.c src/main.c src/builtins/*.c src/executor/*.c src/lexer/*.c src/parser/*.c src/utils/*.c | wc -l