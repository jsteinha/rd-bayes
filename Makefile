% : %.cpp Makefile
	g++ $< -Lsmile -l smile -o $@
