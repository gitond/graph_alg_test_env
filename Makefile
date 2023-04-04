# configuration
CC = g++			# the compiler
#CFLAGS				# compiler flags here
GPPINP = app/main.cpp		# file to be fed to compiler
MAINEX = tb			# main executable outputted by compiler
DUMTST = tests/dummy.cpp	# dummytest source
DTSTEX = dummytest		# dummytest executable

# making
all: $(GPPINP) $(DUMTST)
	$(CC) $(GPPINP) -o $(MAINEX)
	$(CC) $(DUMTST) -o $(DTSTEX)

test: $(DTSTEX)
	chmod +x $(MAINEX)
	./$(DTSTEX)

clean:
	$(RM) $(MAINEX)
	$(RM) $(DTSTEX)
