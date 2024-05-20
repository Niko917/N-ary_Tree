TARGET = lab_4
CC = g++

PREF_SRC = ./SRC/
PREF_OBJ = ./OBJ/

SRC = $(wildcard $(PREF_SRC)*.cpp) 
OBJ = $(patsubst $(PREF_SRC)%.cpp, $(PREF_OBJ)%.o, $(SRC))

$(TARGET) : $(OBJ)
	$(CC) $(OBJ) -g -o $(TARGET) -lm

$(PREF_OBJ)%.o : $(PREF_SRC)%.cpp 
	$(CC) -c $< -o $@

clean :
	rm $(TARGET) $(PREF_OBJ)*.o 
