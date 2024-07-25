.PHONY: build run clean test setup_win setup_linux

build:
	@gcc main.c -Wall -o ./target/main

run: build
	@./target/main $(filter-out $@,$(MAKECMDGOALS))

test: 
	@gcc tests/parser.c -Wall -g -o ./target/parser
	@./target/parser

setup_linux:
	@mkdir -p target

# doesn't work :(
#setup_win:
#	@New-Item -ItemType d target

%:
    @:
