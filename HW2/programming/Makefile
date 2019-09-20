CXX = g++
CXXFLAGS = -std=c++11 -Wall

targets = program_dc program_dp

all: $(targets)

$(targets): %: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ $<

clean:
	rm $(targets)
