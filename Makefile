NAME		= ogl
NAME_DEBUG	= ogl_debug

SRC		=	main.cpp	\
			Shader.cpp	\
			Camera.cpp	\
			TextManager.cpp	\
			Cube.cpp	\
			Section.cpp	\
			Chunk.cpp	\
			MessageManager.cpp	\
			World.cpp	\
			WorldGenerator.cpp	\
			TextureManager.cpp	\
			InputManager.cpp
			##Skybox.cpp

HEAD_DIR	= include
SRC_DIR		= src
DEBUG_DIR	= debug
STATIC_DIR	= static
DEP_DIR		= dep


INCLUDES	= -I/usr/include/freetype2
LIBS		= -lGL -lglfw3 -lGLEW -lSOIL -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -pthread \
				-lfreetype -lz -lpng12  -ldl

OBJ				= $(patsubst %.cpp,$(STATIC_DIR)/%.o,$(SRC))
OBJ_DEBUG		= $(patsubst %.cpp,$(DEBUG_DIR)/%.o,$(SRC))
DEPS			= $(patsubst %.cpp,$(DEP_DIR)/%.d,$(SRC))

CC			= clang++
OPTI		= -O3
FLAGS		= -std=c++11 -Wall #-Wextra -Wno-unused-result
DEPENDS 	= -MT $@ -MD -MP -MF $(subst .o,.d,$@)


$(shell mkdir -p $(STATIC_DIR) $(DEBUG_DIR) $(DEP_DIR))


.PHONY: clean fclean re debug

all: $(NAME)
	@echo "Compilation terminee. (realease)"

$(NAME): $(OBJ)
	$(CC) $(OPTI) $(FLAGS) -I $(HEAD_DIR) $(INCLUDES) -o $@ $(OBJ) $(LIBS)

debug: $(OBJ_DEBUG)
	$(CC) $(OPTI) $(FLAGS) -I $(HEAD_DIR) $(INCLUDES) -o $(NAME_DEBUG) $(OBJ_DEBUG) $(LIBS) -g

-include $(OBJ:.o=.d)

$(STATIC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(OPTI) $(FLAGS) $(DEPENDS) -I $(HEAD_DIR) $(INCLUDES) -o $@ -c $<

$(DEBUG_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(OPTI) $(FLAGS) $(DEPENDS) -I $(HEAD_DIR) $(INCLUDES) -o $@ -c $< -g

clean:
	rm -f $(OBJ) $(OBJ_DEBUG) $(DEPS)

fclean: clean
	rm -f $(NAME) $(NAME_DEBUG)

re: fclean
	make
