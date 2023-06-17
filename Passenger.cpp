#include <iostream>
#include <string>
#include "Passenger.h"
#include "sqlite/sqlite3.h"

using namespace std;


Passenger::Passenger(int trainID, string passengerName, string passengerSurname, int passengerSeat, int newTrainID,
                     string passengerNewName, string passengerNewSurname, int passengerNewSeat) {
    readInformation();
    setTrainID(trainID);
    setPassengerName(passengerName);
    setPassengerSurname(passengerSurname);
    setPassengerSeat(passengerSeat, trainID);
    setNewTrainID(trainID, newTrainID);
    setPassengerNewName(passengerNewName);
    setPassengerNewSurname(passengerNewSurname);
    setPassengerNewSeat(passengerNewSeat, trainID);
}

Passenger::~Passenger() = default;

void Passenger::setTrainID(int id) {
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

void Passenger::setNewTrainID(int id, int newid) {
    bool flag = false;
    bool flag2 = false;
    //if there is a train that has id id flag will be true
    //if there is already a train that has id newid flag2 will be true
    for (int i : ids) {
        if (i == id){
            flag = true;
            for (int j : ids) {
                if (j == newid){
                    flag2 = true;
                    break;
                }
            }
            break;
        }
    }
    if(!flag)
        throw invalid_argument("Invalid train ID");
    if(flag2)
        throw invalid_argument("Invalid new train ID");
    if (flag && !flag2)
        newTrainID = newid;
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
        string query = "INSERT INTO"+ tableName +" (passenger_seat, passenger_name, passenger_surname) VALUES (?, ?, ?)";
        sqlite3_stmt* statement;
        result = sqlite3_prepare_v2(DB, query.c_str(), -1, &statement, 0);

        if (result != SQLITE_OK) {
            throw invalid_argument("Cannot create statement");
        }
        else{
            sqlite3_bind_int(statement, 1, seat);
            sqlite3_bind_text(statement, 2, name.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(statement, 3, surname.c_str(), -1, SQLITE_STATIC);

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

bool Passenger::deletePassengerFromDatabase(int id, int seat) {
    bool successful = false;
    readInformation();

    sqlite3* DB;
    int result = sqlite3_open("Railway Reservation System.db", &DB);

    if (result != SQLITE_OK)
        throw invalid_argument("Cannot open database");
    else {
        string tableName = "passengers_of_train_" + to_string(id);
        string query = "DELETE FROM " + tableName + " WHERE passenger_seat = ?";
        sqlite3_stmt* statement;
        result = sqlite3_prepare_v2(DB, query.c_str(), -1, &statement, 0);

        if (result != SQLITE_OK)
            throw invalid_argument("Cannot create statement");
        else {
            sqlite3_bind_int(statement, 1, seat);

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

bool Passenger::changePassengerInDatabase(int id, int seat, int newid, int newseat, string newname, string newsurname) {
    bool successful = false;
    bool flag = true;
    readInformation();

    for (int i : ids){
        if (i==id){
            for (int j : ids){
                if (j==newid){
                    successful = false;
                    break;
                }
                else{
                    successful = true;
                }

            }
            break;
        }
        else
            flag = false;
    }
    if (!flag)
        throw invalid_argument("Invalid train ID");
    if (!successful)
        throw invalid_argument("Invalid new train ID");
    if (successful && flag){
        sqlite3* DB;
        int result = sqlite3_open("Railway Reservation System.db", &DB);

        if (result != SQLITE_OK)
            throw invalid_argument("Cannot open database");
        else{
            string tableName = "passengers_of_train_" + to_string(id);
            string query = "UPDATE " + tableName + " SET passenger_seat = ?, passenger_name = ?, passenger_surname = ? "
                                                   "WHERE passenger_seat = ?";
            sqlite3_stmt* statement;
            result = sqlite3_prepare_v2(DB, query.c_str(), -1, &statement, 0);

            if (result != SQLITE_OK)
                throw invalid_argument("Cannot create statement");
            else{
                sqlite3_bind_int(statement, 1, newseat);
                sqlite3_bind_text(statement, 2, newname.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_text(statement, 3, newsurname.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_int(statement, 4, seat);

                result = sqlite3_step(statement);

                if (result != SQLITE_DONE)
                    throw invalid_argument("Cannot execute statement");
                else
                    successful = true;
            }
            sqlite3_finalize(statement);
        }
        sqlite3_close(DB);
        changeTableInDatabase(id, newid);
    }
    return successful;
}
