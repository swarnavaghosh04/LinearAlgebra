bin/test.exe: src/test.cpp include/Vector.hpp
	g++ src/test.cpp -o bin/test.exe -I include