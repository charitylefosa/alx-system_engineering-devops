#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Define a structure for a Song
struct Song {
    char title[50];
    char artist[50];
    char genre[20];
};

// Function to recommend a song based on the selected genre
void recommendSong(const char* selectedGenre, const struct Song* songs, int numSongs) {
    // Create an array to store recommended songs
    struct Song recommendedSongs[5];
    int recommendedCount = 0;

    // Loop through the songs to find recommendations
    for (int i = 0; i < numSongs; ++i) {
        if (strcmp(songs[i].genre, selectedGenre) == 0) {
            recommendedSongs[recommendedCount] = songs[i];
            recommendedCount++;

            // Limit the number of recommendations to 5
            if (recommendedCount == 5) {
                break;
            }
        }
    }

    // Display recommended songs
    printf("Recommended Songs in %s:\n", selectedGenre);
    for (int i = 0; i < recommendedCount; ++i) {
        printf("%d. %s - %s\n", i + 1, recommendedSongs[i].title, recommendedSongs[i].artist);
    }
}

int main() {
    // Seed the random number generator for variety in recommendations
    srand(time(NULL));

    // Define an array of sample songs
    struct Song songs[] = {
        {"I love you Lord", "Artist1", "Gospel"},
        {"Song2", "Artist2", "Amapiano"},
        {"Song3", "Artist3", "Jazz"},
        {"Song4", "Artist4", "R&B"},
        // Add more songs as needed
    };

    int numSongs = sizeof(songs) / sizeof(songs[0]);

    // Simulate user selecting a genre (for simplicity)
    const char* selectedGenre = "Gospel";

    // Recommend a song based on the selected genre
    recommendSong(selectedGenre, songs, numSongs);

    return 0;
}

