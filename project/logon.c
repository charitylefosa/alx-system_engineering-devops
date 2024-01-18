#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_USERS 100

struct User {
    char username[50];
    char password[50];
};

// Function to read user data from a file
int readUsers(struct User users[MAX_USERS], int *numUsers) {
    FILE *file = fopen("users.txt", "r");
    if (file == NULL) {
        perror("Error opening file");
        return 0;
    }

    *numUsers = 0;
    while (*numUsers < MAX_USERS && fscanf(file, "%s %s", users[*numUsers].username, users[*numUsers].password) == 2) {
        (*numUsers)++;
    }

    fclose(file);
    return 1;
}

// Function to write user data to a file
int writeUsers(const struct User users[MAX_USERS], int numUsers) {
    FILE *file = fopen("users.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return 0;
    }

    for (int i = 0; i < numUsers; ++i) {
        fprintf(file, "%s %s\n", users[i].username, users[i].password);
    }

    fclose(file);
    return 1;
}

// Function to check if a username already exists
bool usernameExists(const struct User users[MAX_USERS], int numUsers, const char *username) {
    for (int i = 0; i < numUsers; ++i) {
        if (strcmp(users[i].username, username) == 0) {
            return true;
        }
    }
    return false;
}

// Function to register a new user
void registerUser(struct User users[MAX_USERS], int *numUsers) {
    char username[50];
    char password[50];

    printf("Enter your username: ");
    scanf("%s", username);

    if (usernameExists(users, *numUsers, username)) {
        printf("Username already exists. Please choose a different username.\n");
        return;
    }

    printf("Enter your password: ");
    scanf("%s", password);

    // Hash the password (in a real application, use a proper hashing algorithm)
    // For simplicity, we just copy the password
    strcpy(users[*numUsers].username, username);
    strcpy(users[*numUsers].password, password);

    (*numUsers)++;

    if (writeUsers(users, *numUsers)) {
        printf("Registration successful.\n");
    } else {
        printf("Error writing to file. Registration failed.\n");
    }
}

// Function to authenticate a user
bool authenticateUser(const struct User users[MAX_USERS], int numUsers, const char *username, const char *password) {
    for (int i = 0; i < numUsers; ++i) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            return true;
        }
    }
    return false;
}

// Function to log in
bool loginUser(const struct User users[MAX_USERS], int numUsers, char username[50], char password[50]) {
    printf("Enter your username: ");
    scanf("%s", username);

    printf("Enter your password: ");
    scanf("%s", password);

    return authenticateUser(users, numUsers, username, password);
}

int main() {
    struct User users[MAX_USERS];
    int numUsers = 0;

    if (!readUsers(users, &numUsers)) {
        printf("Error reading user data.\n");
        return 1;
    }

    int choice;
    char username[50];
    char password[50];

    do {
        printf("1. Login\n");
        printf("2. Register\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                if (loginUser(users, numUsers, username, password)) {
                    printf("Login successful.\n");
                    // Call your music recommendation function here
                    const char* selectedGenre = "Gospel";  // Example genre
                    recommendSong(selectedGenre, songs, numSongs);
                } else {
                    printf("Login failed. Incorrect username or password.\n");
                }
                break;
            case 2:
                registerUser(users, &numUsers);
                break;
            case 3:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 3);

    return 0;
}
