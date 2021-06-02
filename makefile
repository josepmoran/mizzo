mizzo: main.cpp producer.cpp consumer.cpp io.c
	g++ main.cpp producer.cpp consumer.cpp io.c producer.h  consumer.h io.h -lpthread -o mizzo