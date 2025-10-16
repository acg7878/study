# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -g

# Target executable name
TARGET = main

# Source files
SRCS = main.cpp BinarySearchTree.cpp AVLTree.cpp

# Object files are derived from source files
OBJS = $(SRCS:.cpp=.o)

# Header files (dependencies)
DEPS = BinarySearchTree.h AVLTree.h

# Phony targets (targets that are not actual files)
.PHONY: all clean

# Default target, executed when you just run "make"
all: $(TARGET)

# Rule to link the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Generic rule to compile source files into object files
# It states that each .o file depends on its corresponding .cpp file and the headers
%.o: %.cpp $(DEPS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Rule to clean up the project directory
clean:
	rm -f $(TARGET) $(OBJS)
