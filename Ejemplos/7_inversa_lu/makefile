# Makefile

# Compiler flags: all warnings + debugger meta-data
CFLAGS = -Wall -g

# External libraries: only math in this example
LIBS = -lm

# Pre-defined macros for conditional compilation
DEFS = -DDEBUG_FLAG -DEXPERIMENTAL=0

# The final executable program file, i.e. name of our program
BIN = 7-Inversa_lu

# Object files from which $BIN depends
RUTA= ../..
OBJS= ${RUTA}/matrix.o \
	${RUTA}/operacion_matriz.o\
	${RUTA}/solve.o\
	${RUTA}/EcuacionesL_Metodos.o
# This default rule compiles the executable program
$(BIN): $(OBJS) $(BIN).c
	$(CC) $(CFLAGS) $(DEFS) $(LIBS) $(OBJS) $(BIN).c -o $(BIN)

# This rule compiles each module into its object file
%.o: %.c %.h
	$(CC) -c $(CFLAGS) $(DEFS) $< -o $@

clean:
	rm -f *~ *.o $(BIN)
	rm -f ../../*.o

depend:
	makedepend -Y -- $(CFLAGS) $(DEFS) -- *.c
run:
	./$(BIN) $(f1)

valgrind:
	valgrind --tool=memcheck --leak-check=yes ./$(BIN) ${f1}
