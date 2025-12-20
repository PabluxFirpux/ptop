CFLAGS = -Wall -pedantic -g

LIBDIR = libs/
SRC = main.o $(LIBDIR)String.o

TARGET = ptop

all: $(TARGET)
	./$(TARGET)

$(TARGET): $(SRC)
	gcc $(CFLAGS) $(SRC) -o $(TARGET)

%.o : %.c
	gcc -c $(CFLAGS) $? -o $@

clean :
	@echo "Removing trash"
	@rm -rf *.o || rm -rf *.out || echo "Already clean :)"