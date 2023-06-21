#include <iostream>
#include <string>
#include <random>
#include <algorithm>
#include <iomanip>
#include "Passenger.h"
#include "sqlite/sqlite3.h"

using namespace std;


Passenger::Passenger(int trainID,string passengerId, string passengerName, string passengerSurname, int passengerSeat,
                     string passengerNewName, string passengerNewSurname, int passengerNewSeat) {
    readInformation();
    setPassengerTrainID(trainID);
    setPassengerId(passengerId);
    setPassengerName(passengerName);
    setPassengerSurname(passengerSurname);
    setPassengerSeat(passengerSeat, trainID);
    setPassengerNewName(passengerNewName);
    setPassengerNewSurname(passengerNewSurname);
    setPassengerNewSeat(passengerNewSeat, trainID);

}

Passenger::~Passenger() = default;

void Passenger::setPassengerTrainID(int id) {
    bool flag = false;
    for (int i : ids) {
        if (i == id){
            trainId = id;
            flag = true;
            break;
        }
    }
    if(!flag){
        throw invalid_argument("Invalid train ID");
    }
}

void Passenger::setPassengerId(string id) {
    bool flag = false;
    for (int i : ids){
        if (i == trainId){
            for (size_t j = 0; j < passengerIds.size(); j++) {
                if (passengerIds[j] == id){
                    flag = true;
                    break;
                }
            }
            break;
        }
    }
    if (flag)
        throw invalid_argument("Invalid passenger ID");
    else
        passengerId = id;
}

void Passenger::setPassengerName(string name) {
    if(name.length() <= 20)
        passengerName = name;
    else
        throw invalid_argument("Passenger name is too long");
}

void Passenger::setPassengerSurname(string surname) {
    if(surname.length() <= 20)
        passengerSurname = surname;
    else
        throw invalid_argument("Passenger surname is too long");
}

void Passenger::setPassengerSeat(int seat, int id) {
    bool flag = false;
    for (int i : ids) {
        if (i == id){
            if (seat <= seats[i] && seat > 0){
                passengerSeat = seat;
                flag = true;
                break;
            }
        }
    }
    if (!flag)
        throw invalid_argument("Invalid seat number");
}

void Passenger::setPassengerNewName(string name) {
    if(name.length() <= 20)
        passengerNewName = name;
    else
        throw invalid_argument("Passenger name is too long");
}

void Passenger::setPassengerNewSurname(string surname) {
    if(surname.length() <= 20)
        passengerNewSurname = surname;
    else
        throw invalid_argument("Passenger surname is too long");
}

void Passenger::setPassengerNewSeat(int seat, int id) {
    bool flag = false;
    for (int i:ids) {
        if (i == id){
            if (seat <= seats[i] && seat > 0){
                passengerNewSeat = seat;
                flag = true;
                break;
            }
        }
    }
    if (!flag)
        throw invalid_argument("Invalid seat number");
}

bool Passenger::addPassengerToDatabase(int id, int seat, string name, string surname) {
    bool successful = false;
    readInformation();

    sqlite3 *DB;
    int result = sqlite3_open("Railway Reservation System.db", &DB);

    if (result != SQLITE_OK) {
        throw invalid_argument("Cannot open database");
    }
    else {
        string tableName = "passengers_of_train_" + to_string(id);
        string query = "INSERT INTO"+ tableName +" (passenger_id, passenger_seat, passenger_name, passenger_surname) VALUES (?, ?, ?, ?)";
        sqlite3_stmt* statement;
        result = sqlite3_prepare_v2(DB, query.c_str(), -1, &statement, 0);

        if (result != SQLITE_OK) {
            throw invalid_argument("Cannot create statement");
        }
        else{
            string _id;
            bool check = false;
            do{
                _id = randomPassengerId();
                check = checkPassengerId(id, _id);
            }while (!check);
            cout <<"\n\n\t\tYour passenger ID is: " << _id << endl;

            sqlite3_bind_text(statement, 1,_id.c_str(),-1, SQLITE_STATIC);
            sqlite3_bind_int(statement, 2, seat);
            sqlite3_bind_text(statement, 3, name.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(statement, 4, surname.c_str(), -1, SQLITE_STATIC);

            result = sqlite3_step(statement);

            if (result != SQLITE_DONE)
                throw invalid_argument("Cannot execute statement");
            else
                successful = true;
        }
        sqlite3_finalize(statement);
    }
    sqlite3_close(DB);

    return successful;
}

bool Passenger::deletePassengerFromDatabase(int id, string passengerID) {
    bool successful = false;
    readInformation();

    sqlite3* DB;
    int result = sqlite3_open("Railway Reservation System.db", &DB);

    if (result != SQLITE_OK)
        throw invalid_argument("Cannot open database");
    else {
        string tableName = "passengers_of_train_" + to_string(id);
        string query = "DELETE FROM " + tableName + " WHERE passenger_id = ?";
        sqlite3_stmt* statement;
        result = sqlite3_prepare_v2(DB, query.c_str(), -1, &statement, 0);

        if (result != SQLITE_OK)
            throw invalid_argument("Cannot create statement");
        else {
            sqlite3_bind_text(statement, 1, passengerID.c_str(), -1, SQLITE_STATIC);

            result = sqlite3_step(statement);

            if (result != SQLITE_DONE)
                throw invalid_argument("Cannot execute statement");
            else
                successful = true;
        }
        sqlite3_finalize(statement);
    }
    sqlite3_close(DB);
    return successful;
}

bool Passenger::changePassengerInDatabase(int id, string passengerID, int newseat, string newname, string newsurname) {
    bool flag = false;
    readInformation();
    readPassengerInformation(id);

    if (newseat == -1)
        newseat = passengerSeats[id];
    if (newname == "")
        newname = passengerNames[id];
    if (newsurname == "")
        newsurname = passengerSurnames[id];

    for (int i : ids){
        if (i==id){
            flag = true;

            if(seats[i] < newseat){
                throw invalid_argument("Invalid new seat number");
                return false;
            }
            for (int j : passengerSeats){
                if (newseat == passengerSeats[id])
                    break;
                if (j == newseat){
                    throw invalid_argument("Invalid new seat number");
                    return false;
                }
            }
            break;
        }
        else
            flag = false;
    }

    if (!flag)
        throw invalid_argument("Invalid train ID");
    else{
        sqlite3* DB;
        int result = sqlite3_open("Railway Reservation System.db", &DB);

        if (result != SQLITE_OK)
            throw invalid_argument("Cannot open database");
        else{
            string tableName = "passengers_of_train_" + to_string(id);
            string query = "UPDATE " + tableName + " SET passenger_seat = ?, passenger_name = ?, passenger_surname = ? "
                                                   "WHERE passenger_id = ?";
            sqlite3_stmt* statement;
            result = sqlite3_prepare_v2(DB, query.c_str(), -1, &statement, 0);

            if (result != SQLITE_OK)
                throw invalid_argument("Cannot create statement");
            else{
                sqlite3_bind_int(statement, 1, newseat);
                sqlite3_bind_text(statement, 2, newname.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_text(statement, 3, newsurname.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_text(statement, 4, passengerID.c_str(), -1, SQLITE_STATIC);

                result = sqlite3_step(statement);

                if (result != SQLITE_DONE){
                    flag = false;
                    throw invalid_argument("Cannot execute statement");
                }
            }
            sqlite3_finalize(statement);
        }
        sqlite3_close(DB);
    }
    return flag;
}

string Passenger::randomPassengerId() {
    string id;
    const string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<> distribution(0, characters.size() - 1);
    for (int i = 0; i < 5; i++) {
        id += characters[distribution(generator)];
    }
    return id;
}

bool Passenger::checkPassengerId(int id, string ID) {
    bool check = true;
    sqlite3* DB;
    int result = sqlite3_open("Railway Reservation System.db", &DB);

    if (result != SQLITE_OK)
        throw invalid_argument("Cannot open database");
    else{
        string query = "SELECT * FROM passengers_of_train_" + to_string(id) + " WHERE passenger_id = ?";
        sqlite3_stmt* statement;
        result = sqlite3_prepare_v2(DB, query.c_str(), -1, &statement, nullptr);
        if ( result != SQLITE_OK){
            throw invalid_argument("Cannot create statement");
        }
        else{
            sqlite3_bind_text(statement, 1, ID.c_str(), -1, SQLITE_STATIC);
            result = sqlite3_step(statement);

            if (result == SQLITE_ROW)
                check = false;
        }
        sqlite3_finalize(statement);
    }
    sqlite3_close(DB);
    return check;
}

void Passenger::readPassengerInformation(int id) {
    sqlite3* DB;
    int result = sqlite3_open("Railway Reservation System.db", &DB);

    if (result != SQLITE_OK)
        throw invalid_argument("Cannot open database");
    else{
        string query = "SELECT * FROM passengers_of_train_" + to_string(id);
        sqlite3_stmt* statement;
        result = sqlite3_prepare_v2(DB, query.c_str(), -1, &statement, nullptr);

        if (result != SQLITE_OK)
            throw invalid_argument("Cannot create statement");
        else{
            while (sqlite3_step(statement) == SQLITE_ROW){

                string _passengerID = reinterpret_cast<const char*>(sqlite3_column_text(statement, 0));
                int _seat = sqlite3_column_int(statement, 1);
                string _name = reinterpret_cast<const char*>(sqlite3_column_text(statement, 2));
                string _surname = reinterpret_cast<const char*>(sqlite3_column_text(statement, 3));

                passengerIds.push_back(_passengerID);
                passengerSeats.push_back(_seat);
                passengerNames.push_back(_name);
                passengerSurnames.push_back(_surname);
            }
        }
        sqlite3_finalize(statement);
    }
    sqlite3_close(DB);
}

void Passenger::printPassengerInformation(int id) {

    bool check = true;
    do {
        for (size_t i = 0; i < passengerSeats.size(); i++){
            if (passengerSeats[i] > passengerSeats[i + 1]){
                string temp = passengerIds[i];
                passengerIds[i] = passengerIds[i + 1];
                passengerIds[i + 1] = temp;

                int temp2 = passengerSeats[i];
                passengerSeats[i] = passengerSeats[i + 1];
                passengerSeats[i + 1] = temp2;

                string temp3 = passengerNames[i];
                passengerNames[i] = passengerNames[i + 1];
                passengerNames[i + 1] = temp3;

                string temp4 = passengerSurnames[i];
                passengerSurnames[i] = passengerSurnames[i + 1];
                passengerSurnames[i + 1] = temp4;
                check = false;
            }
        }
    } while(!check);

    int biggestIdLength = 0;
    for (const auto & item : passengerIds){
        if (item.length() > biggestIdLength)
            biggestIdLength = item.length();
    }

    int biggestSeat = 0;
    auto maxNumber = max_element(passengerSeats.begin(), passengerSeats.end());
    biggestSeat = *maxNumber;

    if (biggestSeat<4)
        biggestSeat = 4;

    int biggestNameLength = 0;
    for (const auto & item : passengerNames){
        if (item.length() > biggestNameLength)
            biggestNameLength = item.length();
    }

    int biggestSurnameLength = 0;
    for (const auto & item : passengerSurnames){
        if (item.length() > biggestSurnameLength)
            biggestSurnameLength = item.length();
    }

    int width = biggestIdLength + biggestSeat + biggestNameLength + biggestSurnameLength + 5;

    cout<<setfill('-')<<setw(width)<<"-"<<endl
        <<"|"<<setfill(' ')<<setw(width-2)<<"Passengers of Train "<<id<<"|"<<endl
        <<setfill('-')<<setw(width)<<"-"<<endl
        <<"|"<<setfill(' ')<<setw(biggestIdLength)<<"ID"
        <<"|"<<setfill(' ')<<setw(biggestSeat)<<"Seat"
        <<"|"<<setfill(' ')<<setw(biggestNameLength)
        <<"|"<<"Name"<<setfill(' ')<<setw(biggestSurnameLength)<<"Surname"<<"|"<<endl
        <<setfill('-')<<setw(width)<<"-"<<endl;
    for (size_t i = 0; i<passengerIds.size(); i++){
        cout<<"|"<<setfill(' ')<<setw(biggestIdLength)<<passengerIds[i]
            <<"|"<<setfill(' ')<<setw(biggestSeat)<<passengerSeats[i]
            <<"|"<<setfill(' ')<<setw(biggestNameLength)<<passengerNames[i]
            <<"|"<<setfill(' ')<<setw(biggestSurnameLength)<<passengerSurnames[i]<<"|"<<endl;
        cout<<setfill('-')<<setw(width)<<"-"<<endl;
    }
}