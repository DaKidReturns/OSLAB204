all: clean banker test

banker:
	gcc -o banker -Wall -Werror banker_with_resource_req.c
	chmod 755 banker

clean:
	rm -f banker output

test:
	echo "Output 1"
	./banker < input | tail -1
	echo "Output 2"
	./banker < input2 | tail -1
