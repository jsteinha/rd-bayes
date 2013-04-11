% : %.cpp util.h task.h infer.h Makefile
	g++ $< -Lsmile -l smile -o $@

check-syntax:
	g++ -o nul -S ${CHK_SOURCES}
	rm nul
