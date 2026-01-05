all: clean install Run
graphics: graphics-clean graphics-compile graphics-run a
r_w: r_w-clean r_w-compile r_w-run a

clean:
	rm -rf main.txt

install: main.cpp
	@g++ -o main.txt main.cpp

Run: main.txt
	@./main.txt

graphics-clean:
	rm -rf graphics.txt

graphics-compile: graphics.cpp
	@g++ -o graphics.txt -lglfw graphics.cpp

graphics-run: graphics.txt
	@./graphics.txt

r_w-clean:
	rm -rf r_w.txt

r_w-compile: r_w.cpp
	@g++ -o r_w.txt r_w.cpp

r_w-run: r_w.txt
	@./r_w.txt

