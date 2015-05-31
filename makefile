all:
	g++ -O3 lk.cpp edgetour.cpp tsplib_io.cpp cpputil.cpp -DLK_TEST -lm -DDISTANCE_CALC_METHOD=0

run:
	./a.out

clean:
	rm a.out
