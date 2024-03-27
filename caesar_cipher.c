#include <stdio.h>
#include <string.h>

int main() {
    // Declaring variables
    int i, key;
    char s[1000], c;

    // Taking Input
    printf("Enter a plaintext to encrypt:\n");
    fgets(s, sizeof(s), stdin);
    printf("Enter key:\n");
    scanf("%d", &key);

    int n = strlen(s);

    // Encrypting each character according to the given key
    for (i = 0; i < n; i++) {
        c = s[i];
        if (c >= 'a' && c <= 'z') {
            c = 'a'+(c-'a'+key)%26;
            s[i] = c;

        } else if (c >= 'A' && c <= 'Z') {
        
                c = 'A'+(c-'A'+key)%26;
            s[i] = c;
        }
    }

    // Output the cipher
    printf("Encrypted message: %s\n", s);

    return 0;
}
