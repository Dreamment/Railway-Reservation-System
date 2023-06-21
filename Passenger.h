#ifndef RAILWAY_RESERVATION_SYSTEM_PASSENGER_H
#define RAILWAY_RESERVATION_SYSTEM_PASSENGER_H

#include <string>
#include "Train.h"

class Passenger : public Train{
public:
    explicit Passenger(int trainID = 1, string passengerId = "", string passengerName = " ", string passengerSurname = " ", int passengerSeat = 1,
                       string passengerNewName = " ", string passengerNewSurname = " ",
                       int passengerNewSeat = 1);
    ~Passenger();
    void setPassengerTrainID(int id);
    void setPassengerId(string id);
    void setPassengerName(string name);
    void setPassengerSurname(string surname);
    void setPassengerSeat(int seat, int id);
    void setPassengerNewName(string name);
    void setPassengerNewSurname(string surname);
    void setPassengerNewSeat(int seat, int id);
    bool addPassengerToDatabase(int id, int seat, string name, string surname);
    bool deletePassengerFromDatabase(int id , string passengerID);
    bool changePassengerInDatabase(int id, string passengerID, int newseat, string newname, string newsurname);
    string randomPassengerId();
    bool checkPassengerId(int id, string ID);
    void readPassengerInformation(int id);
    void printPassengerInformation(int id);
private:
    int trainId;
    string passengerId;
    string passengerName;
    string passengerSurname;
    int passengerSeat;
    string passengerNewName;
    string passengerNewSurname;
    int passengerNewSeat;
    vector <string> passengerIds;
    vector <int> passengerSeats;
    vector <string> passengerNames;
    vector <string> passengerSurnames;
};


#endif