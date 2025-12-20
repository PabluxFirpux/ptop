CFLAGS = -Wall -pedantic -g -lncursesw

LIBDIR = libs/
SRC = main.o $(LIBDIR)String.o

TARGET = ptop

all: $(TARGET)
	./$(TARGET)

$(TARGET): $(SRC)
	gcc $(SRC) -o $(TARGET) $(CFLAGS)

%.o : %.c
	gcc -c $? -o $@ $(CFLAGS)

clean :
	@echo "Removing trash"
	@rm -rf *.o || rm -rf *.out || echo "Already clean :)"