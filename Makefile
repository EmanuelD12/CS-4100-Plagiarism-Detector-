LEX_FILE = cmos.l
INPUT_FILE = input.l
OUTPUT_FILE = tokens.txt
LEX_OUTPUT = lex.yy.c
CPP_FILE = cmos.cpp
EXECUTABLE = fingerprint_analysis

.PHONY: all clean

all: $(EXECUTABLE)

# Compile Lex file
$(LEX_OUTPUT): $(LEX_FILE)
	lex $(LEX_FILE)

# Compile C++ file
$(EXECUTABLE): $(LEX_OUTPUT) $(CPP_FILE)
	g++ -o $@ $(LEX_OUTPUT) $(CPP_FILE) -ll

# Run the program
run: $(EXECUTABLE)
	./$(EXECUTABLE) $(INPUT_FILE) > $(OUTPUT_FILE)

clean:
	rm -f $(LEX_OUTPUT) $(EXECUTABLE) $(OUTPUT_FILE)
