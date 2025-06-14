# Compiler
CXX := g++

# Base include path
INCLUDE := -Iinclude

# Directories
SRC_DIR := src
SRC_TIP_DIR := src/tip
SRC_CBP_DIR := src/cbp
OBJ_DIR := build

# Main files
MAIN_TIP := $(SRC_DIR)/mainTIP.cpp
MAIN_CBP := $(SRC_DIR)/mainCBP.cpp

# Source files
SRCS_COMMON := $(wildcard $(SRC_DIR)/*.cpp)
SRCS_TIP := $(filter-out $(MAIN_CBP), $(SRCS_COMMON)) $(wildcard $(SRC_TIP_DIR)/*.cpp)
SRCS_CBP := $(filter-out $(MAIN_TIP), $(SRCS_COMMON)) $(wildcard $(SRC_CBP_DIR)/*.cpp)

# Object files macros
define OBJS_template
$(patsubst %.cpp,$(OBJ_DIR)/$(1)/%.o,$(notdir $(2)))
endef
define OBJS_debug_template
$(patsubst %.cpp,$(OBJ_DIR)/$(1)/%.o.debug,$(notdir $(2)))
endef
define OBJS_prd_template
$(patsubst %.cpp,$(OBJ_DIR)/$(1)/%.o.prd,$(notdir $(2)))
endef

# Object file lists
OBJS_TIP := $(call OBJS_template,tip,$(SRCS_TIP))
OBJS_TIP_DEBUG := $(call OBJS_debug_template,tip,$(SRCS_TIP))
OBJS_TIP_PRD := $(call OBJS_prd_template,tip,$(SRCS_TIP))

OBJS_CBP := $(call OBJS_template,cbp,$(SRCS_CBP)) $(OBJ_DIR)/tip/Instance.o
OBJS_CBP_DEBUG := $(call OBJS_debug_template,cbp,$(SRCS_CBP)) $(OBJ_DIR)/tip/Instance.o.debug
OBJS_CBP_PRD := $(call OBJS_prd_template,cbp,$(SRCS_CBP)) $(OBJ_DIR)/tip/Instance.o.prd

# Executables
TIP := tip
TIP_DEBUG := tip_debug
TIP_PRD := tip_prd

CBP := cbp
CBP_DEBUG := cbp_debug
CBP_PRD := cbp_prd

# Flags
CXXFLAGS := -std=c++17 -Wall -fopenmp -Wextra $(INCLUDE)
CXXFLAGS_DEBUG := -std=c++17 -Wall -Wextra -g $(INCLUDE)
CXXFLAGS_PRD := -std=c++17 -fopenmp -O3 -march=native $(INCLUDE)

# Targets
all: $(TIP)

tip: $(TIP)
tip_debug: $(TIP_DEBUG)
tip_prd: $(TIP_PRD)

cbp: $(CBP)
cbp_debug: $(CBP_DEBUG)
cbp_prd: $(CBP_PRD)

# Linking
$(TIP): $(OBJS_TIP)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(TIP_DEBUG): $(OBJS_TIP_DEBUG)
	$(CXX) $(CXXFLAGS_DEBUG) -o $@ $^

$(TIP_PRD): $(OBJS_TIP_PRD)
	$(CXX) $(CXXFLAGS_PRD) -o $@ $^

$(CBP): $(OBJS_CBP)
	$(CXX) $(CXXFLAGS) -o $@ $^

$(CBP_DEBUG): $(OBJS_CBP_DEBUG)
	$(CXX) $(CXXFLAGS_DEBUG) -o $@ $^

$(CBP_PRD): $(OBJS_CBP_PRD)
	$(CXX) $(CXXFLAGS_PRD) -o $@ $^

# Compile generic rules
$(OBJ_DIR)/tip/%.o: $(SRC_TIP_DIR)/%.cpp | $(OBJ_DIR)/tip
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/tip/%.o.debug: $(SRC_TIP_DIR)/%.cpp | $(OBJ_DIR)/tip
	$(CXX) $(CXXFLAGS_DEBUG) -c $< -o $@

$(OBJ_DIR)/tip/%.o.prd: $(SRC_TIP_DIR)/%.cpp | $(OBJ_DIR)/tip
	$(CXX) $(CXXFLAGS_PRD) -c $< -o $@

$(OBJ_DIR)/cbp/%.o: $(SRC_CBP_DIR)/%.cpp | $(OBJ_DIR)/cbp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/cbp/%.o.debug: $(SRC_CBP_DIR)/%.cpp | $(OBJ_DIR)/cbp
	$(CXX) $(CXXFLAGS_DEBUG) -c $< -o $@

$(OBJ_DIR)/cbp/%.o.prd: $(SRC_CBP_DIR)/%.cpp | $(OBJ_DIR)/cbp
	$(CXX) $(CXXFLAGS_PRD) -c $< -o $@

$(OBJ_DIR)/tip/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)/tip
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/tip/%.o.debug: $(SRC_DIR)/%.cpp | $(OBJ_DIR)/tip
	$(CXX) $(CXXFLAGS_DEBUG) -c $< -o $@

$(OBJ_DIR)/tip/%.o.prd: $(SRC_DIR)/%.cpp | $(OBJ_DIR)/tip
	$(CXX) $(CXXFLAGS_PRD) -c $< -o $@

$(OBJ_DIR)/cbp/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)/cbp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/cbp/%.o.debug: $(SRC_DIR)/%.cpp | $(OBJ_DIR)/cbp
	$(CXX) $(CXXFLAGS_DEBUG) -c $< -o $@

$(OBJ_DIR)/cbp/%.o.prd: $(SRC_DIR)/%.cpp | $(OBJ_DIR)/cbp
	$(CXX) $(CXXFLAGS_PRD) -c $< -o $@

# Directory creation
$(OBJ_DIR)/tip:
	mkdir -p $(OBJ_DIR)/tip

$(OBJ_DIR)/cbp:
	mkdir -p $(OBJ_DIR)/cbp

# Clean
clean:
	rm -rf $(OBJ_DIR) $(TIP)* $(CBP)*

.PHONY: all tip tip_debug tip_prd cbp cbp_debug cbp_prd clean
