# configuration
CC = g++			# the compiler
#CFLAGS				# compiler flags here
MAINEX = tb			# main executable outputted by compiler
CPEXEC = cptest			# command parsing test executable

# making
all: $(GPPINP) $(DUMTST)
	# program
	$(CC) -c app/main.cpp
	$(CC) -c app/modules/main/command_parser.cpp
	$(CC) -c app/modules/main/commands.cpp
	$(CC) main.o command_parser.o commands.o
	mv a.out $(MAINEX)

	# tests
	$(CC) -c tests/command_parsing.cpp
	$(CC) command_parsing.o command_parser.o commands.o
	mv a.out $(CPEXEC)

	# cleanup
	$(RM) main.o
	$(RM) command_parser.o
	$(RM) commands.o
	$(RM) command_parsing.o

test: $(CPEXEC)
	./$(CPEXEC)

clean:
	$(RM) $(MAINEX)
	$(RM) $(CPEXEC)
