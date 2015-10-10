NAME		= ogl
NAME_DEBUG	= ogl_debug

SRC		=	main.cpp	\
			GUI.cpp	\
			Game.cpp	\
			RenderContext.cpp	\
			ChunkManager.cpp	\
			InputManager.cpp	\
			MessageManager.cpp	\
			BlockTypeManager.cpp	\
			WorldGenerator.cpp	\
			ShaderManager.cpp	\
			Block.cpp	\
			BlockType.cpp	\
			Camera.cpp	\
			Chunk.cpp	\
			Color.cpp	\
			EWorld.cpp	\
			Player.cpp	\
			Shader.cpp	\
			Skybox.cpp	\
			World.cpp	\
			Mesh.cpp

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

OPTI		= -O3
CXXFLAGS	= -std=c++11 -Wall #-Wextra -Wno-unused-result
DEPENDS 	= -MT $@ -MD -MP -MF $(subst .o,.d,$@)


$(shell mkdir -p $(STATIC_DIR) $(DEBUG_DIR) $(DEP_DIR))


.PHONY: clean fclean re debug

all: $(NAME)
	@echo "Compilation terminee. (realease)"

$(NAME): $(OBJ)
	$(CXX) $(OPTI) $(CXXFLAGS) -I $(HEAD_DIR) $(INCLUDES) -o $@ $(OBJ) $(LIBS)

debug: $(OBJ_DEBUG)
	$(CXX) $(OPTI) $(CXXFLAGS) -I $(HEAD_DIR) $(INCLUDES) -o $(NAME_DEBUG) $(OBJ_DEBUG) $(LIBS) -g

-include $(OBJ:.o=.d)

$(STATIC_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(OPTI) $(CXXFLAGS) $(DEPENDS) -I $(HEAD_DIR) $(INCLUDES) -o $@ -c $<

$(DEBUG_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(OPTI) $(CXXFLAGS) $(DEPENDS) -I $(HEAD_DIR) $(INCLUDES) -o $@ -c $< -g

clean:
	rm -f $(OBJ) $(OBJ_DEBUG) $(DEPS)

fclean: clean
	rm -f $(NAME) $(NAME_DEBUG)

re: fclean
	make
