NAME	= ogl

SRC		=	main.cpp	\
			Shader.cpp	\
			Camera.cpp	\
			TextManager.cpp	\
			Cube.cpp

HEAD_DIR	= include
SRC_DIR		= src
DEBUG_DIR	= debug
STATIC_DIR	= static


INCLUDES	= -I/usr/include/freetype2
LIBS		= -ldl -lGL -lglfw3 -lGLEW -lSOIL -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -pthread \
				-lfreetype -lz -lpng12

OBJ	= $(patsubst %.cpp,$(STATIC_DIR)/%.o,$(SRC))

CC			= clang++
OPTI		= -O3
FLAGS		= -std=c++11 -Wall #-Wextra -Wno-unused-result


$(shell mkdir -p $(STATIC_DIR) $(DEBUG_DIR))


.PHONY: clean fclean re

all: $(NAME)
	@echo "Compilation terminee. (realease)"

$(NAME): $(OBJ)
	$(CC) $(OPTI) -I $(HEAD_DIR) $(INCLUDES) -o $@ $(OBJ) $(FLAGS) $(LIBS)

$(STATIC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(OPTI) -I $(HEAD_DIR) $(INCLUDES) -o $@ -c $< $(FLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean
	make
