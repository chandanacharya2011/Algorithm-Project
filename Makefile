CXX = icpc
OPT = -O3
VT = -g -opt-report-phase pgo -opt-report-file vtunedemo.rpt -opt-report-level max
all: mbp
mbp: main.cpp union_find.cpp
	$(CXX)  $(OPT) $(VT) main.cpp union_find.cpp -o mbp
clean:
	rm mbp
