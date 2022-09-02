LIBGUI = solgui
TARGET = solgui_test
CC=g++ -Wall
OPTIONS = -lGLEW -lglfw -lGL -lftgl -lfreetype -lm -lXrandr -lX11 -lXxf86vm -lpthread -I/usr/include/freetype2
all:
	$(CC) -c $(LIBGUI).cpp -o $(LIBGUI).o $(OPTIONS)
	$(CC) -c $(TARGET).cpp -o $(TARGET).o $(OPTIONS)
	$(CC) $(LIBGUI).o $(TARGET).o -o $(TARGET) $(OPTIONS)
	rm -r *.o
