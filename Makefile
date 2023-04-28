#run:
#	g++ -Wall -Werror -o main main.cpp && ./main

CC = g++
TARGET = main

# .cpp files paths
PATH_MAIN = ./src/geometry/
PATH_LIB = ./src/libgeometry/

# .o files paths
PATH_OBJ_MAIN = ./obj/src/geometry/
PATH_OBJ_LIB = ./obj/src/libgeometry/

# executable file path
PATH_BIN = ./bin/

# libs files
SRC_LIB = $(wildcard $(PATH_LIB)*.cpp)
OBJ_LIB = $(patsubst $(PATH_LIB)%.cpp, $(PATH_OBJ_LIB)%.o, $(SRC_LIB))

# main files
SRC_MAIN = $(wildcard $(PATH_MAIN)*.cpp)
OBJ_MAIN = $(patsubst $(PATH_MAIN)%.cpp, $(PATH_OBJ_MAIN)%.o, $(SRC_MAIN))


# final
$(PATH_BIN)$(TARGET) : $(OBJ_LIB) $(OBJ_MAIN)
	$(CC) $(OBJ_LIB) $(OBJ_MAIN) -o $(PATH_BIN)$(TARGET)

# libs
$(PATH_OBJ_LIB)%.o : $(PATH_LIB)%.cpp
	$(CC) -c $< -o $@

# main
$(PATH_OBJ_MAIN)%.o : $(PATH_MAIN)%.cpp
	$(CC) -I src/libgeometry/headers -c $< -o $@


clear :
	rm $(OBJ_MAIN) $(OBJ_LIB) $(PATH_BIN)$(TARGET)

run : $(PATH_BIN)$(TARGET)
	$(PATH_BIN)$(TARGET)

drun : $(PATH_BIN)$(TARGET)
	$(PATH_BIN)$(TARGET)
	rm $(OBJ_MAIN) $(OBJ_LIB) $(PATH_BIN)$(TARGET)
