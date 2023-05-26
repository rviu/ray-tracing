main: main.cpp
	g++ $^ -o $@

clean:
	rm main image.ppm
