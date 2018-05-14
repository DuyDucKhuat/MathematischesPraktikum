CXXFLAGS = -O2 -Wall

test: vektor.o matrix.o test.o
	$(CXX) $(CXXFLAGS) -o $@ $^
vektor.o: vektor.cpp vektor.h
	$(CXX) $(CXXFLAGS) -c $<
matrix.o: matrix.cpp matrix.h vektor.h
	$(CXX) $(CXXFLAGS) -c $<
main.o: main.cpp 
	$(CXX) -c  $<
main: main.o unit.o
	$(CXX) -o $^
.PHONY: clean
clean:
	rm -f test vektor.o matrix.o
