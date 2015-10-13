a.out : bplus.o timer_nrp.o makefile
	gcc -g bplus.o timer_nrp.o

bplus.o : bplus.c
	gcc -g -c bplus.c

timer_nrp.o: timer_nrp.c timer_nrp.h
	gcc -g -c timer_nrp.c

profile:
	make a.out
	for i in 10000  20000 30000 40000 50000  ; do ./a.out "$$i" ;done 

plot : 
	make profile
	gnuplot bplus.gnu

clean : 
	rm -f a.out *.o bplus.txt bplus.jpg sourcefile.aux sourcefile.log sourcefile.pdf

report : sourcefile.tex
	make plot
	pdflatex sourcefile.tex
