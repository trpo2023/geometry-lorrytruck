CC = g++

# flags
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -MMD

# executable names
TARGET = main
TARGET_TEST = test

# .cpp files paths
PATH_MAIN = ./src/geometry/
PATH_TEST = ./test/
PATH_LIB = ./src/libgeometry/

# .o files paths
PATH_OBJ_MAIN = ./obj/src/geometry/
PATH_OBJ_TEST = ./obj/test/
PATH_OBJ_LIB = ./obj/src/libgeometry/

# executable files path
PATH_BIN_TARGET = ./bin/geometry/
PATH_BIN_TEST = ./bin/geometry-test/

# -----------------------------------------------------------------------

# libs files
SRC_LIB = $(wildcard $(PATH_LIB)*.cpp)
OBJ_LIB = $(patsubst $(PATH_LIB)%.cpp, $(PATH_OBJ_LIB)%.o, $(SRC_LIB))
STAT_LIB = $(patsubst $(PATH_LIB)%.cpp, $(PATH_OBJ_LIB)%.a, $(SRC_LIB))
STAT_LIB = $(OBJ_LIB)

# main files
SRC_MAIN = $(wildcard $(PATH_MAIN)*.cpp)
OBJ_MAIN = $(patsubst $(PATH_MAIN)%.cpp, $(PATH_OBJ_MAIN)%.o, $(SRC_MAIN))

# test files
SRC_TEST = $(wildcard $(PATH_TEST)*.cpp)
OBJ_TEST = $(patsubst $(PATH_TEST)%.cpp, $(PATH_OBJ_TEST)%.o, $(SRC_TEST)) 

# -----------------------------------------------------------------------

test : $(PATH_BIN_TEST)$(TARGET_TEST)

all : $(PATH_BIN_TARGET)$(TARGET)

# final
$(PATH_BIN_TARGET)$(TARGET) : $(PATH_BIN_TARGET) $(STAT_LIB) $(OBJ_MAIN)
	$(CC) $(STAT_LIB) $(OBJ_MAIN) -o $(PATH_BIN_TARGET)$(TARGET)

$(PATH_BIN_TARGET):
	mkdir -p $(PATH_BIN_TARGET)
# test
$(PATH_BIN_TEST)$(TARGET_TEST) : $(PATH_BIN_TEST) $(STAT_LIB) $(OBJ_TEST)
	$(CC) $(CPPFLAGS) $(CFLAGS) $(STAT_LIB) $(OBJ_TEST) -o $(PATH_BIN_TEST)$(TARGET_TEST)

$(PATH_BIN_TEST):
	mkdir -p $(PATH_BIN_TARGET)

# -----------------------------------------------------------------------

# libs
$(PATH_OBJ_LIB)%.o : $(PATH_LIB)%.cpp
	$(CC) -c $< -o $@
	
# lib.a
$(PATH_OBJ_LIB)%.a : $(PATH_OBJ_LIB)%.o
	ar rcs $@ $^

# main
$(PATH_OBJ_MAIN)%.o : $(PATH_MAIN)%.cpp
	$(CC) -I src/libgeometry/headers -c $< -o $@

# test
$(PATH_OBJ_TEST)%.o : $(PATH_TEST)%.cpp
	$(CC) -I src/libgeometry/headers -c $< -o $@

# -----------------------------------------------------------------------

clear :
	rm -f $(OBJ_MAIN) $(OBJ_TEST) \
	$(PATH_BIN_TARGET)$(TARGET) $(PATH_BIN_TEST)$(TARGET_TEST) \
	$(OBJ_LIB) $(STAT_LIB)

debug : 
	$(info $(STAT_LIB))

runt : $(PATH_BIN_TEST)$(TARGET_TEST)
	./$(PATH_BIN_TEST)$(TARGET_TEST)

run : $(PATH_BIN_TARGET)$(TARGET)
	./$(PATH_BIN_TARGET)$(TARGET)