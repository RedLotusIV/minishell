#!/bin/bash

# Count the number of lines in a file
ls | cat src/main.c src/builtins/*.c src/executor/*.c src/lexer/*.c src/parser/*.c src/utils/*.c | wc -l