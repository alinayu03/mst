# Compiler settings - Can change to clang++ if preferred
CXX = g++
CXXFLAGS = -Wall -g

# Build target executable:
TARGET = randmst

# Source files
SRC = randmst.cpp

# Object files
OBJ = $(SRC:.cpp=.o)

# Default make command
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJ)

# Clean up
clean:
	rm -f $(OBJ) $(TARGET)

# Rule for object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<
