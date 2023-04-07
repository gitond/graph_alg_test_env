# configuration
CC = g++			# the compiler
#CFLAGS				# compiler flags here

# files to be fed to compiler
GPPINP = app/main.cpp app/modules/main/command_parser.cpp

MAINEX = tb			# main executable outputted by compiler

# command parsing test source
CPTEST = tests/command_parsing.cpp app/modules/main/command_parser.cpp

CPEXEC = cptest			# command parsing test executable

# making
all: $(GPPINP) $(DUMTST)
	$(CC) -o $(MAINEX) $(GPPINP)
	$(CC) -o $(CPEXEC) $(CPTEST)

test: $(CPEXEC)
	./$(CPEXEC)

clean:
	$(RM) $(MAINEX)
	$(RM) $(CPEXEC)
