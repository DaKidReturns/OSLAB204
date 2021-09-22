all: clean build

build: 
	@echo "Compiling files.... "
	@gcc -o priority priority.c 
	@gcc -o fcfs fcfs.c 
	@gcc -o roundrobin roundrobin.c
	@gcc -o sjfs sjfs.c
	@echo "Done"

clean:
	@echo "Removing previously compiled binaries"
	@if [ -f fcfs ]; then rm fcfs; fi 
	@if [ -f priority ]; then rm priority; fi
	@if [ -f sjfs ]; then rm sjfs; fi
	@if [ -f roundrobin ]; then rm roundrobin; fi
