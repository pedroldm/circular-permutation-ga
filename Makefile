# Compiler
CXX := g++

# Base include path
INCLUDE := -Iinclude

# Directories
SRC_DIR := src
SRC_TIP_DIR := src/tip
OBJ_DIR := build

# Source files
SRCS := $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_TIP_DIR)/*.cpp)

# Object files for each build type
OBJS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(filter $(SRC_DIR)/%.cpp, $(SRCS))) \
        $(patsubst $(SRC_TIP_DIR)/%.cpp, $(OBJ_DIR)/tip/%.o, $(filter $(SRC_TIP_DIR)/%.cpp, $(SRCS)))

OBJS_DEBUG := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o.debug, $(filter $(SRC_DIR)/%.cpp, $(SRCS))) \
              $(patsubst $(SRC_TIP_DIR)/%.cpp, $(OBJ_DIR)/tip/%.o.debug, $(filter $(SRC_TIP_DIR)/%.cpp, $(SRCS)))

OBJS_PRD := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o.prd, $(filter $(SRC_DIR)/%.cpp, $(SRCS))) \
            $(patsubst $(SRC_TIP_DIR)/%.cpp, $(OBJ_DIR)/tip/%.o.prd, $(filter $(SRC_TIP_DIR)/%.cpp, $(SRCS)))

# Targets
TARGET := main
TARGET_DEBUG := main_debug
TARGET_PRD := main_prd

# Compiler flags for each build
CXXFLAGS := -std=c++17 -Wall -Wextra $(INCLUDE)
CXXFLAGS_DEBUG := -std=c++17 -Wall -Wextra -g $(INCLUDE)
CXXFLAGS_PRD := -std=c++17 -O3 -march=native $(INCLUDE)

# Default target is development build
all: $(TARGET)

# Build targets
dev: $(TARGET)
debug: $(TARGET_DEBUG)
prd: $(TARGET_PRD)

# Link executables
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TARGET_DEBUG): $(OBJS_DEBUG)
	$(CXX) $(CXXFLAGS_DEBUG) -o $@ $^

$(TARGET_PRD): $(OBJS_PRD)
	$(CXX) $(CXXFLAGS_PRD) -o $@ $^

# Compile development object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/tip/%.o: $(SRC_TIP_DIR)/%.cpp | $(OBJ_DIR)/tip
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile debug object files
$(OBJ_DIR)/%.o.debug: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS_DEBUG) -c $< -o $@

$(OBJ_DIR)/tip/%.o.debug: $(SRC_TIP_DIR)/%.cpp | $(OBJ_DIR)/tip
	$(CXX) $(CXXFLAGS_DEBUG) -c $< -o $@

# Compile production object files
$(OBJ_DIR)/%.o.prd: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS_PRD) -c $< -o $@

$(OBJ_DIR)/tip/%.o.prd: $(SRC_TIP_DIR)/%.cpp | $(OBJ_DIR)/tip
	$(CXX) $(CXXFLAGS_PRD) -c $< -o $@

# Create build directories
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/tip:
	mkdir -p $(OBJ_DIR)/tip

# Clean rule
clean:
	rm -rf $(OBJ_DIR) $(TARGET) $(TARGET_DEBUG) $(TARGET_PRD)

.PHONY: all dev debug prd clean
