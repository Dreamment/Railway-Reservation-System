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
    this->trainId = trainID;
    this->passengerId = passengerId;
    this->passengerName = passengerName;
    this->passengerSurname = passengerSurname;
    this->passengerSeat = passengerSeat;
    this->passengerNewName = passengerNewName;
    this->passengerNewSurname = passengerNewSurname;
    this->passengerNewSeat = passengerNewSeat;
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
        throw invalid_argument("There is no train with this ID");
    }
}

void Passenger::setPassengerId(string id) {
    bool flag = false;
    for (string passengerID : passengerIds) {
        if (passengerID == id){
            flag = true;
            break;
        }
    }
    if (!flag)
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

void Passenger::setPassengerSeat(int seat) {
    bool flag = false;
    if (seat < 1)
        throw invalid_argument("Seat number must be greater than 0");
    for (size_t i = 0; i < ids.size(); i++) {
        if (ids[i] == trainId){
            if (seat <= seats[i]){
                passengerSeat = seat;
                flag = true;
                break;
            }
            else{
                throw invalid_argument("Seat number is greater than the number of seats in the train");
            }
        }
    }
    if (!flag)
        throw invalid_argument("Invalid train ID");
}

void Passenger::setPassengerNewName(string name) {
    if(name == "-1")
        passengerNewName = name;
    else if(name.length() <= 20)
        passengerNewName = name;
    else
        throw invalid_argument("Passenger name is too long");
}

void Passenger::setPassengerNewSurname(string surname) {
    if(surname == "-1")
        passengerNewSurname = surname;
    else if(surname.length() <= 20)
        passengerNewSurname = surname;
    else
        throw invalid_argument("Passenger surname is too long");
}

void Passenger::setPassengerNewSeat(int seat, int id) {
    if (seat == -1)
        passengerNewSeat = seat;
    else{
        bool flag = false;
        for (int i:ids) {
            if (i == id){
                if (seat <= seats[i] && seat > 0){
                    flag = checkSeat(seat);
                    break;
                }
            }
        }
        if (!flag)
            throw invalid_argument("Invalid seat number");
        else{
            for (int i:passengerSeats) {
                if (i == seat){
                    throw invalid_argument("This seat is already taken");
                }
            }
        }
    }
}

bool Passenger::addPassengerToDatabase(int id, int seat, string name, string surname) {
    bool successful = false;
    readInformation();

    sqlite3 *DB;
    int result = sqlite3_open("Railway Reservation System.db", &DB);

    if (result != SQLITE_OK) {
        const char* errorMessage = sqlite3_errmsg(DB);
        throw invalid_argument("Cannot open database" + string(errorMessage));
    }
    else {
        string tableName = "passengers_of_train_" + to_string(id);
        string query = "INSERT INTO "+ tableName +" (passenger_id, passenger_seat, passenger_name, passenger_surname) VALUES (?, ?, ?, ?)";
        sqlite3_stmt* statement;
        result = sqlite3_prepare_v2(DB, query.c_str(), -1, &statement, 0);

        if (result != SQLITE_OK) {
            const char* errorMessage = sqlite3_errmsg(DB);
            throw invalid_argument("Cannot create statement" + string(errorMessage));
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

            if (result != SQLITE_DONE){
                const char* errorMessage = sqlite3_errmsg(DB);
                throw invalid_argument("Cannot execute statement" + string(errorMessage));
            }
            else{
                printPassenger(id, _id);
                successful = true;
            }
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

    if (result != SQLITE_OK){
        const char* errorMessage = sqlite3_errmsg(DB);
        throw invalid_argument("Cannot open database: " + string(errorMessage));
    }
    else {
        string tableName = "passengers_of_train_" + to_string(id);
        string query = "DELETE FROM " + tableName + " WHERE passenger_id = ?";
        sqlite3_stmt* statement;
        result = sqlite3_prepare_v2(DB, query.c_str(), -1, &statement, 0);

        if (result != SQLITE_OK){
            const char* errorMessage = sqlite3_errmsg(DB);
            throw invalid_argument("Cannot create statement: " + string(errorMessage));
        }
        else {
            sqlite3_bind_text(statement, 1, passengerID.c_str(), -1, SQLITE_STATIC);

            result = sqlite3_step(statement);

            if (result == SQLITE_DONE){
                int effectedRows = sqlite3_changes(DB);
                if (effectedRows == 0)
                    throw invalid_argument("Invalid passenger ID");
                else
                    successful = true;
            }
            else{
                const char* errorMessage = sqlite3_errmsg(DB);
                throw invalid_argument("Cannot execute statement: " + string(errorMessage));
            }
        }
        sqlite3_finalize(statement);
    }
    sqlite3_close(DB);
    return successful;
}

bool Passenger::changePassengerInDatabase(int id, string passengerID, int newseat, string newname, string newsurname) {
    bool flag = true;

    if (newseat == -1)
        newseat = passengerSeats[id];
    if (newname == "-1")
        newname = passengerNames[id];
    if (newsurname == "-1")
        newsurname = passengerSurnames[id];

    sqlite3* DB;
    int result = sqlite3_open("Railway Reservation System.db", &DB);

    if (result != SQLITE_OK){
        const char* errorMessage = sqlite3_errmsg(DB);
        throw invalid_argument("Cannot open database: " + string(errorMessage));
    }
    else{
        string tableName = "passengers_of_train_" + to_string(id);
        string query = "UPDATE " + tableName + " SET passenger_seat = ?, passenger_name = ?, passenger_surname = ? "
                                               "WHERE passenger_id = ?";
        sqlite3_stmt* statement;
        result = sqlite3_prepare_v2(DB, query.c_str(), -1, &statement, 0);

        if (result != SQLITE_OK) {
            const char* errorMessage = sqlite3_errmsg(DB);
            throw invalid_argument("Cannot create statement: " + string(errorMessage));
        }
        else{
            sqlite3_bind_int(statement, 1, newseat);
            sqlite3_bind_text(statement, 2, newname.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(statement, 3, newsurname.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(statement, 4, passengerID.c_str(), -1, SQLITE_STATIC);

            result = sqlite3_step(statement);

            if (result != SQLITE_DONE){
                flag = false;
                const char* errorMessage = sqlite3_errmsg(DB);
                throw invalid_argument("Cannot execute statement: " + string(errorMessage));
            }
        }
        sqlite3_finalize(statement);
    }
    sqlite3_close(DB);
    return flag;
}

string Passenger::randomPassengerId() {
    string id;
    const string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456789";
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

    if (result != SQLITE_OK){
        const char* errorMessage = sqlite3_errmsg(DB);
        throw invalid_argument("Cannot open database: " + string(errorMessage));
    }
    else{
        string query = "SELECT * FROM passengers_of_train_" + to_string(id) + " WHERE passenger_id = ?";
        sqlite3_stmt* statement;
        result = sqlite3_prepare_v2(DB, query.c_str(), -1, &statement, nullptr);
        if ( result != SQLITE_OK){
            const char* errorMessage = sqlite3_errmsg(DB);
            throw invalid_argument("Cannot create statement: " + string(errorMessage));
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

    if (result != SQLITE_OK){
        const char* errorMessage = sqlite3_errmsg(DB);
        throw invalid_argument("Cannot open database: " + string(errorMessage));
    }
    else{
        string query = "SELECT * FROM passengers_of_train_" + to_string(id);
        sqlite3_stmt* statement;
        result = sqlite3_prepare_v2(DB, query.c_str(), -1, &statement, nullptr);

        if (result != SQLITE_OK){
            const char* errorMessage = sqlite3_errmsg(DB);
            throw invalid_argument("Cannot create statement: " + string(errorMessage));
        }
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

    orderPassengers();

    int biggestLengthOfId = 0;
    for (const auto & item : passengerIds){
        if (item.length() > biggestLengthOfId)
            biggestLengthOfId = item.length();
    }
    if (biggestLengthOfId == 0)
        biggestLengthOfId = 2;

    int biggestSeat = 0;
    if (!passengerSeats.empty()){
        auto maxNumber = max_element(passengerSeats.begin(), passengerSeats.end());
        biggestSeat = *maxNumber;
    }
    int temp = biggestSeat;
    int digitOfBiggestSeat = 0;
    while(temp < 0){
        temp /= 10;
        digitOfBiggestSeat++;
    }

    if (digitOfBiggestSeat<4)
        digitOfBiggestSeat = 4;

    int biggestNameLength = 0;
    for (const auto & item : passengerNames){
        if (item.length() > biggestNameLength)
            biggestNameLength = item.length();
    }
    if (biggestNameLength == 0)
        biggestNameLength = 20;

    int biggestSurnameLength = 0;
    for (const auto & item : passengerSurnames){
        if (item.length() > biggestSurnameLength)
            biggestSurnameLength = item.length();
    }
    if(biggestSurnameLength <7)
        biggestSurnameLength = 7;
    int temp2 = id;
    int digitOfId = 0;
    while (temp2 > 0){
        temp2/=10;
        digitOfId++;
    }
    int width = biggestLengthOfId + digitOfBiggestSeat + biggestNameLength + biggestSurnameLength + 5;
    int widthOfTableName[2] = {(width -2 - 20 - digitOfId)/2 + (width -2 - 20 - digitOfId)%2, (width -2 - 20 - digitOfId)/2};
    int widthOfId[2] = {(biggestLengthOfId - 2) / 2 + (biggestLengthOfId - 2) % 2, (biggestLengthOfId - 2) / 2};
    int widthOfSeat[2] = {(digitOfBiggestSeat-4)/2 + (digitOfBiggestSeat-4)%2, (digitOfBiggestSeat-4)/2};
    int widthOfName[2] = {(biggestNameLength-4)/2 + (biggestNameLength-4)%2, (biggestNameLength-4)/2};
    int widthOfSurname[2] = {(biggestSurnameLength-7)/2, (biggestSurnameLength-7)/2 + (biggestSurnameLength-7)%2};
    cout<<endl<<"\t"<<setfill('-')<<setw(width)<<"-"<<endl;
    if(widthOfTableName[0] > 0){
        cout<<"\t|"<<setfill(' ')<<setw(widthOfTableName[0])<<" "<<"Passengers of Train "<<id;
        if(widthOfTableName[1] > 0)
            cout<<setfill(' ')<<setw(widthOfTableName[1])<<" "<<"|"<<endl;
        else{
            cout<<"|"<<endl;
        }
    }
    else{
        cout<<"\t|Passengers of Train "<<id;
        if(widthOfTableName[1] > 0)
            cout<<setfill(' ')<<setw(widthOfTableName[1])<<" "<<"|"<<endl;
        else{
            cout<<"|"<<endl;
        }
    }
    cout<<"\t"<<setfill('-')<<setw(width)<<"-"<<endl;
    if(widthOfId[0] > 0){
        cout << "\t|"<<setfill(' ')<<setw(widthOfId[0])<<" "<<"ID";
        if(widthOfId[1] > 0)
            cout<<setfill(' ')<<setw(widthOfId[1])<<" "<<"|";
        else{
            cout<<"|";
        }
    }
    else{
        cout<<"\t|ID";
        if(widthOfId[1] > 0)
            cout<<setfill(' ')<<setw(widthOfId[1])<<" "<<"|";
        else{
            cout<<"|";
        }
    }
    if (widthOfSeat[0] > 0){
        cout<<setfill(' ')<<setw(widthOfSeat[0])<<" "<<"Seat";
        if(widthOfSeat[1] > 0)
            cout<<setfill(' ')<<setw(widthOfSeat[1])<<" "<<"|";
        else{
            cout<<"|";
        }
    }
    else{
        cout<<"Seat";
        if(widthOfSeat[1] > 0)
            cout<<setfill(' ')<<setw(widthOfSeat[1])<<" "<<"|";
        else{
            cout<<"|";
        }
    }
    if (widthOfName[0] > 0){
        cout<<setfill(' ')<<setw(widthOfName[0])<<" "<<"Name";
        if(widthOfName[1] > 0)
            cout<<setfill(' ')<<setw(widthOfName[1])<<" "<<"|";
        else{
            cout<<"|";
        }
    }
    else{
        cout<<"Name";
        if(widthOfName[1] > 0)
            cout<<setfill(' ')<<setw(widthOfName[1])<<" "<<"|";
        else{
            cout<<"|";
        }
    }
    if (widthOfSurname[0] > 0){
        cout<<setfill(' ')<<setw(widthOfSurname[0])<<" "<<"Surname";
        if(widthOfSurname[1] > 0)
            cout<<setfill(' ')<<setw(widthOfSurname[1])<<" "<<"|"<<endl;
        else{
            cout<<"|"<<endl;
        }
    }
    else{
        cout<<"Surname";
        if(widthOfSurname[1] > 0)
            cout<<setfill(' ')<<setw(widthOfSurname[1])<<" "<<"|"<<endl;
        else{
            cout<<"|"<<endl;
        }
    }
    cout<<"\t"<<setfill('-')<<setw(width)<<"-"<<endl;
    for (size_t i = 0; i<passengerIds.size(); i++){
        int _temp = widthOfName[0] + widthOfName[1] + 4;
        int _widthOfName[2] = {(_temp - static_cast<int>(passengerNames[i].length()))/2 + (_temp - static_cast<int>(passengerNames[i].length()))%2, (_temp - static_cast<int>(passengerNames[i].length()))/2};
        _temp = widthOfSurname[0] + widthOfSurname[1] + 7;
        int _widthOfSurname[2] = {(_temp - static_cast<int>(passengerSurnames[i].length()))/2 + (_temp - static_cast<int>(passengerSurnames[i].length()))%2, (_temp - static_cast<int>(passengerSurnames[i].length()))/2};
        cout<<"\t|"<<right<<setfill(' ')<<setw(biggestLengthOfId)<<passengerIds[i]
            <<"|"<<right<<setfill(' ')<<setw(digitOfBiggestSeat)<<passengerSeats[i]
            <<"|";
        if(_widthOfName[0] > 0){
            cout<<left<<setfill(' ')<<setw(_widthOfName[0])<<" "<<passengerNames[i];
            if(_widthOfName[1] > 0)
                cout<<left<<setfill(' ')<<setw(_widthOfName[1])<<" "<<"|";
            else{
                cout<<"|";
            }
        }
        else{
            cout<<left<<passengerNames[i];
            if(_widthOfName[1] > 0)
                cout<<left<<setfill(' ')<<setw(_widthOfName[1])<<" "<<"|";
            else{
                cout<<"|";
            }
        }
        if(_widthOfSurname[0] > 0){
            cout<<left<<setfill(' ')<<setw(_widthOfSurname[0])<<" "<<passengerSurnames[i];
            if(_widthOfSurname[1] > 0)
                cout<<left<<setfill(' ')<<setw(_widthOfSurname[1])<<" "<<"|"<<endl;
            else{
                cout<<"|"<<endl;
            }
        }
        else{
            cout<<left<<passengerSurnames[i];
            if(_widthOfSurname[1] > 0)
                cout<<left<<setfill(' ')<<setw(_widthOfSurname[1])<<" "<<"|"<<endl;
            else{
                cout<<"|"<<endl;
            }
        }
        cout<<"\t"<<setfill('-')<<setw(width)<<"-"<<endl;
    }
}

bool Passenger::checkSeat(int seat) {
    bool check = true;
    sqlite3 *DB;
    int result = sqlite3_open("Railway Reservation System.db", &DB);
    if (result != SQLITE_OK){
        const char* errorMessage = sqlite3_errmsg(DB);
        throw invalid_argument("Cannot open database: " + string(errorMessage));
    }
    else{
        string query = "SELECT * FROM passengers_of_train_" + to_string(trainId);
        sqlite3_stmt* statement;
        result = sqlite3_prepare_v2(DB, query.c_str(), -1, &statement, 0);

        if(result != SQLITE_OK){
            const char* errorMessage = sqlite3_errmsg(DB);
            throw invalid_argument("Cannot create statement: " + string(errorMessage));
        }
        else{
            while (sqlite3_step(statement) == SQLITE_ROW){
                if(seat == sqlite3_column_int(statement, 1))
                    check = false;
            }
        }
        sqlite3_finalize(statement);
    }
    sqlite3_close(DB);
    return check;
}

void Passenger::printPassenger(int trainId, string passengerId) {
    string name, surname;
    int seat;
    sqlite3 *DB;
    int result = sqlite3_open("Railway Reservation System.db", &DB);
    if (result != SQLITE_OK){
        const char* errorMessage = sqlite3_errmsg(DB);
        throw invalid_argument("Cannot open database: " + string(errorMessage));
    }
    else{
        string query = "SELECT * FROM passengers_of_train_" + to_string(trainId) + " WHERE passenger_id = ?";
        sqlite3_stmt* statement;
        result = sqlite3_prepare_v2(DB, query.c_str(), -1, &statement, 0);

        if(result != SQLITE_OK){
            const char* errorMessage = sqlite3_errmsg(DB);
            throw invalid_argument("Cannot create statement: " + string(errorMessage));
        }
        else{
            sqlite3_bind_text(statement, 1, passengerId.c_str(), -1, SQLITE_STATIC);
            while (sqlite3_step(statement) == SQLITE_ROW){
                seat = sqlite3_column_int(statement, 1);
                name = reinterpret_cast<const char *>(sqlite3_column_text(statement, 2));
                surname = reinterpret_cast<const char *>(sqlite3_column_text(statement, 3));
            }
        }
        sqlite3_finalize(statement);
    }
    sqlite3_close(DB);

    int lengthOfId = passengerId.length();
    int lengthOfName = name.length();
    int lengthOfSurname = surname.length();
    int digitOfSeat = 0;
    while(true){
        int temp = seat;
        while(temp > 0){
            temp /= 10;
            digitOfSeat++;
        }
        break;
    }
    int lengthOfTrainId = 0;
    while(true){
        int temp = trainId;
        while(temp > 0){
            temp /= 10;
            lengthOfTrainId++;
        }
        break;
    }
    if(digitOfSeat < 4)
        digitOfSeat = 4;
    if(lengthOfId < 2)
        lengthOfId = 2;
    if(lengthOfName < 4)
        lengthOfName = 4;
    if(lengthOfSurname < 7)
        lengthOfSurname = 7;
    int width = lengthOfId + digitOfSeat + lengthOfName + lengthOfSurname + 5;
    int widthOfTableName[2] = { (width - 21 - lengthOfTrainId)/2 + (width - 21 - lengthOfTrainId)%2, (width - 21 - lengthOfTrainId)/2};
    int widthOfID[2] = { (lengthOfId-2)/2 + (lengthOfId-2)%2, (lengthOfId-2)/2};
    int widthOfSeat[2] = { (digitOfSeat-4)/2, (digitOfSeat-4)/2 + (digitOfSeat-4)%2};
    int widthOfName[2] = { (lengthOfName-4)/2, (lengthOfName-4)/2 + (lengthOfName-4)%2};
    int widthOfSurname[2] = { (lengthOfSurname-7)/2, (lengthOfSurname-7)/2 + (lengthOfSurname-7)%2};

    cout<<"\n\t"<<setfill('-')<<setw(width)<<"-";
    if (widthOfTableName[0] > 0){
        cout<<"\n\t|"<<setfill(' ')<<setw(widthOfTableName[0])<<' '<<"Passenger Of Train "<<trainId;
        if(widthOfTableName[1] > 0)
            cout<<setfill(' ')<<setw(widthOfTableName[1])<<" ";
    }
    else{
        cout<<"\n\t|Passenger Of Train "<<trainId;
        if(widthOfTableName[1] > 0)
            cout<<setfill(' ')<<setw(widthOfTableName[1])<<" ";
    }
    cout<<"|\n\t"<<setfill('-')<<setw(width)<<"-";
    if(widthOfID[0] > 0){
        cout<<"\n\t|"<<setfill(' ')<<setw(widthOfID[0])<<" "<<"ID";
        if(widthOfID[1] > 0)
            cout<<setfill(' ')<<setw(widthOfID[1])<<" ";
    }
    else{
        cout<<"\n\t|ID";
        if(widthOfID[1] > 0)
            cout<<setfill(' ')<<setw(widthOfID[1])<<" ";
    }
    if(widthOfSeat[0] > 0){
        cout<<"|"<<setfill(' ')<<setw(widthOfSeat[0])<<" "<<"Seat";
        if(widthOfSeat[1] > 0)
            cout<<setfill(' ')<<setw(widthOfSeat[1])<<" ";
    }
    else{
        cout<<"|Seat";
        if(widthOfSeat[1] > 0)
            cout<<setfill(' ')<<setw(widthOfSeat[1])<<" ";
    }
    if(widthOfName[0] > 0){
        cout<<"|"<<setfill(' ')<<setw(widthOfName[0])<<" "<<"Name";
        if(widthOfName[1] > 0)
            cout<<setfill(' ')<<setw(widthOfName[1])<<" ";
    }
    else{
        cout<<"|Name";
        if(widthOfName[1] > 0)
            cout<<setfill(' ')<<setw(widthOfName[1])<<" ";
    }
    if(widthOfSurname[0] > 0){
        cout<<"|"<<setfill(' ')<<setw(widthOfSurname[0])<<" "<<"Surname";
        if(widthOfSurname[1] > 0)
            cout<<setfill(' ')<<setw(widthOfSurname[1])<<" ";
    }
    else{
        cout<<"|Surname";
        if(widthOfSurname[1] > 0)
            cout<<setfill(' ')<<setw(widthOfSurname[1])<<" ";
    }
    lengthOfId = passengerId.length();
    int temp = seat;
    digitOfSeat = 0;
    while(temp > 0){
        temp /= 10;
        digitOfSeat++;
    }
    lengthOfName = name.length();
    lengthOfSurname = surname.length();
    if(digitOfSeat<4){
        widthOfSeat[0] = (4 - digitOfSeat)/2 + (4 - digitOfSeat)%2;
        widthOfSeat[1] = (4 - digitOfSeat)/2;
    }
    else{
        widthOfSeat[0] = 0;
        widthOfSeat[1] = 0;
    }
    if (lengthOfName < 4){
        widthOfName[0] = (4 - lengthOfName)/2 + (4- lengthOfName)%2;
        widthOfName[1] = (4 - lengthOfName)/2;
    }
    else{
        widthOfName[0] = 0;
        widthOfName[1] = 0;
    }
    if (lengthOfSurname < 7){
        widthOfSurname[0] = (7 - lengthOfSurname)/2 + (7 - lengthOfSurname)%2;
        widthOfSurname[1] = (7 - lengthOfSurname)/2;
    }
    else{
        widthOfSurname[0] = 0;
        widthOfSurname[1] = 0;
    }
    cout<<"|\n\t"<<setfill('-')<<setw(width)<<"-"
        <<"\n\t|"<<setfill(' ')<<setw(lengthOfId)<<passengerId;
    if(widthOfSeat[0] > 0){
        cout<<"|"<<setfill(' ')<<setw(widthOfSeat[0])<<" "<<seat;
        if(widthOfSeat[1] > 0)
            cout<<setfill(' ')<<setw(widthOfSeat[1])<<" ";
    }
    else{
        cout<<"|"<<seat;
        if(widthOfSeat[1] > 0)
            cout<<setfill(' ')<<setw(widthOfSeat[1])<<" ";
    }
    if(widthOfName[0] > 0){
        cout<<"|"<<setfill(' ')<<setw(widthOfName[0])<<" "<<name;
        if(widthOfName[1] > 0)
            cout<<setfill(' ')<<setw(widthOfName[1])<<" ";
    }
    else{
        cout<<"|"<<name;
        if(widthOfName[1] > 0)
            cout<<setfill(' ')<<setw(widthOfName[1])<<" ";
    }
    if(widthOfSurname[0] > 0){
        cout<<"|"<<setfill(' ')<<setw(widthOfSurname[0])<<" "<<surname;
        if(widthOfSurname[1] > 0)
            cout<<setfill(' ')<<setw(widthOfSurname[1])<<" ";
    }
    else{
        cout<<"|"<<surname;
        if(widthOfSurname[1] > 0)
            cout<<setfill(' ')<<setw(widthOfSurname[1])<<" ";
    }
    cout<<"|\n\t"<<setfill('-')<<setw(width)<<"-"<<endl;
}

void Passenger::orderPassengers() {
    bool check = false;
    while(!check){
        check = true;
        if (!passengerIds.empty()){
            for (size_t i = 0; i < passengerIds.size()-1; i++){
                if(passengerSeats[i]>passengerSeats[i+1]){
                    check = false;
                    string tempId = passengerIds[i];
                    passengerIds[i] = passengerIds[i+1];
                    passengerIds[i+1] = tempId;
                    int tempSeat = passengerSeats[i];
                    passengerSeats[i] = passengerSeats[i+1];
                    passengerSeats[i+1] = tempSeat;
                    string tempName = passengerNames[i];
                    passengerNames[i] = passengerNames[i+1];
                    passengerNames[i+1] = tempName;
                    string tempSurname = passengerSurnames[i];
                    passengerSurnames[i] = passengerSurnames[i+1];
                    passengerSurnames[i+1] = tempSurname;
                }
            }
        }
    }
}