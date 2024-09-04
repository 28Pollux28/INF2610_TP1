all:
	gcc -O0 -std=gnu11 -Werror -Wall -Wno-unused-result -Wno-unused-variable -o processlab ./libprocesslab/libprocesslab.c  processes_part1.c processes_part2.c ./libprocesslab/processlab.c -lrt 

mac:
	gcc -O0 -std=gnu11 -Werror -Wall -Wno-unused-result -Wno-unused-variable -o processlab ./libprocesslab/libprocesslab.c  processes_part1.c processes_part2.c ./libprocesslab/processlab.c

clean:
	rm -f processlab
