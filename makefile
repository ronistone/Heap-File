compile: clear
		g++ --std=c++11 src/*.cpp -o main -g

safe-compile:
		g++ --std=c++11 src/*.cpp -o main -g

clear:
		rm *.data
		rm *.join
		rm main
