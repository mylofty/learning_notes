INCLUDES = -I/home/dzm/opencv3_4/include -I.
LIBS = -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -lopencv_videoio -lpthread
LIBDIRS = -L/home/dzm/opencv3_4/lib64

all:singleThreadProcess multiThreadProcess.out

singleThreadProcess : singleThreadProcess.cpp
	g++ -o singleThreadProcess singleThreadProcess.cpp ${INCLUDES} ${LIBDIRS} ${LIBS}


multiThreadProcess.out : multiThreadProcess.o
	g++ multiThreadProcess.o -o multiThreadProcess.out ${INCLUDES} ${LIBDIRS} ${LIBS}
multiThreadProcess.o : multiThreadProcess.cpp
	g++ -c multiThreadProcess.cpp -o multiThreadProcess.o ${INCLUDES} ${LIBDIRS} ${LIBS}
# camera.o : camera.cpp
# 	g++ -c camera.cpp -o camera.o ${INCLUDES} ${LIBDIRS} ${LIBS}


clean:
	rm -rf *.o *.out