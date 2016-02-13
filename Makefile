build:
	g++ main.cpp graphics.cpp -o line.out

generate: build
	./line.out

display: generate
	display line.ppm
