CXX = icpc
OPT = -O3
VT = -g -opt-report-phase pgo -opt-report-file vtunedemo.rpt -opt-report-level max
all: mbp
mbp: main.o union_find.o
	$(CXX)  $(OPT) $(VT)  main.o union_find.o -o mbp
main.o: max_bandwidth.hpp edge.hpp vertex.hpp graph.hpp
	$(CXX)  $(OPT) $(VT)   main.cpp -c
union_find.o: union_find.cpp union_find.hpp
	$(CXX)  $(OPT) $(VT)  union_find.cpp  -c

clean:
	rm mbp *.o 
