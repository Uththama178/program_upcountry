#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>

using namespace std;

// Maximum number of players the system can handle
const int MAX_PLAYERS = 100;

// Player structure to store player details
struct Player {
    char registrationNumber[10];
    char firstName[50];
    char lastName[50];
    char dateOfBirth[15];
    int runsScored;
    char team1[50];
    char team2[50];
};

// Array to store players and a counter to keep track of the number of players
Player players[MAX_PLAYERS];
int playerCount = 0;

// Function prototypes
void loadPlayers();
void savePlayers();
bool login();
void displayPlayers();
void addPlayer();
void manageTeams();
void searchPlayers();
void viewTeamDetails();
void splitName(const char* fullName, char* firstName, char* lastName);

// Function to load player data from file
void loadPlayers() {
    ifstream file("players.txt"); // Open the file for reading
    if (!file) {
        cerr << "Error opening file!" << endl;
        return;
    }
    playerCount = 0;
    while (file >> players[playerCount].registrationNumber) { // Read registration number
        file.ignore(); // ignore comma
        file.getline(players[playerCount].firstName, 50, ','); // Read first name
        file.getline(players[playerCount].lastName, 50, ','); // Read last name
        file.getline(players[playerCount].dateOfBirth, 15, ','); // Read date of birth
        file >> players[playerCount].runsScored; // Read runs scored
        file.ignore(); // ignore comma
        file.getline(players[playerCount].team1, 50, ','); // Read first team
        file.getline(players[playerCount].team2, 50); // Read second team
        playerCount++; // Increment player count
    }
    file.close(); // Close the file
}

// Function to save player data to file
void savePlayers() {
    ofstream file("players.txt"); // Open the file for reading
    if (!file) {
        cerr << "Error opening file!" << endl;
        return;
    }
    for (int i = 0; i < playerCount; i++) {
        file << players[i].registrationNumber << ","
             << players[i].firstName << ","
             << players[i].lastName << ","
             << players[i].dateOfBirth << ","
             << players[i].runsScored << ","
             << players[i].team1 << ","
             << players[i].team2 << "\n";
    }
    file.close(); // Close the file
}

// Function to handle login
bool login() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    // Simple authentication using predefined username and password
    if (username == "Uththama" && password == "1234") {
        return true;
    } else {
        cout << "Invalid login credentials!\n";
        return false;
    }
}

// Function to display all players
void displayPlayers() {
    // Print table headers
    cout << left << setw(15) << "Reg No" << setw(15) << "First Name" << setw(15) << "Last Name"
         << setw(15) << "DOB" << setw(10) << "Runs" << setw(15) << "Team 1" << setw(15) << "Team 2" << endl;
    cout << string(95, '-') << endl;
    // Print each player's information
    for (int i = 0; i < playerCount; i++) {
        cout << left << setw(15) << players[i].registrationNumber << setw(15) << players[i].firstName << setw(15) << players[i].lastName
             << setw(15) << players[i].dateOfBirth << setw(10) << players[i].runsScored << setw(15) << players[i].team1 << setw(15) << players[i].team2 << endl;
    }
}

// Function to add a new player
void addPlayer() {
    if (playerCount >= MAX_PLAYERS) {
        cout << "Player limit reached. Cannot add more players.\n";
        return;
    }
    Player player;
    cout << "Enter registration number: ";
    cin >> player.registrationNumber;
    char fullName[100];
    cout << "Enter full name: ";
    cin.ignore();
    cin.getline(fullName, 100);
    splitName(fullName, player.firstName, player.lastName);
    cout << "Enter date of birth (yyyy.mm.dd): ";
    cin >> player.dateOfBirth;
    cout << "Enter runs scored: ";
    cin >> player.runsScored;
    cout << "Enter first team: ";
    cin >> player.team1;
    cout << "Enter second team (if any, else enter 'none'): ";
    cin >> player.team2;
    if (strcmp(player.team2, "none") == 0) strcpy(player.team2, "");

    players[playerCount] = player;
    playerCount++;
    savePlayers(); // Save updated player list to file
}

// Helper function to split full name into first name and last name
void splitName(const char* fullName, char* firstName, char* lastName) {
    const char* space = strchr(fullName, ' ');
    if (space != nullptr) {
        strncpy(firstName, fullName, space - fullName);
        firstName[space - fullName] = '\0';
        strcpy(lastName, space + 1);
    } else {
        strcpy(firstName, fullName);
        strcpy(lastName, "");
    }
}

// Function to manage teams (placeholder)
void manageTeams() {
    cout << "Team management feature not yet implemented.\n";
}

// Function to search for a player by registration number
void searchPlayers() {
    char regNo[10];
    cout << "Enter player registration number to search: ";
    cin >> regNo;

    bool found = false;
    for (int i = 0; i < playerCount; i++) {
        if (strcmp(players[i].registrationNumber, regNo) == 0) {
            cout << "Player found:\n";
            cout << "Registration Number: " << players[i].registrationNumber << "\n"
                 << "First Name: " << players[i].firstName << "\n"
                 << "Last Name: " << players[i].lastName << "\n"
                 << "Date of Birth: " << players[i].dateOfBirth << "\n"
                 << "Runs Scored: " << players[i].runsScored << "\n"
                 << "Team 1: " << players[i].team1 << "\n"
                 << "Team 2: " << players[i].team2 << "\n";
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Player not found.\n";
    }
}

// Function to view team details
void viewTeamDetails() {
    char teamName[50];
    cout << "Enter team name to view details: ";
    cin >> teamName;

    bool found = false;
    for (int i = 0; i < playerCount; i++) {
        if (strcmp(players[i].team1, teamName) == 0 || strcmp(players[i].team2, teamName) == 0) {
            if (!found) {
                cout << "Team members of " << teamName << ":\n";
                found = true;
            }
            cout << "Registration Number: " << players[i].registrationNumber << "\n"
                 << "First Name: " << players[i].firstName << "\n"
                 << "Last Name: " << players[i].lastName << "\n"
                 << "Date of Birth: " << players[i].dateOfBirth << "\n"
                 << "Runs Scored: " << players[i].runsScored << "\n";
        }
    }
    if (!found) {
        cout << "No players found in team " << teamName << ".\n";
    }
}

int main() {
    loadPlayers(); // Load player data from file

    // Login loop
    while (!login()) {
        cout << "Please try logging in again.\n";
    }

    int choice;
    do {
        // Display menu
        cout << "\nMenu:\n"
             << "1. Display players information\n"
             << "2. Add new players\n"
             << "3. Manage teams\n"
             << "4. Search players\n"
             << "5. View Team Details\n"
             << "6. Logout\n"
             << "7. Exit\n"
             << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayPlayers();
                break;
            case 2:
                addPlayer();
                break;
            case 3:
                manageTeams();
                break;
            case 4:
                searchPlayers();
                break;
            case 5:
                viewTeamDetails();
                break;
            case 6:
                cout << "Logged out successfully.\n";
                // Re-login loop
                while (!login()) {
                    cout << "Please try logging in again.\n";
                }
                break;
            case 7:
                cout << "Exiting the program.\n";
                break;
            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}
