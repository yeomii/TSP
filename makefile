all:
	g++ -O3 -g ga.cpp operators.cpp enums.cpp gautil.cpp lk.cpp edgetour.cpp tsplib_io.cpp cpputil.cpp -lm -DDISTANCE_CALC_METHOD=1

run:
	./a.out

clean:
	rm a.out
