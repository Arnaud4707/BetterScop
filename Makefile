NAME= prog
CXX= c++
CXXFLAGS= -Wall -Wextra -std=c++11 -g -fsanitize=address
# CXXFLAGS= -Wall -Wextra -std=c++11
LDFLAGS= -lGL -lglfw -ldl -fsanitize=address
# LDFLAGS= -lGL -lglfw -ldl
HEADER= include/header.hpp include/shader.hpp include/camera.hpp include/ObjectBlender.hpp \
		include/fonction_math.hpp include/Vec2.hpp include/Vec3.hpp include/Vec4.hpp \
		include/Mat2.hpp include/Mat3.hpp include/Mat4.hpp include/Note.hpp include/Midi.hpp \
		include/DataAudio.hpp include/FFT.hpp include/MusicState.hpp include/MusicEngine.hpp
DIR_SRC = src/
PATH_SRC= Shader.cpp ObjectBlender.cpp Midi.cpp FFT.cpp MusicEngine.cpp fonction.cpp init.cpp main.cpp
SRC= $(addprefix $(DIR_SRC), $(PATH_SRC))
DIR_OBJ= obj/
OBJ= $(addprefix  $(DIR_OBJ), $(PATH_SRC:.cpp=.o))
OBJ_GLAD= obj/glad.o
GLAD= glad.c

$(DIR_OBJ)%.o: $(DIR_SRC)%.cpp $(HEADER)
	mkdir -p obj
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(OBJ_GLAD) $(HEADER)
	$(CXX) $(OBJ) $(OBJ_GLAD) $(LDFLAGS) -o $(NAME)

$(OBJ_GLAD): $(GLAD)
	mkdir -p obj
	$(CXX) $(CXXFLAGS) -c $(GLAD) -o $(OBJ_GLAD)

all: $(NAME)

clean: 
	rm -rf $(OBJ) $(OBJ_GLAD)

fclean: clean 
	rm -rf $(NAME)

re: fclean
	@make --no-print-directory all

teapot: $(OBJ) $(OBJ_GLAD) $(HEADER)
	$(CXX) $(OBJ) $(OBJ_GLAD) $(LDFLAGS) -o $(NAME) -D INIT_ROTY_OBJ=100.0f

# 	$(CXX) $(OBJ) $(OBJ_GLAD) $(LDFLAGS) -o $(NAME) -D INIT_ROTY_OBJ=INIT_ROTY_TEAPOT


.PHONY: all clean fclean re teapot