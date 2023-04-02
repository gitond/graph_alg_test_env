# configuration
CC = g++		# the compiler
#CFLAGS			# compiler flags here
GPPINP = app/main.cpp	# file to be fed to compiler
GPPOUT = testbuilds/tb	# executable outputted by compiler

# making
all: $(GPPINP)
	$(CC) $(GPPINP) -o $(GPPOUT)

clean:
	$(RM) $(GPPOUT)
