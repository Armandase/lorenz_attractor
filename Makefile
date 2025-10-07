MAKEFLAGS += -j

CXX		=	c++
NAME 	= 	lorenz
SRC 	=	main.cpp utils.cpp Attractor.cpp Points.cpp
HEADER	=	inc/simulation.hpp inc/Attractor.hpp inc/Points.hpp
OBJS	=	$(addprefix obj/, $(SRC:.cpp=.o))
CXXFLAGS=	-Wall -Wextra --std=c++17 -g -I$(SDL2_TTF) -I$(SDL2_IMAGE) -I/usr/include/SDL2
SDL2_TTF=	libs/SDL2_ttf
SDL2_IMAGE=	libs/SDL2_image
LDFLAGS = 	-lSDL2 -L$(SDL2_TTF)/build -lSDL2_ttf-2.0 -L$(SDL2_IMAGE)/build -lSDL2_image-2.0

all		:	${NAME} 

lib		:
			cd ${SDL2_TTF} && \
			./configure && \
			cmake -S . -B build && \
			make -C build

			cd ${SDL2_IMAGE} && \
			./configure && \
			cmake -S . -B build && \
			make -C build

lib_clean:
			rm -r ${SDL2_TTF}/build
			rm -r ${SDL2_IMAGE}/build

${NAME}	:	${OBJS} ${HEADER}
			${CXX} -o ${NAME} ${OBJS} ${LDFLAGS}

obj/%.o: src/%.cpp $(HEADER)
	@mkdir -p $(@D)
	${CXX} ${CXXFLAGS} -c $< -o $@

fclean: clean
	rm -f $(NAME)

clean:
	rm -rf obj/

re: fclean
	@make all

.PHONY: all fclean clean re lib lib_clean
