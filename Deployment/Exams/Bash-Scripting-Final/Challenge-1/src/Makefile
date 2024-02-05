all:
	rm -f checker.o checker
	gcc -g -o checker.o checker.c -w
	strip checker.o
	cp checker.o checker
	rm checker.o
	./docker-build.sh
run:
	docker run --name test-container -d --rm -e CHAL_ID=1 -e TEAM_ID=1 cy102l/final_q1
	docker exec -it test-container bash
	docker stop test-container
clean:
	rm checker
