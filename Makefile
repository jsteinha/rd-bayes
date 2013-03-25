% : %.cpp util.h infer.h Makefile
	g++ $< -Lsmile -l smile -o $@
