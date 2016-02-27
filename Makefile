build:
	g++ -std=c++11 main.cpp graphics.cpp transformation.cpp -o draw_shell.out

generate: build
	./line.out

display: generate
	display line.ppm
