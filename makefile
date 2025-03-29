main:
	gcc ./main_lab/process.c ./main_lab/insert.c ./main_lab/matrix.c ./main_lab/main.c -g -o ./main_lab/lab1.out
dop:
	gcc ./add_task/main.c ./add_task/matrix.c -g -o0 -o ./add_task/dop.out
tester:
	gcc ./add_task/tester.c -g -o0 -o ./add_task/test.out
clean:
	rm ./**/*.out ./**/*.bin
