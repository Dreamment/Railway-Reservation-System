#ifndef RAILWAY_RESERVATION_SYSTEM_PASSENGER_H
#define RAILWAY_RESERVATION_SYSTEM_PASSENGER_H

#include <string>
#include "Train.h"

class Passenger : public Train{
public:
    explicit Passenger(int trainID = 1, string passengerName = " ", string passengerSurname = " ", int passengerSeat = 1,
                       int newTrainID = 1, string passengerNewName = " ", string passengerNewSurname = " ",
                       int passengerNewSeat = 1);
    ~Passenger();
    void setTrainID(int id);
    void setPassengerName(string name);
    void setPassengerSurname(string surname);
    void setPassengerSeat(int seat, int id);
    void setNewTrainID(int id, int newid);
    void setPassengerNewName(string name);
    void setPassengerNewSurname(string surname);
    void setPassengerNewSeat(int seat, int id);
    bool addPassengerToDatabase(int id, int seat, string name, string surname);
    bool deletePassengerFromDatabase(int id , int seat);
    bool changePassengerInDatabase(int id, int seat, int newid, int newseat, string newname, string newsurname);
    bool changeTrainTableInDataBase(int id, int newid);
private:
    int trainId;
    string passengerName;
    string passengerSurname;
    int passengerSeat;
    int newTrainID;
    string passengerNewName;
    string passengerNewSurname;
    int passengerNewSeat;
};


#endif