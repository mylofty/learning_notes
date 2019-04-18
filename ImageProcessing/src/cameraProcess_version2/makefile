INCLUDES = -I/home/dzm/opencv3_4/include -I.
LIBS = -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs -lopencv_videoio -lpthread
LIBDIRS = -L/home/dzm/opencv3_4/lib64

main.out : main.o camera.o myVideoCapture.o
	g++ main.o camera.o myVideoCapture.o -o main.out ${LIBDIRS} ${LIBS}
main.o : main.cpp
	g++ -c main.cpp -o main.o ${INCLUDES} -std=c++11
camera.o:camera.cpp
	g++ -c camera.cpp -o camera.o ${INCLUDES}  -std=c++11
myVideoCapture.o : myVideoCapture.cpp
	g++ -c myVideoCapture.cpp -o myVideoCapture.o ${INCLUDES}  -std=c++11

clean:
	rm -rf *.o