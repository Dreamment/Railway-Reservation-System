#include <iostream>
#include <string>
#include <stdexcept>
#include <iomanip>
#include <regex>
#include "Train.h"
#include "sqlite/sqlite3.h"
using namespace std;

Train::Train(int id, int seat, string name, int year, int month, int day, int hour, int minute, int newID) {
    readInformation();
    this->ID = id;
    this->trainSeat = seat;
    this->trainName = name;
    this->trainDepartureYear = year;
    this->trainDepartureMonth = month;
    this->trainDepartureDay = day;
    this->trainDepartureHour = hour;
    this->trainDepartureMinute = minute;
    this->newID = newID;
}

Train::~Train() = default;

void Train::setTrainID(int id) {
    if (id > 0){
        for (int i : ids) {
            if (id == i) {
                throw (invalid_argument("This ID is already taken"));
            }
        }
    }
    else
        throw invalid_argument("Train ID must be greater than 0");
    ID = id;
}

void Train::setTrainSeat(int seat) {
    if (seat < 1)
        throw invalid_argument("Train seat must be greater than 0");

    for (size_t i = 0; i<ids.size(); i++){
        if (ids[i] == ID){
            if (seat <= seats[i]){
                trainSeat = seat;
                break;
            }
            else
                throw invalid_argument("Entered seat number is greater than the available seats");
        }
    }
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

void Train::setDay(int day) {
    if (trainDepartureMonth == 1){
        if (day > 0 && day < 32)
            trainDepartureDay = day;
        else
            throw invalid_argument("Train departure day must be between 1 and 31");
    }
    else if (trainDepartureMonth == 2){
        if (trainDepartureYear%4 != 0){
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
    else if (trainDepartureMonth == 3){
        if (day > 0 && day < 32)
            trainDepartureDay = day;
        else
            throw invalid_argument("Train departure day must be between 1 and 31");
    }
    else if (trainDepartureMonth == 4){
        if (day > 0 && day < 31)
            trainDepartureDay = day;
        else
            throw invalid_argument("Train departure day must be between 1 and 30");
    }
    else if (trainDepartureMonth == 5){
        if (day > 0 && day < 32)
            trainDepartureDay = day;
        else
            throw invalid_argument("Train departure day must be between 1 and 31");
    }
    else if (trainDepartureMonth == 6){
        if (day > 0 && day < 31)
            trainDepartureDay = day;
        else
            throw invalid_argument("Train departure day must be between 1 and 30");
    }
    else if (trainDepartureMonth == 7){
        if (day > 0 && day < 32)
            trainDepartureDay = day;
        else
            throw invalid_argument("Train departure day must be between 1 and 31");
    }
    else if (trainDepartureMonth == 8){
        if (day > 0 && day < 32)
            trainDepartureDay = day;
        else
            throw invalid_argument("Train departure day must be between 1 and 31");
    }
    else if (trainDepartureMonth == 9){
        if (day > 0 && day < 31)
            trainDepartureDay = day;
        else
            throw invalid_argument("Train departure day must be between 1 and 30");
    }
    else if (trainDepartureMonth == 10){
        if (day > 0 && day < 32)
            trainDepartureDay = day;
        else
            throw invalid_argument("Train departure day must be between 1 and 31");
    }
    else if (trainDepartureMonth == 11){
        if (day > 0 && day < 31)
            trainDepartureDay = day;
        else
            throw invalid_argument("Train departure day must be between 1 and 30");
    }
    else if (trainDepartureMonth == 12){
        if (day > 0 && day < 32)
            trainDepartureDay = day;
        else
            throw invalid_argument("Train departure day must be between 1 and 31");
    }
}

void Train::setDate(string date) {
    if (date != "-1"){
        regex dateRegex("([0-9]{2})\\.([0-9]{2})\\.([0-9]{4})");
        if (!regex_match(date, dateRegex))
            throw invalid_argument("Train departure date must be in format DD.MM.YYYY");
        else{
            setYear(stoi(date.substr(6, 4)));
            setMonth(stoi(date.substr(3, 2)));
            setDay(stoi(date.substr(0, 2)));
        }
    }
    else {
        trainDepartureYear = -1;
        trainDepartureMonth = -1;
        trainDepartureDay = -1;
    }
}

void Train::setTime(string time) {
    bool check = true;
    if(time != "-1"){
        regex timeRegex("([0-9]{2}):([0-9]{2})");
        if (!regex_match(time, timeRegex))
            check = false;

        if (!check)
            throw invalid_argument("Train departure time must be in format HH:MM");
        else{
            int hour = stoi(time.substr(0, 2));
            int minute = stoi(time.substr(3, 2));

            if(hour < 0 || hour > 23)
                check = false;
            if(minute < 0 || minute > 59)
                check = false;
            if (!check)
                throw invalid_argument("Train departure time must be between 00:00 and 23:59");
            else {
                trainDepartureHour = hour;
                trainDepartureMinute = minute;
            }
        }
    }
    else {
        trainDepartureHour = -1;
        trainDepartureMinute = -1;
    }
}

void Train::setNewID(int id) {
    bool check = true;
    for (int i : ids){
        if (i == id){
            check = false;
            break;
        }
    }
    if(check)
        newID = id;
    else
        throw invalid_argument("There is already a train with ID " + to_string(id));
}

void Train::setDeletionID(int id) {
    bool check = false;
    for (int i : ids){
        if (i == id){
            check = true;
            break;
        }
    }
    if(check)
        deletionID = id;
    else
        throw invalid_argument("There is no train with ID " + to_string(id));
}

void Train::setChangeID(int id) {
    bool check = false;
    for (int i : ids){
        if (i == id){
            check = true;
            break;
        }
    }
    if(check)
        changeID = id;
    else
        throw invalid_argument("There is no train with ID " + to_string(id));
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

bool Train::addTrainToDatabase (int id, int seat, string name, string date, string time) {
    bool successful = false;
    sqlite3* DB;
    int result = sqlite3_open("Railway Reservation System.db", &DB);

    if (result != SQLITE_OK){
        const char* errorMessage = sqlite3_errmsg(DB);
        throw invalid_argument("Error opening database"+ string(errorMessage));
    }
    else{
        string query = "INSERT INTO trains (train_id, train_name, train_departure_date, train_departure_time,"
                       " train_seat) VALUES (?, ?, ?, ?, ?)";
        sqlite3_stmt* statement;
        result = sqlite3_prepare_v2(DB, query.c_str(), -1, &statement, 0);
        if (result != SQLITE_OK){
            const char* errorMessage = sqlite3_errmsg(DB);
            throw invalid_argument("Query preparation failed" + string(errorMessage));
        }
        else{
            sqlite3_bind_int(statement, 1, id);
            sqlite3_bind_text(statement, 2, name.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(statement, 3, date.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(statement, 4, time.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_int(statement, 5, seat);

            result = sqlite3_step(statement);

            if (result != SQLITE_DONE){
                const char* errorMessage = sqlite3_errmsg(DB);
                throw invalid_argument("Data insertion failed" + string(errorMessage));
            }
            else
                successful = true;
        }
        sqlite3_finalize(statement);
    }
    sqlite3_close(DB);
    if (successful)
        addNewTableToDataBase(id);
    return successful;
}

void Train::addNewTableToDataBase(int id) {
    sqlite3* DB;
    int result = sqlite3_open("Railway Reservation System.db", &DB);

    if (result != SQLITE_OK){
        const char* errorMessage = sqlite3_errmsg(DB);
        throw invalid_argument("Error at database connection" + string(errorMessage));
    }
    else{
        string tableName = "passengers_of_train_" + to_string(id);
        string query = "CREATE TABLE "+ tableName + " (passenger_id TEXT PRIMARY KEY UNIQUE NOT NULL, "
                                                    "passenger_seat INTEGER UNIQUE NOT NULL, "
                                                    "passenger_name TEXT NOT NULL, "
                                                    "passenger_surname TEXT NOT NULL)";
        result = sqlite3_exec(DB, query.c_str(), nullptr, nullptr, nullptr);

        if (result != SQLITE_OK){
            const char* errorMessage = sqlite3_errmsg(DB);
            throw invalid_argument("Table creation failed: " + string(errorMessage));
        }
    }
}

bool Train::deleteTrainFromDatabase (int id) {
    bool successful = false;

    sqlite3* DB;
    int result = sqlite3_open("Railway Reservation System.db", &DB);

    if (result != SQLITE_OK){
        const char* errorMessage = sqlite3_errmsg(DB);
        throw invalid_argument("Error at database connection: " + string(errorMessage));
    }
    else{
        string query = "DELETE FROM trains WHERE train_id = ?";
        sqlite3_stmt* statement;
        result = sqlite3_prepare_v2(DB, query.c_str(), -1, &statement, nullptr);

        if (result != SQLITE_OK){
            const char* errorMessage = sqlite3_errmsg(DB);
            throw invalid_argument("Query preparation failed: " + string(errorMessage));
        }
        else{
            sqlite3_bind_int(statement, 1, id);
            result = sqlite3_step(statement);
            if(result == SQLITE_DONE){
                int effectedRows = sqlite3_changes(DB);
                if (effectedRows == 0)
                    throw invalid_argument("Train with ID " + to_string(id) + " does not exist");
                else
                    successful = true;
            }
            else{
                const char* errorMessage = sqlite3_errmsg(DB);
                throw invalid_argument("Data deletion failed: " + string(errorMessage));
            }
        }
        sqlite3_finalize(statement);
    }
    sqlite3_close(DB);
    if(successful)
        deleteTableFromDatabase(id);
    return successful;
}

void Train::deleteTableFromDatabase(int id) {
    sqlite3* DB;
    int result = sqlite3_open("Railway Reservation System.db", &DB);

    if (result != SQLITE_OK){
        const char* errorMessage = sqlite3_errmsg(DB);
        throw invalid_argument("Error at database connection" + string(errorMessage));
    }
    else{
        string tableName = "passengers_of_train_" + to_string(id);
        string query = "DROP TABLE " + tableName;
        result = sqlite3_exec(DB, query.c_str(), nullptr, nullptr, nullptr);

        if (result != SQLITE_OK){
            const char* errorMessage = sqlite3_errmsg(DB);
            throw invalid_argument("Table deletion failed" + string(errorMessage));
        }
    }
}

bool Train::changeTrainInformationInDatabase (int id, int seat, string name, string date, string time, int newid) {
    bool successful = false;
    readInformation();
    if (newid == -1)
    {
        newid = id;
    }

    for (size_t i = 0; i < ids.size(); i++)
    {
        if (ids[i] == id)
        {
            if (seat == -1)
            {
                seat = seats[i];
            }
            if (name == "-1")
            {
                name = names[i];
            }
            if (date == "-1")
            {
                date = dates[i];
            }
            if (time == "-1")
            {
                time = times[i];
            }
            break;
        }
    }

    sqlite3* DB;
    int result = sqlite3_open("Railway Reservation System.db", &DB);
    if (result != SQLITE_OK){
        const char* errorMessage = sqlite3_errmsg(DB);
        throw invalid_argument("Error at database connection: " + string(errorMessage));
    }
    else{
        string query = "UPDATE trains SET train_id = ?, train_name = ?, train_departure_date = ?, "
                       "train_departure_time = ?, train_seat = ? WHERE train_id = ?";
        sqlite3_stmt* statement;
        result = sqlite3_prepare_v2(DB, query.c_str(), -1, &statement, nullptr);
        if(result != SQLITE_OK){
            const char* errorMessage = sqlite3_errmsg(DB);
            throw invalid_argument("Query preparation failed: " + string(errorMessage));
        }
        else{
            sqlite3_bind_int(statement, 1, newid);
            sqlite3_bind_text(statement, 2, name.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(statement, 3, date.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(statement, 4, time.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_int(statement, 5, seat);
            sqlite3_bind_int(statement, 6, id);

            result = sqlite3_step(statement);
            if(result != SQLITE_DONE){
                const char* errorMessage = sqlite3_errmsg(DB);
                throw invalid_argument("Data update failed: " + string(errorMessage));
            }
            else
                successful = true;
        }
        sqlite3_finalize(statement);
    }
    sqlite3_close(DB);

    if (newid != id && successful)
    {
        changeTableInDatabase(id, newid);
    }

    return successful;
}

void Train::changeTableInDatabase(int id, int newid) {
    sqlite3* DB;
    int result = sqlite3_open("Railway Reservation System.db", &DB);

    if (result != SQLITE_OK){
        const char* errorMessage = sqlite3_errmsg(DB);
        throw invalid_argument("Error at database connection" + string(errorMessage));
    }
    else{
        string tableName = "passengers_of_train_" + to_string(id);
        string newTableName = "passengers_of_train_" + to_string(newid);
        string query = "ALTER TABLE " + tableName + " RENAME TO " + newTableName;
        result = sqlite3_exec(DB, query.c_str(), 0, 0, 0);

        if (result != SQLITE_OK) {
            const char *errorMessage = sqlite3_errmsg(DB);
            throw invalid_argument("Table renaming failed" + string(errorMessage));
        }
    }
}

void Train::readInformation () {
    ids.clear();
    names.clear();
    dates.clear();
    times.clear();
    seats.clear();
    sqlite3* DB;
    int result = sqlite3_open("Railway Reservation System.db", &DB);

    if (result != SQLITE_OK)
        throw invalid_argument("Error opening database");
    else{
        string query = "SELECT * FROM trains ";
        sqlite3_stmt* statement;
        result = sqlite3_prepare_v2(DB, query.c_str(), -1, &statement, nullptr);

        if (result != SQLITE_OK)
            throw invalid_argument("Query preparation failed");
        else{
            while (sqlite3_step(statement) == SQLITE_ROW){
                int id = sqlite3_column_int(statement, 0);
                ids.push_back(id);

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
    system("cls");
    int biggestID = 0;
    for (int id : ids){
        if (id > biggestID)
            biggestID = id;
    }
    int digitOfBiggestID = 0;
    while (biggestID != 0){
        biggestID /= 10;
        digitOfBiggestID++;
    }
    if (digitOfBiggestID == 1)
        digitOfBiggestID = 2;
    int biggestSeat = 0;
    for (int seat : seats){
        if (seat > biggestSeat)
            biggestSeat = seat;
    }
    int digitOfBiggestSeat = 0;
    while (biggestSeat != 0){
        biggestSeat /= 10;
        digitOfBiggestSeat++;
    }
    if (digitOfBiggestSeat < 4)
        digitOfBiggestSeat = 4;
    int width = 71 + digitOfBiggestID + digitOfBiggestSeat;

    int widthOfTrains[2] = {(width - 6)/2, (width - 6)/2 + (width - 6)%2 -1};
    cout << "\t"<<setfill('-')<<setw(width)<<"-"<<endl<<"\t"
         <<"|"<<setfill(' ')<<setw(widthOfTrains[0])<<" "<<"Trains"<<setfill(' ')<<setw(widthOfTrains[1])<<"|"<<endl
         <<"\t"<<setfill('-')<<setw(width)<<"-"<<endl<<"\t"
         <<"|"<<setfill(' ')<<setw(digitOfBiggestID)<<"ID"
         <<"|"<<setfill(' ')<<setw(23)<<""<<"Name"<<setfill(' ')<<setw(23)<<""
         <<"|   Date   "
         <<"|"<<left<<setfill(' ')<<setw(5)<<"Time"
         <<"|"<<left<<setfill(' ')<<setw(digitOfBiggestSeat)<<"Seat"<<"|\n\t"
         <<setfill('-')<<setw(width)<<"-"<<endl<<"\t";
    for (size_t i = 0; i < ids.size(); i++){
        int temp = static_cast<int>(names[i].length());
        int widthOfName[2] = {(50 - temp)/2, (50 - temp)/2};
        if (temp % 2 == 1)
            widthOfName[0]++;
        cout<<"|"<<right<<setfill(' ')<<setw(digitOfBiggestID)<<ids[i]
            <<"|"<<setfill(' ')<<setw(widthOfName[0])<<" "<<names[i]<<setfill(' ')<<setw(widthOfName[1])<<" "<<"|"
            <<setfill(' ')<<setw(10)<<dates[i]<<"|"
            <<setw(5)<<times[i]<<"|"
            <<right<<setfill(' ')<<setw(digitOfBiggestSeat)<<seats[i]<<"|\n\t";
        cout<<setfill('-')<<setw(width)<<"-"<<endl<<"\t";
    }
}

void Train::printTrain(int id) {
    int index = 0;
    for(size_t i = 0; i < ids.size(); i++){
        if (ids[i] == id)
            index = int(i);
    }
    int digitOfID = 0;
    while (id != 0){
        id /= 10;
        digitOfID++;
    }
    if (digitOfID == 1)
        digitOfID = 2;
    int digitOfSeat = 0;
    int temp = seats[index];
    while (temp != 0){
        temp /= 10;
        digitOfSeat++;
    }
    if (digitOfSeat < 4)
        digitOfSeat = 4;
    int width = 71 + digitOfID + digitOfSeat;
    cout << "\t"<<setfill('-')<<setw(width)<<"-"<<endl<<"\t"
         <<"|"<<setfill(' ')<<setw(digitOfID)<<"ID"
         <<"|"<<setfill(' ')<<setw(23)<<""<<"Name"<<setfill(' ')<<setw(23)<<""
         <<"|   Date   "
         <<"|"<<left<<setfill(' ')<<setw(5)<<"Time"
         <<"|"<<left<<setfill(' ')<<setw(digitOfSeat)<<"Seat"<<"|\n\t"
         <<setfill('-')<<setw(width)<<"-"<<endl<<"\t";
    int temp2 = static_cast<int>(names[index].length());
    int widthOfName[2] = {(50 - temp2)/2, (50 - temp2)/2};
    if (temp2 % 2 == 1)
        widthOfName[0]++;
    cout<<"|"<<right<<setfill(' ')<<setw(digitOfID)<<ids[index]
        <<"|"<<setfill(' ')<<setw(widthOfName[0])<<" "<<names[index]<<setfill(' ')<<setw(widthOfName[1])<<" "<<"|"
        <<setfill(' ')<<setw(10)<<dates[index]<<"|"
        <<setw(5)<<times[index]<<"|"
        <<right<<setfill(' ')<<setw(digitOfSeat)<<seats[index]<<"|\n\t";
    cout<<setfill('-')<<setw(width)<<"-"<<endl<<"\t";
}
