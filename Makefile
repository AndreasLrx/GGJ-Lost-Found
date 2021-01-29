TARGET := alien

OBJ_PATH := bin
SRCS_BASE := 	main.cpp \
				\
				StateMachine.cpp \
				AssetManager.cpp \
				InputManager.cpp \
				Core.cpp \
				\
				GUIManager.cpp \
				GUIItem.cpp \
				TextItem.cpp \
				TextShape.cpp \
				Button.cpp \
				CheckBox.cpp \
				RadioButtons.cpp \
				TextField.cpp \
				ScrollBar.cpp \
				TextButton.cpp \
				ClickableText.cpp \
				\
				MenuState.cpp

OBJS := $(addprefix $(OBJ_PATH)/, $(SRCS_BASE:.cpp=.o))
CC := g++
#CC := x86_64-w64-mingw32-g++
CFLAGS := -Wall -Werror -pedantic
CFLAGS_LIB := -lm -lsfml-graphics -lsfml-window -lsfml-system
CFLAGS_INCLUDE := -I./include/

all: $(OBJ_PATH) $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(CFLAGS_LIB)

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -f $(TARGET)

re: fclean all

$(OBJ_PATH)/%.o: ./srcs/%.cpp
	$(CC) $(CFLAGS) -c $(CFLAGS_INCLUDE) -o $@ $<

$(OBJ_PATH)/%.o: ./srcs/GameEngine/%.cpp
	$(CC) $(CFLAGS) -c $(CFLAGS_INCLUDE) -o $@ $<

$(OBJ_PATH)/%.o: ./srcs/GUI/%.cpp
	$(CC) $(CFLAGS) -c $(CFLAGS_INCLUDE) -o $@ $<

$(OBJ_PATH)/%.o: ./srcs/States/%.cpp
	$(CC) $(CFLAGS) -c $(CFLAGS_INCLUDE) -o $@ $<

$(OBJ_PATH):
	mkdir $@

.PHONY: clean fclean re all
