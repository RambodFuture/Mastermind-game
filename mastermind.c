#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>                                 //added to use isspace

#define MAX_TURNS 20
#define DIGITS 6 

int main() {
    unsigned int initSeed;
    int solution[DIGITS];                            // 1-D array for the secret code generated 
    int guess[DIGITS];                               // 1-D array for storing the guesses
    char buffer[100];                                // for users input using fgets
    int history[MAX_TURNS][DIGITS];  
    int exactMatchesHistory[MAX_TURNS];              // this is for the correct matches by user
    int partialMatchesHistory[MAX_TURNS]; 
    int turn = 0;

    printf("Enter the integer value of the seed for the game: ");
    scanf("%u", &initSeed);
    while (getchar() != '\n');

    printf("For each turn enter 6 digits 0 <= digit <= 5\n");              //Rules
    printf("Spaces or tabs in your response will be ignored.\n");

    srand(initSeed);
    for (int i = 0; i < DIGITS; i++) {                                     // this loop generates the secret number
        solution[i] = rand() % 6;
    }

    while (turn < MAX_TURNS) {
        int validGuess = 0;
        while (!validGuess) {
            printf("Enter your guess, 6 digits\n");
            fgets(buffer, 100, stdin);                                      // reads user input as a string


            int digitCount = 0;
            int i = 0;
            validGuess = 1;
            while (buffer[i] != '\n' && buffer[i] != '\0' && digitCount < DIGITS) {                         // processes each character in the input buffer
                if (isspace(buffer[i])) {
                    i++;
                } else if (buffer[i] >= '0' && buffer[i] <= '5') {
                    guess[digitCount] = buffer[i] - '0';
                    digitCount++;
                    i++;
                } else if (buffer[i] >= '6' && buffer[i] <= '9') {
                    printf("ERROR: A character in your guess was a digit that was too large\n");
                    validGuess = 0;
                    break;
                } else {
                    printf("ERROR: A character in your guess was not valid\n");
                    validGuess = 0;
                    break;
                }
            }

            if (digitCount < DIGITS && validGuess) {
                printf("You need to enter %d more digits to complete your guess\n", DIGITS - digitCount);
                validGuess = 0;
            }
        }

        int exactMatches = 0;
        int partialMatches = 0;
        int solutionUsed[DIGITS] = {0};
        int guessUsed[DIGITS] = {0};

        for (int i = 0; i < DIGITS; i++) {
            if (guess[i] == solution[i]) {
                exactMatches++;
                solutionUsed[i] = 1;
                guessUsed[i] = 1;
            }
        }

        for (int i = 0; i < DIGITS; i++) {
            if (!guessUsed[i]) {
                for (int j = 0; j < DIGITS; j++) {
                    if (!solutionUsed[j] && guess[i] == solution[j]) {
                        partialMatches++;
                        solutionUsed[j] = 1;
                        break;
                    }
                }
            }
        }

        exactMatchesHistory[turn] = exactMatches;
        partialMatchesHistory[turn] = partialMatches;
        for (int i = 0; i < DIGITS; i++) {
            history[turn][i] = guess[i];
        }

        for (int t = 0; t <= turn; t++) {
            printf("Previous guess %d: ", t + 1);
            for (int i = 0; i < DIGITS; i++) {
                printf("%d ", history[t][i]);
            }
            printf("- %d matches %d partial matches\n", exactMatchesHistory[t], partialMatchesHistory[t]);
        }

        printf("%d matches %d partial matches\n", exactMatches, partialMatches);
        if (exactMatches == DIGITS) {
            printf("YOU DID IT!!\n");
            break;
        }

        turn++;
    }

    if (turn == MAX_TURNS) {
        printf("Game over! You have used all %d turns.\n", MAX_TURNS);           // this wasnt mentioned in the assignment
    }

    return 0;
}
