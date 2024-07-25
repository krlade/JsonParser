.PHONY: build run clean test

build:
	@gcc main.c -Wall -o target/main

run: build
	@./target/main $(filter-out $@,$(MAKECMDGOALS))

test: 
	@gcc tests/parser.c -Wall -g -o target/parser
	@./target/parser

%:
    @:
