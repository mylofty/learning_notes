all: create_thread mutex_test timed_mutex_test

create_thread : 	create_thread.cpp
	g++ create_thread.cpp -o create_thread -std=c++11 -lpthread

mutex_test : 	mutex_test.cpp
	g++ mutex_test.cpp -o mutex_test -std=c++11 -lpthread

timed_mutex_test : 	timed_mutex_test.cpp
	g++ timed_mutex_test.cpp -o timed_mutex_test -std=c++11 -lpthread
