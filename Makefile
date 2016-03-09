build:
	g++ -std=c++11 main.cpp graphics.cpp transformation.cpp curves.cpp -o line.out

generate: build
	./line.out

display: generate
	display line.ppm
