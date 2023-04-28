# configuration
CC = g++			# the compiler
MAINEX = tb			# main executable outputted by compiler
CPEXEC = cptest			# command parsing test executable
MLEXEC = mltest			# module loading test executable
# compiler flags here
CFLAGS = -lsfml-graphics -lsfml-window -lsfml-system
# main program depandancies
MAINDEP = app/main.cpp app/modules/main/command_parser.cpp app/modules/main/commands.cpp app/modules/main/module_loader.cpp app/modules/testmod/commands.cpp app/modules/graphs/commands.cpp app/modules/graphs/vertex.cpp app/modules/graphs/graph.cpp app/modules/graphs/rand_mat_gen.cpp
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
	$(CC) -c app/modules/graphs/graph.cpp
	$(CC) -c app/modules/graphs/rand_mat_gen.cpp
	$(CC) -c app/modules/main/module_loader.cpp
	$(CC) -c app/modules/graphs/visualisation.cpp
	$(CC) main.o command_parser.o maincomms.o tcomms.o commands.o module_loader.o vertex.o graph.o rand_mat_gen.o visualisation.o -o $(MAINEX) $(CFLAGS)

	# tests
	$(CC) -c tests/command_parsing.cpp
	$(CC) command_parsing.o command_parser.o maincomms.o tcomms.o commands.o module_loader.o vertex.o graph.o rand_mat_gen.o visualisation.o -o $(CPEXEC) -lsfml-graphics -lsfml-window -lsfml-system
	$(CC) -c tests/module_loading.cpp
	$(CC) module_loading.o command_parser.o maincomms.o tcomms.o commands.o module_loader.o vertex.o graph.o rand_mat_gen.o visualisation.o -o $(MLEXEC) -lsfml-graphics -lsfml-window -lsfml-system

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
	$(RM) graph.o
	$(RM) rand_mat_gen.o
	$(RM) visualisation.o

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
	$(CC) -c app/modules/graphs/graph.cpp
	$(CC) -c app/modules/graphs/rand_mat_gen.cpp
	$(CC) -c app/modules/main/module_loader.cpp
	$(CC) -c app/modules/graphs/visualisation.cpp
	$(CC) -c app/modules/graphs/graph_file_operations.cpp
	$(CC) main.o command_parser.o maincomms.o tcomms.o commands.o module_loader.o vertex.o graph.o rand_mat_gen.o visualisation.o graph_file_operations.o -o testbuilds/newest $(CFLAGS)

	# cleanup
	$(RM) main.o
	$(RM) command_parser.o
	$(RM) maincomms.o
	$(RM) tcomms.o
	$(RM) commands.o
	$(RM) module_loader.o
	$(RM) vertex.o
	$(RM) graph.o
	$(RM) rand_mat_gen.o
	$(RM) visualisation.o
	$(RM) graph_file_operations.o

gv: app/modules/graphs/graph.cpp app/modules/graphs/vertex.cpp app/modules/graphs/rand_mat_gen.cpp
	$(CC) -c app/modules/graphs/graph.cpp
	$(CC) -c app/modules/graphs/vertex.cpp
	$(CC) -c app/modules/graphs/rand_mat_gen.cpp
	$(CC) graph.o vertex.o rand_mat_gen.o
	mv a.out testbuilds/graph
	$(RM) graph.o
	$(RM) vertex.o
	$(RM) rand_mat_gen.o

graphics: app/modules/graphs/visualisation.cpp
	$(CC) -c app/modules/graphs/visualisation.cpp
	$(CC) -c app/modules/graphs/graph.cpp
	$(CC) -c app/modules/graphs/vertex.cpp
	$(CC) visualisation.o graph.o vertex.o -o graphics -lsfml-graphics -lsfml-window -lsfml-system
	$(RM) visualisation.o
	$(RM) graph.o
	$(RM) vertex.o

gfo: app/modules/graphs/graph_file_operations.cpp
	$(CC) -c app/modules/graphs/graph_file_operations.cpp
	$(CC) -c app/modules/graphs/graph.cpp
	$(CC) -c app/modules/graphs/vertex.cpp
	$(CC) graph_file_operations.o graph.o vertex.o -o testbuilds/gfo
	$(RM) graph_file_operations.o
	$(RM) graph.o
	$(RM) vertex.o

test: $(CPEXEC)
	./$(CPEXEC)
	./$(MLEXEC)

clean:
	$(RM) $(MAINEX)
	$(RM) $(CPEXEC)
	$(RM) $(MLEXEC)
