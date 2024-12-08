// C++ Guessing Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

// Class to encapsulate the Guessing Game
class GuessingGame {
private:
    int number;       // Random number to guess
    int attempts;     // Max attempts allowed
    string playerName; // Player's name

    // Function to save high scores to a file
    void saveHighScore(int attemptsUsed) {
        // Open the file in append mode to add new high scores
        ofstream outFile("guessing_game_scores.txt", ios::app);
        if (outFile.is_open()) {
            // Write the player's name and their attempts to the file
            outFile << playerName << " " << attemptsUsed << endl;
            // Close the file after writing
            outFile.close();
        }
        else {
            // Display an error if the file could not be opened
            cout << "Error: Unable to save high score.\n";
        }
    }

    // Function to display the best score from the file
    void displayBestScore() {
        // Open the file containing high scores
        ifstream inFile("guessing_game_scores.txt");
        string bestPlayer;  // Store the name of the player with the best score
        int bestScore = numeric_limits<int>::max(); // Initialize the best score to the maximum possible integer
        string currentPlayer; // Store the name of the current player being read from the file
        int currentScore;     // Store the score of the current player being read from the file

        if (inFile.is_open()) {
            // Loop through each line in the file
            while (inFile >> currentPlayer >> currentScore) {
                // If the current player's score is better (lower) than the best score
                if (currentScore < bestScore) {
                    // Update the best score and the best player
                    bestScore = currentScore;
                    bestPlayer = currentPlayer;
                }
            }
            // Close the file after reading all entries
            inFile.close();

            // If a valid best score was found, display it
            if (bestScore != numeric_limits<int>::max()) {
                cout << "High Score:\n";
                cout << "-------------------------\n";
                cout << bestPlayer << " guessed the number in " << bestScore << " attempts.\n";
                cout << "-------------------------\n";
            }
            else {
                // If no valid scores exist in the file, display a message
                cout << "No high scores available yet.\n";
            }
        }
        else {
            // If the file could not be opened, display a message
            cout << "No high scores available yet.\n";
        }
    }

public:
    // Constructor to initialize the game
    GuessingGame(int maxAttempts) : attempts(maxAttempts) {}

    // Function to play the game
    void play() {
        // Display the best score before the game starts
        displayBestScore();

        // Seed the random number generator with the current time
        srand(static_cast<int>(time(0)));
        // Generate a random number between 1 and 100
        number = rand() % 100 + 1;

        // Display welcome message and prompt the player for their name
        cout << "\nThank you for participating in the Guessing Game\n\n";
        cout << "Enter your name: ";
        cin >> playerName;

        int guess;            // Store the player's current guess
        int attemptsUsed = 0; // Track the number of attempts the player has used
        bool guessedCorrectly = false; // Track whether the player guessed the correct number

        // Loop to give the player a maximum of 'attempts' chances to guess the number
        for (int i = 0; i < attempts; i++) {
            // Increment the attempts counter
            attemptsUsed++;
            // Prompt the player to guess the number
            cout << "\nGuess the number the computer randomly picked between 1 - 100: ";
            cin >> guess;

            // Check if the guess is lower than the number
            if (guess < number) {
                cout << "Sorry, your guess is too low.\n";
            }
            // Check if the guess is higher than the number
            else if (guess > number) {
                cout << "Sorry, your guess is too high.\n";
            }
            // If the guess is correct
            else {
                cout << "\nCongratulations! You guessed the correct number: " << number << endl;
                guessedCorrectly = true; // Mark the game as won
                break; // Exit the loop since the player guessed correctly
            }
        }

        // If the player did not guess the number within the allowed attempts
        if (!guessedCorrectly) {
            cout << "\nSorry, you lost. The number is: " << number << endl;
        }

        // Save the player's score to the high scores file
        saveHighScore(attemptsUsed);
    }
};

// Main function
int main() {
    // Create a GuessingGame object with a maximum of 5 attempts
    GuessingGame game(5);
    // Start the game
    game.play();
    return 0;
}


