#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// Function to encrypt the message
void encrypt(string &plaintext, const string &key) {
    for (char &c : plaintext) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            c = key[c - base];
        }
    }
}

// Function to decrypt the message
void decrypt(string &ciphertext, const string &key) {
    for (char &c : ciphertext) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            auto pos = key.find(c);
            if (pos != string::npos) {
                c = base + pos;
            }
        }
    }
}

int main() {
    string plaintext;
    string key;
    string ciphertext;
    string decrypted;

    // Input plaintext from user
    cout << "Enter the plaintext: ";
    getline(cin, plaintext);

    // Input key from user
    cout << "Enter the key: ";
    getline(cin, key);

    // Encrypt the plaintext
    ciphertext = plaintext;
    encrypt(ciphertext, key);
    cout << "Ciphertext: " << ciphertext << endl;

    // Decrypt the ciphertext
    decrypted = ciphertext;
    decrypt(decrypted, key);
    cout << "Decrypted plaintext: " << decrypted << endl;

    return 0;
}
