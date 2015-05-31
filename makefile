all:
	g++ -O3 ga.cpp crossover.cpp lk.cpp edgetour.cpp tsplib_io.cpp cpputil.cpp -lm -DDISTANCE_CALC_METHOD=0

run:
	./a.out

clean:
	rm a.out
