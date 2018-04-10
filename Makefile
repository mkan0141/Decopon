game: ./src/main.cpp
	g++ -std=c++11 -o Decopon ./src/main.cpp 
Board.hpp.gch: ./src/hpp/Board.hpp
	g++ -std=c++11 ./src/hpp/Board.hpp
AI.hpp.gch: ./src/hpp/AI.hpp
	g++ -std=c++11 ./src/hpp/AI.hpp
RandomAI.hpp.gch: ./src/hpp/RandomAI.hpp
	g++ -std=c++11 ./src//hpp/RandomAI.hpp
User.hpp.gch: ./src/hpp/User.hpp
	g++ -std=c++11 ./src/hpp/User.hpp
