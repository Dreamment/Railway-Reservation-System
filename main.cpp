#include <iostream>
#include <string>
#include <conio.h>
#include <regex>
#include "Admin.h"
#include "Train.h"
#include "Passenger.h"

using namespace std;

int main (){
    while (true){
        Admin myAdmin;
        int login = -1;
        try{
            login=myAdmin.login();
        }
        catch(invalid_argument &e){
            cerr<<"\n\n\t\tError while logging in: "<<e.what();
        }

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
                  "\n\t\t3. Admin Settings"
                  "\n\t\t4. Main Menu"
                  "\n\t\t0. Exit System"
                  "\n\n\t\tChoose an option: ";
            char ch = _getch();
            fflush(stdin);
            int response = ch - '0';
            cout << response;
            while(response != 1 && response != 2 && response != 3 && response != 4 && response != 0){
                cout<<"\n\t\tInvalid option. Please try again: ";
                ch = _getch();
                fflush(stdin);
                response = ch - '0';
                cout << response;
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
                    Train myTrain;

                    int trainId = 0;
                    cout<<"\n\t\tEnter the train id:";
                    cin>>trainId;
                    fflush(stdin);
                    try{
                        myTrain.setTrainID(trainId);
                    }
                    catch (invalid_argument &e){
                        cerr<<"\n\n\t\tError while setting train id: "<<e.what();
                        cout<<"\n\t\tPress any key to continue...";
                        _getch();
                        break;
                    }

                    int trainSeat = 0;
                    cout<<"\n\t\tEnter the train seat:";
                    cin>>trainSeat;
                    fflush(stdin);
                    try{
                        myTrain.setTrainSeat(trainSeat);
                    }
                    catch (invalid_argument &e){
                        cerr<<"\n\n\t\tError while setting train seat: "<<e.what();
                        cout<<"\n\t\tPress any key to continue...";
                        _getch();
                        break;
                    }

                    string trainName;
                    cout<<"\n\t\tEnter the train name:";
                    getline(cin, trainName);
                    fflush(stdin);
                    try{
                        myTrain.setTrainName(trainName);
                    }
                    catch (invalid_argument &e){
                        cerr<<"\n\n\t\tError while setting train name: "<<e.what();
                        cout<<"\n\t\tPress any key to continue...";
                        _getch();
                        break;
                    }

                    regex dateRegex("([0-9]{2})\\.([0-9]{2})\\.([0-9]{4})");
                    string trainDepartureDate;
                    cout<<"\n\t\tEnter the train departure date(DD.MM.YYYY): ";
                    getline(cin,trainDepartureDate);
                    fflush(stdin);
                    while(!regex_match(trainDepartureDate, dateRegex)){
                        cout<<"\n\t\tInvalid date format. Please try again(DD.MM.YYYY): ";
                        getline(cin,trainDepartureDate);
                        fflush(stdin);
                    }
                    try{
                        myTrain.setDate(trainDepartureDate);
                    }
                    catch (invalid_argument &e){
                        cerr<<"\n\n\t\tError while setting date: "<<e.what();
                        cout<<"\n\t\tPress any key to continue...";
                        _getch();
                        break;
                    }

                    regex timeRegex("([0-9]{2}):([0-9]{2})");
                    string trainDepartureTime;
                    cout<<"\n\t\tEnter the train departure time(HH:MM): ";
                    getline(cin, trainDepartureTime);
                    fflush(stdin);
                    while(!regex_match(trainDepartureTime, timeRegex)){
                        cout<<"\n\t\tInvalid time format. Please try again: ";
                        getline(cin,trainDepartureTime);
                        fflush(stdin);
                    }
                    try{
                        myTrain.setTime(trainDepartureTime);
                    }
                    catch (invalid_argument &e){
                        cerr<<"\n\n\t\tError while setting time: "<<e.what();
                        cout<<"\n\t\tPress any key to continue...";
                        _getch();
                        break;
                    }

                    bool check = false;
                    try {
                        check = myTrain.addTrainToDatabase(trainId, trainSeat, trainName, trainDepartureDate, trainDepartureTime);
                    }
                    catch (invalid_argument &e){
                        cerr<<"\n\n\t\tError while writing train information: "<<e.what();
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
                    Train myTrain;

                    int trainId = 0;
                    cout<<"\n\t\tEnter the train id which you want to delete:";
                    cin>>trainId;

                    try{
                        myTrain.setDeletionID(trainId);
                    }
                    catch (invalid_argument &e){
                        cerr<<"\n\n\t\tError while setting id: "<<e.what();
                        cout<<"\n\t\tPress any key to continue...";
                        _getch();
                        break;
                    }
                    cout<<endl;
                    myTrain.printTrain(trainId);
                    cout<<"\n\n\t\tAre you sure you want to delete this train? (Y/N): ";
                    char ch3 = _getch();
                    fflush(stdin);
                    cout<<ch3;
                    while(ch3 != 'Y' && ch3 != 'y' && ch3 != 'N' && ch3 != 'n'){
                        cout<<"\n\t\tInvalid option. Please try again: ";
                        ch3 = _getch();
                        fflush(stdin);
                        cout<<ch3;
                    }
                    if(ch3 == 'n' || ch3 == 'N'){
                        cout<<"\n\t\tTrain not deleted.";
                        cout<<"\n\t\tPress any key to continue...";
                        _getch();
                        break;
                    }

                    bool check = false;
                    try {
                        check = myTrain.deleteTrainFromDatabase(trainId);
                    }
                    catch (invalid_argument &e){
                        cerr<<"\n\n\t\tError while deleting train information: "<<e.what();
                        cout<<"\n\t\tPress any key to continue...";
                        _getch();
                        break;
                    }

                    if (check){
                        cout<<"\n\t\tTrain deleted successfully.";
                    }
                    else {
                        cout<<"\n\t\tTrain could not be deleted.";
                    }

                    cout<<"\n\n\t\tDo you want to delete another train? (Y/N): ";
                    ch3 = '\0';
                    ch3 = _getch();
                    cout << ch3;
                    fflush(stdin);
                    while (ch3 != 'Y' && ch3 != 'y' && ch3 != 'N' && ch3 != 'n'){
                        cout<<"\n\t\tInvalid option. Please try again: ";
                        ch3 = _getch();
                        fflush(stdin);
                        cout<<ch3;
                    }
                    if (ch3 == 'n' || ch3 == 'N')
                        break;
                }
                while (response2 == 4){
                    system("cls");
                    cout<<"\n\n\t\tRailway Reservation System"
                          "\n\t\tChange Train Menu";
                    Train myTrain;

                    int trainId = 0;
                    cout<<"\n\t\tEnter the train id which you want to change:";
                    cin>>trainId;
                    fflush(stdin);
                    try{
                        myTrain.setChangeID(trainId);
                    }
                    catch (invalid_argument &e){
                        cerr<<"\n\n\t\tError while setting id: "<<e.what();
                        cout<<"\n\t\tPress any key to continue...";
                        _getch();
                        break;
                    }
                    cout<<endl;
                    myTrain.printTrain(trainId);
                    cout<<"\n\n\t\tDo you want to change this train? (Y/N): ";
                    char ch3 = _getch();
                    fflush(stdin);
                    cout<<ch3;
                    while(ch3 != 'Y' && ch3 != 'y' && ch3 != 'N' && ch3 != 'n'){
                        cout<<"\n\t\tInvalid option. Please try again: ";
                        ch3 = _getch();
                        fflush(stdin);
                        cout<<ch3;
                    }
                    if(ch3 == 'n' || ch3 == 'N')
                        break;
                    cout<<"\n\n\t\tEnter the new train information ";

                    int newTrainId = 0;
                    cout<<"\n\t\tEnter the new train id(Enter -1 if you don't want to change):";
                    cin>>newTrainId;
                    fflush(stdin);
                    while(newTrainId < -1 || newTrainId == 0){
                        cout<<"\n\t\tTrain new id cannot be less than 1:";
                        cin>>newTrainId;
                        fflush(stdin);
                    }
                    try{
                        myTrain.setNewID(newTrainId);
                    }
                    catch (invalid_argument &e){
                        cerr<<"\n\n\t\tError while setting new id: "<<e.what();
                        cout<<"\n\t\tPress any key to continue...";
                        _getch();
                        break;
                    }

                    int newTrainSeat = 0;
                    cout<<"\n\t\tEnter the new train seat(Enter -1 if you don't want to change): ";
                    cin>>newTrainSeat;
                    fflush(stdin);
                    try{
                        if(newTrainSeat != -1)
                            myTrain.setTrainSeat(newTrainSeat);
                        else{
                            myTrain.setTrainSeat(1);
                        }
                    }
                    catch (invalid_argument &e){
                        cerr<<"\n\n\t\tError while setting train seat: "<<e.what();
                        cout<<"\n\t\tPress any key to continue...";
                        _getch();
                        break;
                    }

                    string newTrainName;
                    cout<<"\n\t\tEnter the new train name(Enter -1 if you don't want to change): ";
                    cin>>newTrainName;
                    fflush(stdin);
                    try{
                        if (newTrainName != "-1")
                            myTrain.setTrainName(newTrainName);
                        else{
                            myTrain.setTrainName(" ");
                        }
                    }
                    catch (invalid_argument &e){
                        cerr<<"\n\n\t\tError while setting train name: "<<e.what();
                        cout<<"\n\t\tPress any key to continue...";
                        _getch();
                        break;
                    }

                    string newTrainDepartureDate;
                    regex dateRegex("([0-9]{2})\\.([0-9]{2})\\.([0-9]{4})");
                    cout<<"\n\t\tEnter the new train departure date(DD.MM.YYYY)(Enter -1 if you don't want to change): ";
                    getline(cin, newTrainDepartureDate);
                    fflush(stdin);
                    while(newTrainDepartureDate != "-1" && !regex_match(newTrainDepartureDate, dateRegex)){
                        cout<<"\n\t\tInvalid date format. Please try again: ";
                        getline(cin, newTrainDepartureDate);
                        fflush(stdin);
                    }
                    try{
                        myTrain.setDate(newTrainDepartureDate);
                    }
                    catch (invalid_argument &e){
                        cerr<<"\n\n\t\tError while setting date: "<<e.what();
                        cout<<"\n\t\tPress any key to continue...";
                        _getch();
                        break;
                    }

                    regex timeRegex("([0-9]{2}):([0-9]{2})");
                    string newTrainDepartureTime;
                    cout<<"\n\t\tEnter the new train departure time(HH:MM)(Enter -1 if you don't want to change):";
                    getline(cin, newTrainDepartureTime);
                    fflush(stdin);
                    while(newTrainDepartureTime != "-1" && !regex_match(newTrainDepartureTime, timeRegex)){
                        cout<<"\n\t\tInvalid time format. Please try again(HH:MM): ";
                        getline(cin, newTrainDepartureTime);
                        fflush(stdin);
                    }
                    try{
                        myTrain.setTime(newTrainDepartureTime);
                    }
                    catch (invalid_argument &e){
                        cerr<<"\n\n\t\tError while setting time: "<<e.what();
                        cout<<"\n\t\tPress any key to continue...";
                        _getch();
                        break;
                    }

                    bool check = false;
                    try {
                        check = myTrain.changeTrainInformationInDatabase(trainId, newTrainSeat, newTrainName,
                                                                         newTrainDepartureDate, newTrainDepartureTime,
                                                                         newTrainId);
                    }
                    catch (invalid_argument &e){
                        cerr<<"\n\n\t\tError while changing train information: "<<e.what();
                    }

                    if (check){
                        cout<<"\n\t\tTrain changed successfully.";
                    }
                    else {
                        cout<<"\n\t\tTrain could not be changed.";
                    }

                    cout<<"\n\n\t\tDo you want to change another train? (Y/N): ";
                    ch3 = '\0';
                    ch3 = _getch();
                    fflush(stdin);
                    cout<<ch3;
                    while (ch3 != 'Y' && ch3 != 'y' && ch3 != 'N' && ch3 != 'n'){
                        cout<<"\n\t\tInvalid option. Please try again: ";
                        ch3 = _getch();
                        fflush(stdin);
                        cout<<ch3;
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
            // TODO:Fix Passenger Menu
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
                system("cls");
                cout<<"\n\n\t\tRailway Reservation System"
                      "\n\t\tAdmin Settings"
                      "\n\n\t\t1.Add New Admin"
                      "\n\t\t2.Delete Admin(Current Admin)"
                      "\n\t\t3.Change Password(Current Admin)"
                      "\n\t\t4.Previous Menu"
                      "\n\t\t5.Main Menu"
                      "\n\t\t0.Exit System"
                      "\n\n\t\tChoose an option: ";
                char ch2 = _getch();
                fflush(stdin);
                int response2 = ch2 - '0';
                cout << response2;
                while (response2 != 1 && response2 != 2 && response2 != 3 && response2 != 4 && response2 != 5 && response2 != 0) {
                    cout << "\n\t\tInvalid option. Please try again: ";
                    ch2 = _getch();
                    fflush(stdin);
                    response2 = ch2 - '0';
                    cout << response2;
                }
                while(response2 == 1){
                    try{
                        myAdmin.createAdmin();
                        cout<<"\n\t\tYou are redirecting to main menu."
                              "\n\t\tPress any key to continue.";
                        _getch();
                        fflush(stdin);
                        response2 = 5;
                        break;
                    }
                    catch (invalid_argument &e){
                        cerr<<"\n\n\t\tError while creating admin: "<<e.what();
                        cout<<"\n\t\tPress any key to exit.";
                        _getch();
                        fflush(stdin);
                        response2 = 0;
                        break;
                    }
                }
                while(response2 == 2){
                    system("cls");
                    cout<<"\n\n\t\tRailway Reservation System"
                          "\n\t\tDelete Admin Menu";
                    bool check = myAdmin.deleteAdmin();
                    if(check){
                        cout<<"\n\n\t\tAdmin deleted successfully."
                              "\n\t\tPress any key to exit.";
                        _getch();
                        fflush(stdin);
                        response2 = 0;
                        break;
                    }
                    else{
                        cout<<"\n\n\t\tAdmin could not be deleted."
                              "\n\t\tPress any key to exit.";
                        _getch();
                        fflush(stdin);
                        response2 = 0;
                        break;
                    }
                }
                while(response2 == 3){
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
                        response2 = 5;
                        break;
                    }
                    else{
                        cout<<"\n\n\t\tPassword could not be changed."
                              "\n\t\tPress any key to exit.";
                        _getch();
                        fflush(stdin);
                        response2 = 0;
                        break;
                    }
                }
                while(response2 == 4){
                    response = -1;
                    break;
                }
                while(response2 == 5){
                    response = 4;
                    break;
                }
                while(response2 == 0){
                    response = 0;
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
                  "\n\t\tUser Menu"
                  "\n\n\t\t1.Show Trains"
                  "\n\t\t2.Book Ticket"
                  "\n\t\t3.Cancel Ticket"
                  "\n\t\t4.Main Menu"
                  "\n\t\t0.Exit System"
                  "\n\n\t\tChoose an option: ";
            char ch = _getch();
            fflush(stdin);
            response = ch - '0';
            cout << response;
            while (response != 1 && response != 2 && response != 3 && response != 4 && response != 0) {
                cout << "\n\t\tInvalid option. Please try again: ";
                ch = _getch();
                fflush(stdin);
                response = ch - '0';
                cout << response;
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
                system("cls");
                cout<<"\n\n\t\tRailway Reservation System"
                      "\n\t\tBook Ticket Menu";
                bool flag = true;
                Passenger myPassenger;
                int trainNumber;
                cout<<"\n\n\t\tEnter train number: ";
                cin>>trainNumber;
                try{
                    myPassenger.setPassengerTrainID(trainNumber);
                }
                catch (invalid_argument &e){
                    flag = false;
                    cerr<<"\n\n\t\tError while setting passenger train id: "<<e.what()<<endl;
                    cout<<"\n\n\t\tPress any key to continue.";
                    _getch();
                }
                if (!flag)
                    break;
                int seatNumber;
                cout<<"\n\n\t\tEnter seat number: ";
                cin>>seatNumber;
                try{
                    myPassenger.setPassengerSeat(seatNumber);
                }
                catch (invalid_argument &e){
                    flag = false;
                    cerr<<"\n\n\t\tError while setting passenger seat number: "<<e.what()<<endl;
                    cout<<"\n\n\t\tPress any key to continue.";
                    _getch();
                }
                if (!flag)
                    break;
                string passengerName;
                cout<<"\n\n\t\tEnter passenger name: ";
                cin>>passengerName;
                try{
                    myPassenger.setPassengerName(passengerName);
                }
                catch (invalid_argument &e){
                    flag = false;
                    cerr<<"\n\n\t\tError while setting passenger name: "<<e.what()<<endl;
                    cout<<"\n\n\t\tPress any key to continue.";
                    _getch();
                }
                if (!flag)
                    break;
                string passengerSurname;
                cout<<"\n\n\t\tEnter passenger surname: ";
                cin>>passengerSurname;
                try{
                    myPassenger.setPassengerSurname(passengerSurname);
                }
                catch (invalid_argument &e){
                    flag = false;
                    cerr<<"\n\n\t\tError while setting passenger surname: "<<e.what()<<endl;
                    cout<<"\n\n\t\tPress any key to continue.";
                    _getch();
                }
                if (!flag)
                    break;

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
                cout << ch2;
                fflush(stdin);
                while (ch2 != 'y' && ch2 != 'Y' && ch2 != 'n' && ch2 != 'N'){
                    cout<<"\n\n\t\tInvalid option. Please try again: ";
                    ch2 = _getch();
                    fflush(stdin);
                    cout << ch2;
                }
                if (ch2 == 'n' || ch2 == 'N')
                    break;
            }
            while (response == 3){
                system("cls");
                cout<<"\n\n\t\tRailway Reservation System"
                      "\n\t\tCancel Ticket Menu";
                Passenger myPassenger;
                int trainNumber;
                cout<<"\n\n\t\tEnter train number: ";
                cin>>trainNumber;
                fflush(stdin);
                try{
                    myPassenger.setPassengerTrainID(trainNumber);
                }
                catch (invalid_argument &e){
                    cerr<<"\n\n\t\tError while setting passenger train id: "<<e.what()<<endl;
                }
                string passengerId;
                passengerId = "";
                cout<<"\n\n\t\tEnter id number: ";
                for (int i = 0; i < 5;){
                    char ch2 = _getch();
                    if (ch2 == '\r'){
                        if(passengerId.empty()){
                            cout<<"\n\t\tYou need to enter 5 characters. "
                                  "\n\t\tPlease try again: ";
                            i = 0;
                            continue;
                        }
                        else if (passengerId.length() == 5)
                            break;
                        else{
                            cout<<"\n\t\tYou need to enter 5 characters. "
                                  "\n\t\tPlease try again: ";
                            i = 0;
                            passengerId.clear();
                            continue;
                        }
                    }
                    else if (ch2 == '\b'){
                        if(!passengerId.empty()){
                            cout<<"\b \b";
                            passengerId.erase(passengerId.length() - 1);
                            i--;
                        }
                        else{
                            cout<<"\n\t\tYou need to enter at least 1 character. "
                                  "\n\t\tPlease try again: ";
                            i=0;
                            continue;
                        }
                    }
                    else{
                        cout<<ch2;
                        passengerId += ch2;
                        i++;
                    }
                }
                fflush(stdin);
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