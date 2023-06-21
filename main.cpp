#include <iostream>
#include <string>
#include <conio.h>
#include "Admin.h"
#include "Train.h"
#include "Passenger.h"

using namespace std;

int main (){
    while (true){
        Admin myAdmin;
        int login=myAdmin.login();
        // succesfull admin login -> login = 1
        // succesfull user login -> login = 2
        // unsuccesfull login -> login = 3
        // no admin account -> login = 4
        // exit system -> login = 0
        while (login == 1){
            system("cls");
            cout<<"\n\n\t\tRailway Reservation System"
                  "\n\t\tAdmin Menu"
                  "\n\n\t\t1. Train Menu"
                  "\n\t\t2. Passenger Menu"
                  "\n\t\t3. Change Password"
                  "\n\t\t4. Main Menu"
                  "\n\t\t0. Exit System"
                  "\n\n\t\tChoose an option: ";
            char ch = _getch();
            fflush(stdin);
            int response = ch - '0';
            while(response != 1 && response != 2 && response != 3 && response != 4 && response != 0){
                cout<<"\n\t\tInvalid option. Please try again: ";
                ch = _getch();
                fflush(stdin);
                response = ch - '0';
            }

            while(response == 1){
                system ("cls");
                cout<<"\n\n\t\tRailway Reservation System"
                      "\n\t\tTrain Menu"
                      "\n\n\t\t1. Show Trains"
                      "\n\t\t2. Add Train"
                      "\n\t\t3. Delete Train"
                      "\n\t\t4. Change Train"
                      "\n\t\t5. Previous Menu"
                      "\n\t\t6. Main Menu"
                      "\n\t\t0. Exit System"
                      "\n\n\t\tChoose an option: ";
                char ch2 = _getch();
                fflush(stdin);
                int response2 = ch2 - '0';
                while (response2 != 1 && response2 != 2 && response2 != 3 && response2 != 4 &&
                       response2 != 5 && response2 != 6 && response2 != 0){
                    cout<<"\n\t\tInvalid option. Please try again: ";
                    ch2 = _getch();
                    fflush(stdin);
                    response2 = ch2 - '0';
                }
                while (response2 == 1){
                    system ("cls");
                    cout<<"\n\n\t\tRailway Reservation System"
                          "\n\t\tShow Trains Menu";
                    Train myTrain;
                    try {
                        myTrain.readInformation();
                    }
                    catch (invalid_argument &e){
                        cerr<<"\n\n\t\tError while reading train information: "<<e.what();
                    }
                    myTrain.printInformation();

                    cout<<"Press any key to continue...";
                    _getch();
                    break;
                }
                while (response2 == 2){
                    system ("cls");
                    cout<<"\n\n\t\tRailway Reservation System"
                          "\n\t\tAdd Train Menu";
                    int trainId = 0;
                    cout<<"\n\t\tEnter the train id:";
                    cin>>trainId;

                    int trainSeat = 0;
                    cout<<"\n\t\tEnter the train seat:";
                    cin>>trainSeat;

                    string trainName;
                    cout<<"\n\t\tEnter the train name:";
                    cin>>trainName;

                    string trainDepartureDate;
                    cout<<"\n\t\tEnter the train departure date(DD/MM/YYYY):";
                    cin>>trainDepartureDate;

                    int day = stoi(trainDepartureDate.substr(0,2));
                    int month = stoi(trainDepartureDate.substr(3,2));
                    int year = stoi(trainDepartureDate.substr(6,4));

                    string trainDepartureTime;
                    cout<<"\n\t\tEnter the train departure time(MM:HH):";
                    cin>>trainDepartureTime;

                    int hour = stoi(trainDepartureTime.substr(0,2));
                    int minute = stoi(trainDepartureTime.substr(3,2));

                    bool check = false;
                    try {
                        Train myTrain(trainId, trainSeat, trainName, year, month, day, hour, minute);
                        try {
                            check = myTrain.addTrainToDatabase(trainId, trainSeat, trainName, year, month, day, hour, minute);
                        }
                        catch (invalid_argument &e){
                            cerr<<"\n\n\t\tError while writing train information: "<<e.what();
                        }
                    }
                    catch (invalid_argument &e){
                        cerr<<"\n\n\t\tError while creating train object: "<<e.what();
                    }

                    if (check){
                        cout<<"\n\t\tTrain added successfully.";
                    }
                    else {
                        cout<<"\n\t\tTrain could not be added.";
                    }

                    cout<<"\n\n\t\tDo you want to add another train? (Y/N): ";
                    char ch3 = _getch();
                    fflush(stdin);
                    while (ch3 != 'Y' && ch3 != 'y' && ch3 != 'N' && ch3 != 'n'){
                        cout<<"\n\t\tInvalid option. Please try again: ";
                        ch3 = _getch();
                        fflush(stdin);
                    }
                    if (ch3 == 'n' || ch3 == 'N')
                        break;
                }
                while (response2 == 3){
                    system ("cls");
                    cout<<"\n\n\t\tRailway Reservation System"
                          "\n\t\tDelete Train Menu";
                    int trainId = 0;
                    cout<<"\n\t\tEnter the train id which you want to delete:";
                    cin>>trainId;

                    bool check = false;
                    try {
                        Train myTrain;
                        try {
                            check = myTrain.deleteTrainFromDatabase(trainId);
                        }
                        catch (invalid_argument &e){
                            cerr<<"\n\n\t\tError while deleting train information: "<<e.what();
                        }
                    }
                    catch (invalid_argument &e){
                        cerr<<"\n\n\t\tError while creating train object: "<<e.what();
                    }

                    if (check){
                        cout<<"\n\t\tTrain deleted successfully.";
                    }
                    else {
                        cout<<"\n\t\tTrain could not be deleted.";
                    }

                    cout<<"\n\n\t\tDo you want to delete another train? (Y/N): ";
                    char ch3 = _getch();
                    fflush(stdin);
                    while (ch3 != 'Y' && ch3 != 'y' && ch3 != 'N' && ch3 != 'n'){
                        cout<<"\n\t\tInvalid option. Please try again: ";
                        ch3 = _getch();
                        fflush(stdin);
                    }
                    if (ch3 == 'n' || ch3 == 'N')
                        break;
                }
                while (response2 == 4){
                    system("cls");
                    cout<<"\n\n\t\tRailway Reservation System"
                          "\n\t\tChange Train Menu";

                    int trainId = 0;
                    cout<<"\n\t\tEnter the train id which you want to change:";
                    cin>>trainId;

                    int newTrainId = 0;
                    cout<<"\n\t\tEnter the new train id(Enter -1 if you don't want to change):";
                    cin>>newTrainId;

                    int newTrainSeat = 0;
                    cout<<"\n\t\tEnter the new train seat(Enter -1 if you don't want to change):";
                    cin>>newTrainSeat;

                    string newTrainName;
                    cout<<"\n\t\tEnter the new train name(Enter -1 if you don't want to change):";
                    cin>>newTrainName;
                    if (newTrainName == "-1")
                        newTrainName = "";

                    string newTrainDepartureDate;
                    cout<<"\n\t\tEnter the new train departure date(DD/MM/YYYY)(Enter -1 if you don't want to change):";
                    cin>>newTrainDepartureDate;

                    int year = 0;
                    int month = 0;
                    int day = 0;
                    if (newTrainDepartureDate == "-1"){
                        year = -1;
                        month = -1;
                        day = -1;
                    }
                    else{
                        day = stoi(newTrainDepartureDate.substr(0,2));
                        month = stoi(newTrainDepartureDate.substr(3,2));
                        year = stoi(newTrainDepartureDate.substr(6,4));
                    }

                    string newTrainDepartureTime;
                    cout<<"\n\t\tEnter the new train departure time(MM:HH)(Enter -1 if you don't want to change):";
                    cin>>newTrainDepartureTime;

                    int hour = 0;
                    int minute = 0;
                    if (newTrainDepartureTime == "-1"){
                        hour = -1;
                        minute = -1;
                    }
                    else{
                        hour = stoi(newTrainDepartureTime.substr(0,2));
                        minute = stoi(newTrainDepartureTime.substr(3,2));
                    }

                    bool check = false;
                    try {
                        Train myTrain;
                        try {
                            check = myTrain.changeTrainInformationInDatabase(trainId, newTrainSeat,
                                                                             newTrainName, year, month, day, hour,
                                                                             minute, newTrainId);
                        }
                        catch (invalid_argument &e){
                            cerr<<"\n\n\t\tError while changing train information: "<<e.what();
                        }
                    }
                    catch (invalid_argument &e){
                        cerr<<"\n\n\t\tError while creating train object: "<<e.what();
                    }

                    if (check){
                        cout<<"\n\t\tTrain changed successfully.";
                    }
                    else {
                        cout<<"\n\t\tTrain could not be changed.";
                    }

                    cout<<"\n\n\t\tDo you want to change another train? (Y/N): ";
                    char ch3 = _getch();
                    fflush(stdin);
                    while (ch3 != 'Y' && ch3 != 'y' && ch3 != 'N' && ch3 != 'n'){
                        cout<<"\n\t\tInvalid option. Please try again: ";
                        ch3 = _getch();
                        fflush(stdin);
                    }
                    if (ch3 == 'n' || ch3 == 'N')
                        break;
                }
                while (response2 == 5){
                    response = -1;
                    break;
                }
                while (response2 == 6){
                    response = 4;
                    break;
                }
                while (response2 == 0){
                    response = 0;
                    break;
                }
            }
            while(response == 2){
                system("cls");
                cout<<"\n\n\t\tRailway Reservation System"
                      "\n\t\tPassenger Menu"
                      "\n\n\t\t1. Show Passengers"
                      "\n\n\t\t2. Add Passenger"
                      "\n\t\t3. Delete Passenger"
                      "\n\t\t4. Change Passenger"
                      "\n\t\t5. Previous Menu"
                      "\n\t\t6. Main Menu"
                      "\n\t\t0. Exit System"
                      "\n\n\t\tChoose an option: ";
                char ch2 = _getch();
                fflush(stdin);
                int response2 = ch2 - '0';
                while (response2 != 1 && response2 != 2 && response2 != 3 && response2 != 4 &&
                       response2 != 5 && response2 != 6 && response2 != 0){
                    cout<<"\n\t\tInvalid option. Please try again: ";
                    ch2 = _getch();
                    fflush(stdin);
                    response2 = ch2 - '0';
                }
                while (response2 == 1){
                    system("cls");
                    cout<<"\n\n\t\tRailway Reservation System"
                          "\n\t\tShow Passengers Menu";
                    int trainId = 0;
                    cout<<"\n\t\tEnter the train id:";
                    cin>>trainId;
                    Passenger myPassenger;
                    try {
                        myPassenger.readPassengerInformation(trainId);
                    }
                    catch (invalid_argument &e){
                        cerr<<"\n\n\t\tError while reading passenger information: "<<e.what();
                    }
                    myPassenger.printPassengerInformation(trainId);

                    cout<<"Do you want to see passengers of another train? (y/n)";
                    char ch3 = _getch();
                    fflush(stdin);
                    while (ch3 != 'y' && ch3 != 'Y' && ch3 != 'n' && ch3 != 'N'){
                        cout<<"\n\t\tInvalid option. Please try again: ";
                        ch3 = _getch();
                        fflush(stdin);
                    }
                    if (ch3 == 'n' || ch3 == 'N')
                        break;
                }
                while (response2 == 2){
                    system("cls");
                    cout<<"\n\n\t\tRailway Reservation System"
                          "\n\t\tAdd Passenger Menu";
                    int trainId = 0;
                    cout << "\n\t\tEnter the train id which you want to add passenger:";
                    cin >> trainId;

                    cout<<"\n\t\tPassenger id will be generated automatically.";

                    int seat = 0;
                    cout << "\n\t\tEnter the passenger's seat:";
                    cin >> seat;

                    string passengerName="";
                    cout << "\n\t\tEnter the passenger's name:";
                    getline(cin, passengerName);

                    string passengerSurname="";
                    cout << "\n\t\tEnter the passenger's surname:";
                    getline(cin, passengerSurname);

                    bool check = false;
                    Passenger myPassenger;
                    try {
                       check = myPassenger.addPassengerToDatabase(trainId, seat, passengerName, passengerSurname);
                    }
                    catch (invalid_argument &e){
                        cerr<<"\n\n\t\tError while adding passenger: "<<e.what();
                    }

                    if (check)
                        cout<<"\n\t\tPassenger added successfully.";
                    else
                        cout<<"\n\t\tPassenger could not be added.";

                    cout<<"Do you want to add another passenger? (y/n)";
                    char ch3 = _getch();
                    fflush(stdin);
                    while (ch3 != 'y' && ch3 != 'Y' && ch3 != 'n' && ch3 != 'N'){
                        cout<<"\n\t\tInvalid option. Please try again: ";
                        ch3 = _getch();
                        fflush(stdin);
                    }
                    if (ch3 == 'n' || ch3 == 'N')
                        break;
                }
                while (response2 == 3){
                    system("cls");
                    cout<<"\n\n\t\tRailway Reservation System"
                          "\n\t\tDelete Passenger Menu";

                    int trainId = 0;
                    cout << "\n\t\tEnter the passenger's train id:";
                    cin >> trainId;

                    string passengerId="";
                    cout << "\n\t\tEnter the passenger's id:";
                    getline(cin, passengerId);

                    bool check = false;
                    Passenger myPassenger;
                    try {
                        check = myPassenger.deletePassengerFromDatabase(trainId, passengerId);
                    }
                    catch (invalid_argument &e){
                        cerr<<"\n\n\t\tError while deleting passenger: "<<e.what();
                    }

                    if (check)
                        cout<<"\n\t\tPassenger deleted successfully.";
                    else
                        cout<<"\n\t\tPassenger could not be deleted.";

                    cout<<"Do you want to delete another passenger? (y/n)";
                    char ch3 = _getch();
                    fflush(stdin);
                    while (ch3 != 'y' && ch3 != 'Y' && ch3 != 'n' && ch3 != 'N'){
                        cout<<"\n\t\tInvalid option. Please try again: ";
                        ch3 = _getch();
                        fflush(stdin);
                    }
                    if (ch3 == 'n' || ch3 == 'N')
                        break;
                }
                while (response2 == 4){
                    system("cls");
                    cout<<"\n\n\t\tRailway Reservation System"
                          "\n\t\tChange Passenger Menu";
                    int trainId = 0;
                    cout << "\n\t\tEnter the passenger's train id:";
                    cin >> trainId;

                    string passengerId;
                    cout << "\n\t\tEnter the passenger's id:";
                    getline(cin, passengerId);

                    int seatNumber = 0;
                    cout << "\n\t\tEnter the passenger's new seat number(If you don't want to change, enter -1):";
                    cin >> seatNumber;

                    string passengerName;
                    cout << "\n\t\tEnter the passenger's new name(If you don't want to change press enter):";
                    getline(cin, passengerName);

                    string passengerSurname;
                    cout << "\n\t\tEnter the passenger's new surname(If you don't want to change press enter):";
                    getline(cin, passengerSurname);

                    bool check = false;
                    Passenger myPassenger;
                    try {
                        check = myPassenger.changePassengerInDatabase(trainId, passengerId, seatNumber, passengerName, passengerSurname);
                    }
                    catch (invalid_argument &e){
                        cerr<<"\n\n\t\tError while changing passenger: "<<e.what();
                    }

                    if (check)
                        cout<<"\n\t\tPassenger changed successfully.";
                    else
                        cout<<"\n\t\tPassenger could not be changed.";

                    cout<<"Do you want to change another passenger? (y/n)";
                    char ch3 = _getch();
                    fflush(stdin);
                    while (ch3 != 'y' && ch3 != 'Y' && ch3 != 'n' && ch3 != 'N'){
                        cout<<"\n\t\tInvalid option. Please try again: ";
                        ch3 = _getch();
                        fflush(stdin);
                    }
                    if (ch3 == 'n' || ch3 == 'N')
                        break;
                }
                while (response2 == 5){
                    response = -1;
                    break;
                }
                while (response2 == 6){
                    response = 4;
                    break;
                }
                while (response2 == 0){
                    login = 0;
                    response = 0;
                    break;
                }
            }
            while(response == 3){
                bool check = false;
                try {
                    check = myAdmin.passwordChange();
                }
                catch (invalid_argument &e){
                    cerr<<"\n\n\t\tError while changing password: "<<e.what();
                }
                if(check){
                    cout << "\n\n\t\tYou are redirected to the main menu.";
                    _getch();
                    fflush(stdin);
                    login = -1;
                    break;
                }
                else{
                    cout<<"\n\n\t\tPassword could not be changed."
                          "\n\t\tPress any key to continue.";
                    _getch();
                    fflush(stdin);
                    login = 0;
                    break;
                }
            }
            while(response == 4){
                login = -1;
                break;
            }
            while(response == 0){
                login = 0;
                break;
            }
        }
        while (login == 2){
            int response;
            system("cls");
            cout<<"\n\n\t\tRailway Reservation System"
                  "\n\n\t\t1.Show Trains"
                  "\n\t\t2.Book Ticket"
                  "\n\t\t3.Cancel Ticket"
                  "\n\t\t4.Main Menu"
                  "\n\t\t0.Exit System"
                  "\n\n\t\tChoose an option: ";
            char ch2 = _getch();
            fflush(stdin);
            response = ch2 - '0';
            while (response != 1 && response != 2 && response != 3 && response != 4 && response != 0) {
                cout << "\n\t\tInvalid option. Please try again: ";
                ch2 = _getch();
                fflush(stdin);
                response = ch2 - '0';
            }
            while (response == 1){
                Train myTrain;
                myTrain.readInformation();
                myTrain.printInformation();
                cout<<"\n\n\t\tPress any key to continue.";
                _getch();
                fflush(stdin);
                break;
            }
            while (response == 2){
                Passenger myPassenger;
                int trainNumber;
                cout<<"\n\n\t\tEnter train number: ";
                cin>>trainNumber;
                int seatNumber;
                cout<<"\n\n\t\tEnter seat number: ";
                cin>>seatNumber;
                string passengerName;
                cout<<"\n\n\t\tEnter passenger name: ";
                cin>>passengerName;
                string passengerSurname;
                cout<<"\n\n\t\tEnter passenger surname: ";
                cin>>passengerSurname;

                bool check = false;
                try{
                    check = myPassenger.addPassengerToDatabase(trainNumber, seatNumber, passengerName, passengerSurname);
                }
                catch (invalid_argument &e){
                    cerr<<"\n\n\t\tError while adding passenger to database: "<<e.what()<<endl<<endl;
                }

                if(check){
                    cout<<"\n\n\t\tTicket has been booked successfully.";
                }
                else{
                    cout<<"\n\n\t\tTicket could not be booked.";
                }

                cout<<"\n\n\t\tDo you want to book another ticket? (y/n): ";
                char ch2 = _getch();
                fflush(stdin);
                while (ch2 != 'y' && ch2 != 'Y' && ch2 != 'n' && ch2 != 'N'){
                    cout<<"\n\n\t\tInvalid option. Please try again: ";
                    ch2 = _getch();
                    fflush(stdin);
                }
                if (ch2 == 'n' || ch2 == 'N')
                    break;
            }
            while (response == 3){
                Passenger myPassenger;
                int trainNumber;
                cout<<"\n\n\t\tEnter train number: ";
                cin>>trainNumber;
                string passengerId;
                cout<<"\n\n\t\tEnter id number: ";
                getline(cin, passengerId);

                bool check = false;
                try {
                    check = myPassenger.deletePassengerFromDatabase(trainNumber, passengerId);
                }
                catch (invalid_argument &e) {
                    cerr<<"\n\n\t\tError while deleting passenger from database: "<<e.what()<<endl<<endl;
                }

                if (check){
                    cout<<"\n\n\t\tTicket cancelled successfully.";
                }
                else{
                    cout<<"\n\n\t\tTicket could not be cancelled.";
                }

                cout<<"\n\n\t\tDo you want to cancel another ticket? (y/n): ";
                char ch2 = _getch();
                fflush(stdin);
                while (ch2 != 'y' && ch2 != 'Y' && ch2 != 'n' && ch2 != 'N'){
                    cout<<"\n\n\t\tInvalid option. Please try again: ";
                    ch2 = _getch();
                    fflush(stdin);
                }
                if (ch2 == 'n' || ch2 == 'N')
                    break;
            }
            while (response == 4){
                login = -1;
                break;
            }
            while (response == 0){
                login = 0;
                break;
            }
        }
        while (login == 3){
            system("cls");
            cout<<"\n\n\t\tRailway Reservation System"
                  "\n\n\t\tYou have entered wrong username or password."
                  "\n\t\tExiting system.";
            break;
        }
        while (login == 4){
            system("cls");
            cout<<"\n\n\t\tRailway Reservation System"
                  "\n\n\t\tAdmin account created."
                  "\n\t\tThank you for using my system."
                  "\n\t\tExiting system.";
            break;
        }
        while (login == 0){
            system("cls");
            cout<<"\n\n\t\tRailway Reservation System"
                  "\n\n\t\tThank you for using my system."
                  "\n\t\tHave a nice day!"
                  "\n\n\t\tExiting system.";
            break;
        }
        if (login == 0 || login == 4 || login == 3)
            break;
    }
    return 0;
}