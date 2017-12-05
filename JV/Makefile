CPPFLAGS = -I/usr/include/irrlicht
CXXFLAGS = -Wall -Wextra -O2 -g -std=c++11 -Wno-unused-parameter

irrlicht-gui: main.o events.o 
	g++ $^ -o $@ -lIrrlicht -lX11 -lXxf86vm -lGLU -lGL -lglut

main.o events.o  : events.h gui_ids.h  
clean:
	@rm -f irrlicht-gui *.o
