#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <math.h>
#include <string.h>


//riprendere l'esercizio https://github.com/marcotessarotto/esercizio-C-2020-03-30/
//calcolare fibonacci_array(39) e scrivere i valori dell'array in formato testo in un file chiamato fibonacci.txt
//se il file esiste, deve essere sovrascritto
//il programma scrive nel file un valore (in formato testo) per riga
//
//per convertire un numero intero in stringa, vedere:
//https://github.com/marcotessarotto/exOpSys/tree/master/003.2sprintf


unsigned long fibonacci(unsigned int n);
int min_string_len(unsigned long number);
char * itoa_printf(unsigned long number);


int main(int argc, char *argv[]) {
	unsigned int n = 39;

	char * file_name = "test.txt";
	printf("Leggo il file: %s\n", file_name);

	int fd = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
	if (fd == -1) {
		perror("open()");
		exit(EXIT_FAILURE);
	}
	else {
		printf("System call open() andata a buon fine!\n");
	}

	for(int i=0; i<=n; i++){
		char * text_to_write = itoa_printf(fibonacci(i));
		int text_to_write_len = strlen(text_to_write);
		char * text = malloc((text_to_write_len+1)*sizeof(char));
		text = strcat(text_to_write, "\n");

		int res = write(fd, text, text_to_write_len+1);

		if (res == -1) {
			perror("write()");
			exit(EXIT_FAILURE);
		}
	}

	printf("Scrittura su file andata a buon fine, chiusura del file...");

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


int min_string_len(unsigned long number) {
	int digits = 1;
	while (number != 0){
		number /= 10;
		digits++;
	}

	return digits;
}


char * itoa_printf(unsigned long number) {
	char * result;

	int digits = min_string_len(number);
	result = calloc(digits, sizeof(char));
	snprintf(result, digits, "%lu", number);

	return result;
}
