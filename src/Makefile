all: clean install run

clean:
	rm -rf main.txt

install: main.c
	@g++ -o main.txt main.c

run: main.txt
	@./main.txt
