# configuration
CC = g++			# the compiler
#CFLAGS				# compiler flags here
GPPINP = app/main.cpp		# file to be fed to compiler
MAINEX = testbuilds/tb		# main executable outputted by compiler
DUMTST = tests/dummy.cpp	# dummytest source
DTSTEX = testbuilds/dummytest	# dummytest executable

# making
all: $(GPPINP) $(DUMTST)
	$(CC) $(GPPINP) -o $(MAINEX)	# compile main program
	chmod +x $(MAINEX)		# make main program executable
	$(CC) $(DUMTST) -o $(DTSTEX)	# compile dummy test

test: $(DTSTEX)
	./$(DTSTEX)

clean:
	$(RM) $(MAINEX)
	$(RM) $(DTSTEX)
