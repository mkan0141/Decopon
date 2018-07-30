game: ./src/main.cpp
	g++ -std=c++14 -Wall -O3 -o Decopon ./src/main.cpp 
Board.hpp.gch: ./src/hpp/Board.hpp
	g++ -std=c++14 -Wall -O3 ./src/hpp/Board.hpp
AI.hpp.gch: ./src/hpp/AI.hpp
	g++ -std=c++14 -Wall -O3 ./src/hpp/AI.hpp
RandomAI.hpp.gch: ./src/hpp/RandomAI.hpp
	g++ -std=c++14 -Wall -O3 ./src//hpp/RandomAI.hpp
User.hpp.gch: ./src/hpp/User.hpp
	g++ -std=c++14 -Wall -O3 ./src/hpp/User.hpp
