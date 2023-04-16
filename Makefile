# configuration
CC = g++			# the compiler
#CFLAGS				# compiler flags here
MAINEX = tb			# main executable outputted by compiler
CPEXEC = cptest			# command parsing test executable
MLEXEC = mltest			# module loading test executable
# main program depandancies
MAINDEP = app/main.cpp app/modules/main/command_parser.cpp app/modules/main/commands.cpp app/modules/main/module_loader.cpp app/modules/testmod/commands.cpp app/modules/graphs/commands.cpp app/modules/graphs/vertex.cpp
# additional dependencies for testing
TESTDEP = tests/command_parsing.cpp tests/module_loading.cpp

# making
all: $(MAINDEP) $(TESTDEP)
	# program
	$(CC) -c app/main.cpp
	$(CC) -c app/modules/main/command_parser.cpp
	$(CC) -c app/modules/main/commands.cpp
	mv commands.o maincomms.o
	$(CC) -c app/modules/testmod/commands.cpp
	mv commands.o tcomms.o
	$(CC) -c app/modules/graphs/commands.cpp
	$(CC) -c app/modules/graphs/vertex.cpp
	$(CC) -c app/modules/main/module_loader.cpp
	$(CC) main.o command_parser.o maincomms.o tcomms.o commands.o module_loader.o vertex.o
	mv a.out $(MAINEX)

	# tests
	$(CC) -c tests/command_parsing.cpp
	$(CC) command_parsing.o command_parser.o maincomms.o tcomms.o commands.o
	mv a.out $(CPEXEC)
	$(CC) -c tests/module_loading.cpp
	$(CC) module_loading.o module_loader.o command_parser.o maincomms.o tcomms.o commands.o
	mv a.out $(MLEXEC)

	# cleanup
	$(RM) main.o
	$(RM) command_parser.o
	$(RM) maincomms.o
	$(RM) tcomms.o
	$(RM) commands.o
	$(RM) command_parsing.o
	$(RM) module_loader.o
	$(RM) module_loading.o
	$(RM) vertex.o

newtest: $(MAINDEP)
	# program
	$(CC) -c app/main.cpp
	$(CC) -c app/modules/main/command_parser.cpp
	$(CC) -c app/modules/main/commands.cpp
	mv commands.o maincomms.o
	$(CC) -c app/modules/testmod/commands.cpp
	mv commands.o tcomms.o
	$(CC) -c app/modules/graphs/commands.cpp
	$(CC) -c app/modules/graphs/vertex.cpp
	$(CC) -c app/modules/main/module_loader.cpp
	$(CC) main.o command_parser.o maincomms.o tcomms.o commands.o module_loader.o vertex.o
	mv a.out testbuilds/newest

	# cleanup
	$(RM) main.o
	$(RM) command_parser.o
	$(RM) maincomms.o
	$(RM) tcomms.o
	$(RM) commands.o
	$(RM) module_loader.o
	$(RM) vertex.o

test: $(CPEXEC)
	./$(CPEXEC)
	./$(MLEXEC)

clean:
	$(RM) $(MAINEX)
	$(RM) $(CPEXEC)
	$(RM) $(MLEXEC)
