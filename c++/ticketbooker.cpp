#include <iostream>
#include <ctime>
#include <string>
#include <unistd.h>

using namespace std;

// Functions We Created
void ticket_booker(string seats[9][5]); // For Booking seats
void display_booked(string seats[9][5]); // For displaying your booked seats
void bill(int ticket_count); // For displaying Bill

// Global Variables
string seatsArray[9][5]; // Renamed to avoid ambiguity
string booked = "XX";
int ticket_count;

// Main function
int main() { 
    // Initialize the array to empty strings
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 5; j++) {
            seatsArray[i][j] = "  ";
        }
    }

    cout << endl;
    cout << "|--------------------------------------*|" << endl;
    cout << "|------------* Ticket Booker ------------*|" << endl;
    cout << "|--------------------------------------*|" << endl;
       
    ticket_booker(seatsArray);
    display_booked(seatsArray);
    bill(ticket_count);

    return 0;
}

// For booking seats
void ticket_booker(string seats[9][5])
{
    srand(time(0));  
    cout << endl;

    for (int i = 0; i < 9; i++) {
        cout << i + 1 << ".  ";
        for (int j = 0; j < 5; j++) {
            int ran1 = rand() % 9 + 1;
            int ran2 = rand() % 5 + 1;
            if (i + 1 == ran1 && j + 1 == ran2) {
                seats[i][j] = booked;
                cout << "\033[31m" << booked << " " << "\033[0m"; // Red for booked seats
            } else {
                seats[i][j] = string(1, char(i + 65));
                
                cout << "\033[32m" << seats[i][j] << j + 1 << " " << "\033[0m"; // Green for available seats
            }  
        }
        cout << endl;
    }

    cout << endl << "Note :- \n 1. You can only book the tickets which are green in color. \n 2. Seats with XX sign are already booked." << endl;
    cout << endl << endl;

    int rn, cn;
    do { 
        cout << "\033[33m" << "How many tickets do you want to book?:" << "\033[0m";
        cin >> ticket_count;
        if (ticket_count <= 0) cout << "\033[33m"<< "Tickets cannot be zero or negative !" << "\033[0m" << endl;
    } while (ticket_count <= 0);

    for (int i = 0; i < ticket_count; i++) {
        do {
            cout << "Enter row number for ticket no " << i + 1 << " : ";
            cin >> rn;
            cout << "Enter column number : ";
            cin >> cn;

            if (rn <= 0 || rn > 9 || cn <= 0 || cn > 5) {
                cout << "\033[33m"<< "Please enter a valid seat !" << "\033[0m" << endl;
            } else if (seats[rn - 1][cn - 1] == "XX") {
                cout << "\033[33m" << "Selected seat is already booked !" << "\033[0m" << endl; // Yellow for errors
            } else {
                seats[rn - 1][cn - 1] = booked;
                break; // Exit the do-while loop after successfully booking a seat
            }
        } while (true); // Keep looping until a valid seat is booked
    }

    cout << endl << "\033[33m" << "Booking Tickets !" << "\033[0m" << endl;
    sleep(2);
    cout << "\033[32m" << "Tickets Booked Successfully !" << "\033[0m" << endl;

    cout << endl << endl;
}

// For displaying your booked seats
void display_booked(string seats[9][5])
{ 
    for (int i = 0; i < 9; i++) {
        cout << i + 1 << ".  ";
        for (int j = 0; j < 5; j++) {
            if (seats[i][j] == booked) {
                cout << "\033[31m" << seats[i][j] << " " << "\033[0m"; // Red for booked seats
            } else {
                cout << "\033[32m" << seats[i][j] << j + 1 << " " << "\033[0m"; // Green for available seats
            }
        }
        cout << endl;
    }
    cout << endl << endl;
}

// For displaying Bill
void bill(int ticket_count)
{
    cout << endl;
    cout << " Bill :" << endl << endl;
    cout << "*" << endl;
    cout << "*      Booking Summary      *" << endl;
    cout << "*" << endl;
    cout << "* Item         |       Amount*" << endl;
    cout << "---------------------------" << endl;
    cout << "" << "\033[33m" << "Tickets booked:" << "\t\t" << ticket_count << "\033[0m" << "" << endl;
    cout << "" << "\033[31m" << "Total Amount:" << "\t      " << ticket_count * 15 << "$" << "\033[0m" << "" << endl;
    cout << "*" << endl;
    cout << "Thank you for your booking!" << endl;
    cout << "*" << endl;
}