CC=g++
LIBS=lm

tags: tags.cpp driver.cpp tags.h
	$(CC) driver.cpp  tags.cpp -o tags

clean:
	rm -f *.o