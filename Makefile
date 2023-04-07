# configuration
CC = g++			# the compiler
#CFLAGS				# compiler flags here

# files to be fed to compiler
GPPINP = app/main.cpp app/modules/main/command_parser.cpp

MAINEX = tb			# main executable outputted by compiler
DUMTST = tests/dummy.cpp	# dummytest source
DTSTEX = dummytest		# dummytest executable

# making
all: $(GPPINP) $(DUMTST)
	$(CC) -o $(MAINEX) $(GPPINP)
	$(CC) $(DUMTST) -o $(DTSTEX)

test: $(DTSTEX)
	chmod +x $(MAINEX)
	./$(DTSTEX)

clean:
	$(RM) $(MAINEX)
	$(RM) $(DTSTEX)
