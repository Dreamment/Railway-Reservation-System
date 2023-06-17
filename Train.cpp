#include <iostream>
#include <string>
#include <stdexcept>
#include <iomanip>
#include "Train.h"
#include "sqlite/sqlite3.h"
using namespace std;

Train::Train(int id, int seat, string name, int year, int month, int day, int hour, int minute, int newID) {
    setTrainID(id);
    setTrainSeat(seat);
    setTrainName(name);
    setYear(year);
    setMonth(month);
    setDay(day, month);
    setTime(hour, minute);
    setNewID(newID);
}

Train::~Train() {

}

void Train::setTrainID(int id) {
    if (id > 0)
        ID = id;
    else
        throw invalid_argument("Train ID must be greater than 0");
}

void Train::setTrainSeat(int seat) {
    if (seat > 0)
        trainSeat = seat;
    else
        throw invalid_argument("Train seat must be greater than 0");
}

void Train::setTrainName(string name) {
    if (name.length() > 0 && name.length() < 50)
        trainName = name;
    else
        throw invalid_argument("Train name must be between 1 and 50 characters");
}

void Train::setYear(int year) {
    if (year > 2022 && year < 2026)
        trainDepartureYear = year;
    else
        throw invalid_argument("Train departure year must be between 2023 and 2025");
}

void Train::setMonth(int month) {
    if (month > 0 && month < 13)
        trainDepartureMonth = month;
    else
        throw invalid_argument("Train departure month must be between 1 and 12");
}

void Train::setDay(int day, int month) {
    if (month == 1){
        if (day > 0 && day < 32)
            trainDepartureDay = day;
        else
            throw invalid_argument("Train departure day must be between 1 and 31");
    }
    else if (month == 2){
        if (getYear()%4){
            if (day > 0 && day < 29)
                trainDepartureDay = day;
            else
                throw invalid_argument("Train departure day must be between 1 and 28");
        }
        else{
            if (day > 0 && day < 30)
                trainDepartureDay = day;
            else
                throw invalid_argument("Train departure day must be between 1 and 29");
        }
    }
    else if (month == 3){
        if (day > 0 && day < 32)
            trainDepartureDay = day;
        else
            throw invalid_argument("Train departure day must be between 1 and 31");
    }
    else if (month == 4){
        if (day > 0 && day < 31)
            trainDepartureDay = day;
        else
            throw invalid_argument("Train departure day must be between 1 and 30");
    }
    else if (month == 5){
        if (day > 0 && day < 32)
            trainDepartureDay = day;
        else
            throw invalid_argument("Train departure day must be between 1 and 31");
    }
    else if (month == 6){
        if (day > 0 && day < 31)
            trainDepartureDay = day;
        else
            throw invalid_argument("Train departure day must be between 1 and 30");
    }
    else if (month == 7){
        if (day > 0 && day < 32)
            trainDepartureDay = day;
        else
            throw invalid_argument("Train departure day must be between 1 and 31");
    }
    else if (month == 8){
        if (day > 0 && day < 32)
            trainDepartureDay = day;
        else
            throw invalid_argument("Train departure day must be between 1 and 31");
    }
    else if (month == 9){
        if (day > 0 && day < 31)
            trainDepartureDay = day;
        else
            throw invalid_argument("Train departure day must be between 1 and 30");
    }
    else if (month == 10){
        if (day > 0 && day < 32)
            trainDepartureDay = day;
        else
            throw invalid_argument("Train departure day must be between 1 and 31");
    }
    else if (month == 11){
        if (day > 0 && day < 31)
            trainDepartureDay = day;
        else
            throw invalid_argument("Train departure day must be between 1 and 30");
    }
    else if (month == 12){
        if (day > 0 && day < 32)
            trainDepartureDay = day;
        else
            throw invalid_argument("Train departure day must be between 1 and 31");
    }
}

void Train::setTime(int hour, int minute) {
    bool check = false;
    if (hour >=0 && hour <24){
        if (minute >=0 && minute <60){
            trainDepartureHour = hour;
            trainDepartureMinute = minute;
            check = true;
        }
    }
    if (!check)
        throw invalid_argument("Train departure time must be between 00:00 and 23:59");
}

void Train::setNewID(int id) {
    if (newID > 0)
        newID = id;
    else
        throw invalid_argument("Train new ID must be greater than 0");
}

int Train::getID () const {
    return ID;
}

int Train::getSeat () const{
    return trainSeat;
}

string Train::getName () const{
    return trainName;
}

int Train::getYear () const{
    return trainDepartureYear;
}

int Train::getMonth () const{
    return trainDepartureMonth;
}

int Train::getDay () const{
    return trainDepartureDay;
}

int Train::getHour () const{
    return trainDepartureHour;
}

int Train::getMinute () const{
    return trainDepartureMinute;
}

int Train::getNewID () const{
    return newID;
}

bool Train::addTrainToDatabase (int id, int seat, string name, int year, int month, int day, int hour, int minute) {
    bool successful = false;

    string date = to_string(day) + "." + to_string(month) + "." + to_string(year);
    string time = to_string(hour) + ":" + to_string(minute);

    sqlite3* DB;
    int result = sqlite3_open("Railway Reservation System.db", &DB);

    if (result != SQLITE_OK)
        throw invalid_argument("Error opening database");
    else{
        string query = "INSERT INTO trains (train_id, train_name, train_departure_date, train_departure_time,"
                       " train_seat) VALUES (?, ?, ?, ?, ?)";
        sqlite3_stmt* statement;
        result = sqlite3_prepare_v2(DB, query.c_str(), -1, &statement, 0);
        if (result != SQLITE_OK)
            throw invalid_argument("Query preparation failed");
        else{
            sqlite3_bind_int(statement, 1, id);
            sqlite3_bind_text(statement, 2, name.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(statement, 3, date.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(statement, 4, time.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_int(statement, 5, seat);

            result = sqlite3_step(statement);

            if (result != SQLITE_DONE)
                throw invalid_argument("Data insertion failed");
            else
                successful = true;
        }
        sqlite3_finalize(statement);
    }
    sqlite3_close(DB);
    addNewTableToDataBase(id);
    return successful;
}

void Train::addNewTableToDataBase(int id) {
    sqlite3* DB;
    int result = sqlite3_open("Railway Reservation System.db", &DB);

    if (result != SQLITE_OK)
        throw invalid_argument("Error at database connection");
    else{
        string tableName = "passengers_of_train_" + to_string(id);
        string query = "CREATE TABLE "+ tableName + " (passenger_seat INTEGER PRIMARY KEY UNIQUE NOT NULL, "
                                                    "passenger_name TEXT NOT NULL, "
                                                    "passenger_surname TEXT NOT NULL)";
        result = sqlite3_exec(DB, query.c_str(), 0, 0, 0);

        if (result != SQLITE_OK)
            throw invalid_argument("Table creation failed");
    }
}

bool Train::deleteTrainFromDatabase (int id) {
    bool successful = false;

    sqlite3* DB;
    int result = sqlite3_open("Railway Reservation System.db", &DB);

    if (result != SQLITE_OK)
        throw invalid_argument("Error at database connection");
    else{
        string query = "DELETE FROM trains WHERE train_id = ?";
        sqlite3_stmt* statement;
        result = sqlite3_prepare_v2(DB, query.c_str(), -1, &statement, 0);

        if (result != SQLITE_OK)
            throw invalid_argument("Query preparation failed");
        else{
            sqlite3_bind_int(statement, 1, id);
            result = sqlite3_step(statement);
            if(result != SQLITE_DONE)
                throw invalid_argument("Data deletion failed");
            else
                successful = true;
        }
        sqlite3_finalize(statement);
    }
    sqlite3_close(DB);
    deleteTableFromDatabase(id);
    return successful;
}

void Train::deleteTableFromDatabase(int id) {
    sqlite3* DB;
    int result = sqlite3_open("Railway Reservation System.db", &DB);

    if (result != SQLITE_OK)
        throw invalid_argument("Error at database connection");
    else{
        string tableName = "passengers_of_train_" + to_string(id);
        string query = "DROP TABLE " + tableName;
        result = sqlite3_exec(DB, query.c_str(), 0, 0, 0);

        if (result != SQLITE_OK)
            throw invalid_argument("Table deletion failed");
    }
}

bool Train::changeTrainInformationInDatabase (int id, int seat, string name, int year, int month, int day, int hour,
                                              int minute, int newid) {
    bool successful = false;
    readInformation();
    if (newid == -1)
    {
        newid == id;
    }

    for (size_t i = 0; i < ids.size(); i++)
    {
        if (ids[i] == id)
        {
            string date = dates[i];
            string time = times[i];
            //dd.mm.yyyy
            if (seat == -1)
            {
                seat = seats[i];
            }
            if (name == "")
            {
                name = names[i];
            }
            if (year == -1)
            {
                year = stoi(date.substr(6, 4));
            }
            if (month == -1)
            {
                month = stoi(date.substr(3, 2));
            }
            if (day == -1)
            {
                day = stoi(date.substr(0, 2));
            }
            if (hour == -1)
            {
                hour = stoi(time.substr(0, 2));
            }
            if (minute == -1)
            {
                minute = stoi(time.substr(3, 2));
            }
            break;
        }
    }

    string date = to_string(day) + "." + to_string(month) + "." + to_string(year);
    string time = to_string(hour) + ":" + to_string(minute);

    sqlite3* DB;
    int result = sqlite3_open("Railway Reservation System.db", &DB);
    if (result != SQLITE_OK)
        throw invalid_argument("Error at database connection");
    else{
        string query = "UPDATE trains SET train_id = ?, train_name = ?, train_departure_date = ?, "
                       "train_departure_time = ?, train_seat = ? WHERE train_id = ?";
        sqlite3_stmt* statement;
        result = sqlite3_prepare_v2(DB, query.c_str(), -1, &statement, 0);
        if(result != SQLITE_OK)
            throw invalid_argument("Query preparation failed");
        else{
            sqlite3_bind_int(statement, 1, newid);
            sqlite3_bind_text(statement, 2, name.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(statement, 3, date.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(statement, 4, time.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_int(statement, 5, seat);
            sqlite3_bind_int(statement, 6, id);

            result = sqlite3_step(statement);
            if(result != SQLITE_DONE)
                throw invalid_argument("Data update failed");
            else
                successful = true;
        }
        sqlite3_finalize(statement);
    }
    sqlite3_close(DB);

    if (newid != id)
    {
        changeTableInDatabase(id, newid);
    }

    return successful;
}

void Train::changeTableInDatabase(int id, int newid) {
    sqlite3* DB;
    int result = sqlite3_open("Railway Reservation System.db", &DB);

    if (result != SQLITE_OK)
        throw invalid_argument("Error at database connection");
    else{
        string tableName = "passengers_of_train_" + to_string(id);
        string newTableName = "passengers_of_train_" + to_string(newid);
        string query = "ALTER TABLE " + tableName + " RENAME TO " + newTableName;
        result = sqlite3_exec(DB, query.c_str(), 0, 0, 0);

        if (result != SQLITE_OK)
            throw invalid_argument("Table renaming failed");
    }
}

void Train::readInformation () {
    sqlite3* DB;
    int result = sqlite3_open("Railway Reservation System.db", &DB);

    if (result != SQLITE_OK)
        throw invalid_argument("Error opening database");
    else{
        string query = "SELECT * FROM trains ";
        sqlite3_stmt* statement;
        result = sqlite3_prepare_v2(DB, query.c_str(), -1, &statement, 0);

        if (result != SQLITE_OK)
            throw invalid_argument("Query preparation failed");
        else{
            while (sqlite3_step(statement) == SQLITE_ROW){
                int id = sqlite3_column_int(statement, 0);
                ids.push_back(ID);

                string NAME = reinterpret_cast<const char*>(sqlite3_column_text(statement, 1));
                names.push_back(NAME);

                string DATE = reinterpret_cast<const char*>(sqlite3_column_text(statement, 2));
                dates.push_back(DATE);

                string TIME = reinterpret_cast<const char*>(sqlite3_column_text(statement, 3));
                times.push_back(TIME);

                int SEAT = sqlite3_column_int(statement, 4);
                seats.push_back(SEAT);
            }
        }
        sqlite3_finalize(statement);
    }
    sqlite3_close(DB);
}

void Train::printInformation() {
    int biggestID = 0;
    for (size_t i = 0; i < ids.size(); i++){
        if (ids[i] > biggestID)
            biggestID = ids[i];
    }
    int digitOfBiggestID = 0;
    while (biggestID != 0){
        biggestID /= 10;
        digitOfBiggestID++;
    }
    int biggestSeat = 0;
    for (size_t i = 0; i < seats.size(); i++){
        if (seats[i] > biggestSeat)
            biggestSeat = seats[i];
    }
    int digitOfBiggestSeat = 0;
    while (biggestSeat != 0){
        biggestSeat /= 10;
        digitOfBiggestSeat++;
    }
    if (digitOfBiggestSeat < 4)
        digitOfBiggestSeat = 4;
    int width = 69 + digitOfBiggestID + digitOfBiggestSeat;
    cout << setfill('-')<<setw(width)<<"-"<<endl
            <<"|"<<setfill(' ')<<setw(width)<<"Trains"<<"|"<<endl
            <<setfill('-')<<setw(width)<<"-"<<endl
            <<"|"<<setfill(' ')<<setw(digitOfBiggestID)<<"ID"<<"|"<<setfill(' ')<<setw(50)<<"Name"<<"|"
            <<setfill(' ')<<setw(10)<<"Date"<<"|"<<left<<setw(5)<<"Time"<<"|"<<setfill(' ')
            <<setw(digitOfBiggestSeat)<<"Seat"<<"|\n"
            <<setfill('-')<<setw(width)<<"-"<<endl;
    for (size_t i = 0; i < ids.size(); i++){
        cout<<"|"<<right<<setfill(' ')<<setw(digitOfBiggestID)<<ids[i]<<"|"
            <<left<<setfill(' ')<<setw(50)<<names[i]<<"|"
            <<setfill(' ')<<setw(10)<<dates[i]<<"|"
            <<setw(5)<<times[i]<<"|"
            <<right<<setfill(' ')<<setw(digitOfBiggestSeat)<<seats[i]<<"|\n";
        cout<<setfill('-')<<setw(width)<<"-"<<endl;
    }
}
