SRC_DIR=src
INC_DIR=include
BIN_DIR=bin

SRCS=$(wildcard $(SRC_DIR)/*.cpp)
OBJS=$(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%.o,$(SRCS))
DEPS=$(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%.d,$(SRCS))

EXE=$(BIN_DIR)/Debug

all: $(EXE)

$(EXE): $(OBJS)
	g++ $^ -o $@ -lglut -lGL -lGLU

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ -I$(INC_DIR) -MMD -MP -c $< -o $@

clean:
	rm -f $(OBJS) $(DEPS) $(EXE)

-include $(DEPS)
