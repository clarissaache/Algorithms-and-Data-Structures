myProgram: test-subseq.o maxSeq.o
	gcc -o myProgram maxSeq.o test-subseq.o
power.o: maxSeq.c
	gcc -std=gnu99 -pedantic -Wall -c maxSeq.c
test-power.o: test-subseq.c
	gcc -std=gnu99 -pedantic -Wall -c test-subseq.c
