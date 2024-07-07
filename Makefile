


CXX = clang++
CXXFLAGS = -std=c++17 -Werror -Wsign-conversion
LDFLAGS = -lstdc++ -lm -lsfml-graphics -lsfml-window -lsfml-system
SFML_INCLUDE = -I/usr/include/SFML

OBJS = demo.o 

demo: $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o demo

demo.o: demo.cpp
	$(CXX) $(CXXFLAGS) $(SFML_INCLUDE) -c demo.cpp


test: TestCounter.o Test.o
	@echo "Compiling test executable..."
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o test
	@echo "Test executable created."

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(SFML_INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJS) demo TestCounter.o Test.o test
