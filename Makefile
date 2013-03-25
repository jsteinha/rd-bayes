% : %.cpp util.h infer.h Makefile
	g++ $< -Lsmile -l smile -o $@

check-syntax:
	gcc -o nul -S ${CHK_SOURCES}
