#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <math.h>

//riprendere l'esercizio https://github.com/marcotessarotto/esercizio-C-2020-03-30/
//calcolare fibonacci_array(39) e scrivere i valori dell'array in formato testo in un file chiamato fibonacci.txt
//se il file esiste, deve essere sovrascritto
//il programma scrive nel file un valore (in formato testo) per riga
//
//per convertire un numero intero in stringa, vedere:
//https://github.com/marcotessarotto/exOpSys/tree/master/003.2sprintf


unsigned long fibonacci(unsigned int n);
int min_string_len(int number);
char * itoa_printf(int number);


int main(int argc, char *argv[]) {
	char * text_to_write;
	int text_to_write_len;
	unsigned int n = 39;
	int result = fibonacci(n);
	printf("\nThe item (%u) of the Fibonacci's series is: %lu\n\n", n, result);

	char * file_name = "/home/utente/prova.txt";
	printf("Leggo il file %s\n", file_name);

	int fd = open(file_name, O_CREAT | O_TRUNC | O_WRONLY);
	if (fd == -1) {
		perror("open()");
		exit(EXIT_FAILURE);
	}
	else {
		printf("open() ok\n");
	}

	text_to_write = itoa_printf(result);
	text_to_write_len = strlen(text_to_write) + 1;

	printf("scrivo %d bytes\n", text_to_write_len);

	int res = write(fd, text_to_write, text_to_write_len);

	if (res == -1) {
		perror("write()");
		exit(EXIT_FAILURE);
	}

	if (close(fd) == -1) {
		perror("close");
		exit(EXIT_FAILURE);
	}

	return 0;
}


unsigned long fibonacci(unsigned int n) {
	unsigned long firstNum = 0;
	unsigned long secondNum = 1;
	unsigned long result = 0;

	switch (n) {
		case 0:
			result = firstNum;
			break;
		case 1:
			result = secondNum;
			break;
		default:
			for (int i = 1; i < n; i++) {
				result = secondNum + firstNum;
				firstNum = secondNum;
				secondNum = result;
			}
			break;
	}

	return result;
}

int min_string_len(int number) {
	int res =  (int)( ceil( log10( labs(number) )) + 1 ) * sizeof(char);
	if (number < 0){
		res++;
	}

	return res;
}


char * itoa_printf(int number) {
	char * result;

	printf("minimum string len: %d\n",min_string_len(number));
	result = calloc(12, sizeof(char));
	snprintf(result, 12, "%d", number);

	return result;
}