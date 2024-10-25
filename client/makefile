main.c : main.o file.o login.o 
	gcc -o client main.o file.o login.o -lreadline
main.o : host/main.c
	gcc -c host/main.c -o main.o
file.o : chat/file/file.c
	gcc -c chat/file/file.c -o file.o
login.o : chat/login/login.c
	gcc -c chat/login/login.c -o login.o