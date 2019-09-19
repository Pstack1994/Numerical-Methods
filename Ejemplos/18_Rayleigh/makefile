# Makefile

# Compiler flags: all warnings + debugger meta-data
CFLAGS = -Wall -g

# External libraries: only math in this example
LIBS = -lm

# Pre-defined macros for conditional compilation
DEFS = -DDEBUG_FLAG -DEXPERIMENTAL=0

# The final executable program file, i.e. name of our program
BIN = 18-Metodo_Rayleigh

# Object files from which $BIN depends
RUTA= ../..
OBJS= ${RUTA}/matrix.o \
	${RUTA}/Eigen.o\
	${RUTA}/solve.o\
	${RUTA}/operacion_matriz.o\
	${RUTA}/EcuacionesL_Metodos.o
# This default rule compiles the executable program
$(BIN): $(OBJS) $(BIN).c
	$(CC) $(CFLAGS) $(DEFS) $(OBJS) $(BIN).c -o $(BIN) $(LIBS)

# This rule compiles each module into its object file
%.o: %.c %.h
	$(CC) -c $(CFLAGS) $(DEFS) $< -o $@

clean:
	rm -f *~ *.o $(BIN)
	rm -f ../../*.o

depend:
	makedepend -Y -- $(CFLAGS) $(DEFS) -- *.c
run:
	./$(BIN) $(f1) $(f2)
valgrind:
	valgrind --tool=memcheck --leak-check=yes ./$(BIN) ${f1} $(f2)
