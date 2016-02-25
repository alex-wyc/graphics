build:
	g++ main.cpp -std=c++11 graphics.cpp transformation.cpp -o line.out

generate: build
	./line.out

display: generate
	display line.ppm
