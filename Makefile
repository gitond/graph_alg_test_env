# configuration
CC = g++			# the compiler
#CFLAGS				# compiler flags here
MAINEX = tb			# main executable outputted by compiler
CPEXEC = cptest			# command parsing test executable
# main program depandancies
MAINDEP = app/main.cpp app/modules/main/command_parser.cpp app/modules/main/commands.cpp app/modules/main/module_loader.cpp
# additional dependencies for testing
TESTDEP = tests/command_parsing.cpp

# making
all: $(MAINDEP) $(TESTDEP)
	# program
	$(CC) -c app/main.cpp
	$(CC) -c app/modules/main/command_parser.cpp
	$(CC) -c app/modules/main/commands.cpp
	$(CC) -c app/modules/main/module_loader.cpp
	$(CC) main.o command_parser.o commands.o module_loader.o
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
	$(RM) module_loader.o

newesttestbuild: $(MAINDEP)
	# program
	$(CC) -c app/main.cpp
	$(CC) -c app/modules/main/command_parser.cpp
	$(CC) -c app/modules/main/commands.cpp
	$(CC) -c app/modules/main/module_loader.cpp
	$(CC) main.o command_parser.o commands.o module_loader.o
	mv a.out testbuilds/newest

	# cleanup
	$(RM) main.o
	$(RM) command_parser.o
	$(RM) commands.o
	$(RM) module_loader.o

test: $(CPEXEC)
	./$(CPEXEC)

clean:
	$(RM) $(MAINEX)
	$(RM) $(CPEXEC)
