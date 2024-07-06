CXX = clang++
CXXFLAGS = -std=c++17 -Werror -Wsign-conversion
LDFLAGS = -lstdc++ -lm

OBJS = demo.o 

demo: $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o demo

Demo.o: demo.cpp tree.hpp
	$(CXX) $(CXXFLAGS) -c demo.cpp

test: TestCounter.o Test.o
	@echo "Compiling test executable..."
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $^ -o test
	@echo "Test executable created."

%.o: %.cpp
	$(CXX) $(CXXFLAGS) --compile $< -o $@

clean:
	rm -f $(OBJS) demo TestCounter.o Test.o test
