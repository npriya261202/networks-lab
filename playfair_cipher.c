#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

// Structure to hold the coordinates of a letter in the table
struct Point {
    int x;
    int y;
};

// Function prototypes
void parseString(char *str);
void initializeTable(char *key, char table[SIZE][SIZE]);
void printTable(char table[SIZE][SIZE]);
struct Point findPosition(char letter, char table[SIZE][SIZE]);
char* cipher(char *input, char table[SIZE][SIZE]);
char* decode(char *input, char table[SIZE][SIZE]);
void printResults(char *output, char *decodedOutput);

int main() {
    char key[100];
    printf("Enter the key for playfair cipher: ");
    fgets(key, sizeof(key), stdin);
    parseString(key);

    char table[SIZE][SIZE];
    initializeTable(key, table);

    char input[100];
    printf("Enter the plaintext to be encipher: ");
    fgets(input, sizeof(input), stdin);
    parseString(input);

    char *output = cipher(input, table);
    char *decodedOutput = decode(output, table);

    printTable(table);
    printResults(output, decodedOutput);

    return 0;
}

void parseString(char *str) {
    int i, j = 0;
    for (i = 0; str[i] != '\0'; i++) {
        if (isalpha(str[i])) {
            str[j++] = toupper(str[i]);
        }
    }
    str[j] = '\0';
}

void initializeTable(char *key, char table[SIZE][SIZE]) {
    // Initialize the table with zeros
    memset(table, 0, sizeof(table[0][0]) * SIZE * SIZE);

    // Fill the table with the key
    int len = strlen(key);
    int i, j, k;
    int used[26] = {0};

    for (i = 0, k = 0; k < len; k++) {
        if (key[k] == 'J') key[k] = 'I';

        if (!used[key[k] - 'A']) {
            table[i / SIZE][i % SIZE] = key[k];
            used[key[k] - 'A'] = 1;
            i++;
        }
    }

    // Fill the rest of the table with the remaining alphabet
    for (j = 0; j < 26; j++) {
        if (j != ('J' - 'A') && !used[j]) {
            table[i / SIZE][i % SIZE] = 'A' + j;
            i++;
        }
    }
}

void printTable(char table[SIZE][SIZE]) {
    printf("Playfair Cipher Table:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", table[i][j]);
        }
        printf("\n");
    }
}

struct Point findPosition(char letter, char table[SIZE][SIZE]) {
    struct Point pos = {-1, -1};
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (table[i][j] == letter) {
                printf("Found position of '%c' at (%d, %d)\n", letter, i, j);
                pos.x = i;
                pos.y = j;
                return pos;
            }
        }
    }
    return pos;
}


char* cipher(char *input, char table[SIZE][SIZE]) {
    int len = strlen(input);
    static char output[100];
    int k = 0;

    for (int i = 0; i < len; i += 2) {
        char a = input[i];
        char b = (i + 1 < len) ? input[i + 1] : 'X';

        if (a == b) {
            b = 'X';
            i--;
        }

        struct Point posA = findPosition(a, table);
        struct Point posB = findPosition(b, table);

        if (posA.x == posB.x) {
            output[k++] = table[posA.x][(posA.y + 1) % SIZE];
            output[k++] = table[posB.x][(posB.y + 1) % SIZE];
        } else if (posA.y == posB.y) {
            output[k++] = table[(posA.x + 1) % SIZE][posA.y];
            output[k++] = table[(posB.x + 1) % SIZE][posB.y];
        } else {
            output[k++] = table[posA.x][posB.y];
            output[k++] = table[posB.x][posA.y];
        }
    }
    output[k] = '\0';
    return output;
}

char* decode(char *input, char table[SIZE][SIZE]) {
    static char decodedOutput[100];
    int len = strlen(input);
    int k = 0;

    for (int i = 0; i < len; i += 2) {
        char a = input[i];
        char b = input[i + 1];

        struct Point posA = findPosition(a, table);
        struct Point posB = findPosition(b, table);

        if (posA.x == posB.x) {
            decodedOutput[k++] = table[posA.x][(posA.y - 1 + SIZE) % SIZE];
            decodedOutput[k++] = table[posB.x][(posB.y - 1 + SIZE) % SIZE];
        } else if (posA.y == posB.y) {
            decodedOutput[k++] = table[(posA.x - 1 + SIZE) % SIZE][posA.y];
            decodedOutput[k++] = table[(posB.x - 1 + SIZE) % SIZE][posB.y];
        } else {
            decodedOutput[k++] = table[posA.x][posB.y];
            decodedOutput[k++] = table[posB.x][posA.y];
        }
    }

    // Remove any 'X' characters introduced as filler during encryption
    // and preserve 'X' characters from the original plaintext
    int j = 0;
    for (int i = 0; i < k; i++) {
        if (decodedOutput[i] != 'X' && isalpha(decodedOutput[i])) {
            decodedOutput[j++] = decodedOutput[i];
        }
    }
    decodedOutput[j] = '\0';

    return decodedOutput;
}



void printResults(char *output, char *decodedOutput) {
    printf("Encrypted Text: %s\n", output);
    printf("Decrypted Text: %s\n", decodedOutput);
}
