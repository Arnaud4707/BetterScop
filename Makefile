NAME= prog
CXX= c++
CXXFLAGS= -Wall -Wextra -std=c++11 -g -fsanitize=address
# CXXFLAGS= -Wall -Wextra -std=c++11
LDFLAGS= -lGL -lglfw -ldl -fsanitize=address
# LDFLAGS= -lGL -lglfw -ldl
HEADER= include/header.hpp include/3D/shader.hpp include/3D/camera.hpp include/3D/ObjectBlender.hpp \
		include/fonction_math.hpp include/vec/Vec2.hpp include/vec/Vec3.hpp include/vec/Vec4.hpp \
		include/mat/Mat2.hpp include/mat/Mat3.hpp include/mat/Mat4.hpp include/fft/AudioStats.hpp \
		include/midi/Note.hpp include/midi/Midi.hpp include/fft/DataAudio.hpp include/fft/FFT.hpp \
		include/musicEngine/MusicState.hpp include/musicEngine/MusicEngine.hpp include/musicEngine/MusicAnalyzer.hpp \
		include/animationEngine/AnimationState.hpp include/animationEngine/AnimationEngine.hpp include/globals.hpp \
		include/other/History.hpp include/other/StatsHistory.hpp include/other/NormalizePeak.hpp include/WindowManager.hpp

DIR_SRC = src/
PATH_SRC= 	Shader.cpp ObjectBlender.cpp Midi.cpp FFT.cpp MusicEngine.cpp MusicAnalyzer.cpp \
			globals.cpp WindowManager.cpp utils.cpp init.cpp main.cpp
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