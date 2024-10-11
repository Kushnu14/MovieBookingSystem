#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class MovieBookingSystem {
private:
    int rows;
    int cols;
    char** seats; // Dynamic 2D array for seating arrangement
    const string filename = "booking_data.txt";

public:
    MovieBookingSystem(int r = 5, int c = 5) : rows(r), cols(c) {
        seats = new char*[rows];
        for (int i = 0; i < rows; i++) {
            seats[i] = new char[cols];
            for (int j = 0; j < cols; j++) {
                seats[i][j] = 'O'; // 'O' indicates the seat is vacant
            }
        }
        loadBookingData();
    }

    // Destructor to clean up dynamic memory
    ~MovieBookingSystem() {
        for (int i = 0; i < rows; i++) {
            delete[] seats[i];
        }
        delete[] seats;
    }

    void displaySeats() {
        cout << "Seating Arrangement (O: Vacant, X: Booked)\n";
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << seats[i][j] << " ";
            }
            cout << endl;
        }
    }

    void bookSeat(int row, int col) {
        if (row >= 0 && row < rows && col >= 0 && col < cols) {
            if (seats[row][col] == 'O') {
                seats[row][col] = 'X'; // Mark seat as booked
                cout << "Seat (" << row + 1 << ", " << col + 1 << ") booked successfully!" << endl;
            } else {
                cout << "Seat is already booked!" << endl;
            }
        } else {
            cout << "Invalid seat number!" << endl;
        }
    }

    void saveBookingData() {
        ofstream outFile(filename);
        if (outFile.is_open()) {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    outFile << seats[i][j] << " ";
                }
                outFile << endl;
            }
            outFile.close();
            cout << "Booking data saved!" << endl;
        } else {
            cout << "Unable to save booking data!" << endl;
        }
    }

    void loadBookingData() {
        ifstream inFile(filename);
        if (inFile.is_open()) {
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) {
                    inFile >> seats[i][j];
                }
            }
            inFile.close();
        } else {
            cout << "No existing booking data found. Starting fresh!" << endl;
        }
    }
};

int main() {
    MovieBookingSystem mbs;

    int choice, row, col;
    do {
        cout << "\nMovie Booking System Menu:\n";
        cout << "1. Display Seats\n";
        cout << "2. Book a Seat\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                mbs.displaySeats();
                break;
            case 2:
                cout << "Enter row and column to book (1-5): ";
                cin >> row >> col;
                mbs.bookSeat(row - 1, col - 1);
                break;
            case 3:
                mbs.saveBookingData();
                cout << "Exiting system. Goodbye!\n";
                break;
            default:
                cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 3);

    return 0;
}
