compile: clear
		g++ src/*.cpp -o main

safe-compile:
		g++ src/*.cpp -o main

clear:
		rm dados.d
		rm main
