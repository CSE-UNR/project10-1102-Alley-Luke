//Luke Alley

#include <stdio.h>

void loadWord(char target[]);
void printPrompt(int guessNum);
void getGuess(char buffer[]);
int getLength(char str[]);
void makeLowercase(char str[]);
int isValid(char str[]);
int findLetter(char c, char target[]);
void displayGuesses(char guesses[][6], int num_guesses, char target[]);
int isWin(char guess[], char target[]);

int main() {
	char target[6];
	loadWord(target);
	makeLowercase(target);
	
	char guesses[6][6];
	int num_guesses = 0;
	int won = 0;
	
	while (num_guesses < 6 && !won) {
		char buffer[100];
		
		printPrompt(num_guesses + 1);
		getGuess(buffer);
		
		while (!isValid(buffer)) {
			printPrompt(num_guesses + 1);
			getGuess(buffer);
		}
		
		makeLowercase(buffer);
		
		for (int i = 0; i < 6; i++) {
			guesses[num_guesses][i] = buffer[i];
		}
		
		num_guesses++;
		
		printf("===================================\n");
		
		if (isWin(guesses[num_guesses - 1], target)) {
			won = 1;
			
			printf("               ");
			for (int i = 0; i < 5; i++) {
				printf("%c", guesses[num_guesses - 1][i] - ('a' - 'A'));
			}
			printf("\n");
			
			printf("	You won in %d guesses!\n", num_guesses);
			printf("		Amazing!\n");
		} else {
			displayGuesses(guesses, num_guesses, target);
			
			if (num_guesses == 6) {
				printf("You lost, better luck next time!\n");
			}
		}
	}
	
	return 0;
}

void loadWord(char target[]) {
	FILE *file = fopen("word.txt", "r");
	if (file != NULL) {
		fscanf(file, "%5s", target);
		fclose(file);
	} else {
		target[0] = 's'; target[1] = 'o'; target[2] = 'u'; target[3] = 'n'; target[4] = 'd'; target[5] = '\0';
	}
}

void printPrompt(int guessNum) {
	if (guessNum < 6) {
		printf("GUESS %d! Enter your guess: ", guessNum);
	} else {
		printf("FINAL GUESS: ");
	}
}

void getGuess(char buffer[]) {
	int i = 0;
	int c;
	while ((c = getchar()) != '\n' && c != EOF) {
		if (i < 99) {
			buffer[i] = (char)c;
			i++;
		}
	}
	buffer[i] = '\0';
}

int getLength(char str[]) {
	int len = 0;
	while (str[len] != '\0') {
		len++;
	}
	return len;
}

void makeLowercase(char str[]) {
	for (int i = 0; str[i] != '\0'; i++) {
		if (str[i] >= 'A' && str[i] <= 'Z') {
			str[i] = str[i] + ('a' - 'A');
		}
	}
}

int isValid(char str[]) {
	if (getLength(str) !=5) {
		return 0;
	}
	for (int i = 0; i < 5; i++) {
		int isLower = (str[i] >= 'a' && str[i] <= 'z');
		int isUpper = (str[i] >= 'A' && str[i] <= 'Z');
		if (!isLower && !isUpper) {
			return 0;
		}
	}
	return 1;
}

int findLetter(char c, char target[]) {
	for (int i = 0; i < 5; i++) {
		if (target[i] == c) {
			return i;
		}
	}
	return -1;
}

void displayGuesses(char guesses[][6], int num_guesses, char target[]) {
	for (int g = 0; g < num_guesses; g++) {
		
		for (int i = 0; i < 5; i++) {
			if (guesses[g][i] == target[i]) {
				printf("%c", guesses[g][i] - ('a' - 'A'));
			} else {
				printf("%c", guesses[g][i]);
			}
		}
		printf("\n");
		
		for (int i = 0; i < 5; i++) {
			if (guesses[g][i] == target[i]) {
				printf(" ");
			} else {
				int target_idx = findLetter(guesses[g][i], target);
				if (target_idx != -1) {
					if (guesses[g][target_idx] == target[target_idx]) {
						printf(" ");
					} else {
						printf("^");
					}
				} else {
					printf(" ");
				}
			}
		}
		printf("\n");
	}
}

int isWin(char guess[], char target[]) {
	for (int i = 0; i < 5; i++) {
		if (guess[i] != target[i]) {
			return 0;
		}
	}
	return 1;
}
