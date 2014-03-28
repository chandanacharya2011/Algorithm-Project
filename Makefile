CXX = icpc
OPT = -O3
all: mbp
mbp: main.cpp union_find.cpp
	$(CXX)  $(OPT) main.cpp union_find.cpp -o mbp
clean:
	rm mbp
