#ifndef RAILWAY_RESERVATION_SYSTEM_TRAIN_H
#define RAILWAY_RESERVATION_SYSTEM_TRAIN_H

#include <string>
#include <vector>
#include <conio.h>
using namespace std;

class Train
{
public:
    explicit Train ( int id = 1, int seat = 1, string name = " ", int year = 1, int month = 1, int day = 1,
                     int hour = 1, int minute = 1, int newID = 1 );
    ~Train();
    void setTrainID ( int id );
    void setTrainSeat ( int seat );
    void setTrainName ( string name );
    void setYear ( int year );
    void setMonth ( int month );
    void setDay ( int day);
    void setDate ( string date );
    void setTime ( string time );
    void setNewID ( int id );
    void setDeletionID( int id );
    void setChangeID( int id );
    int getID () const;
    int getSeat () const;
    string getName () const;
    int getYear () const;
    int getMonth () const;
    int getDay () const;
    int getHour () const;
    int getMinute () const;
    int getNewID () const;
    bool addTrainToDatabase (int id, int seat, string name, string date, string time);
    void addNewTableToDataBase(int id);
    bool deleteTrainFromDatabase (int id);
    void deleteTableFromDatabase(int id);
    bool changeTrainInformationInDatabase (int id, int seat, string name, string date, string time, int newid);
    void changeTableInDatabase(int id, int newid);
    void readInformation ();
    void printInformation ();
    void printTrain(int id);
private:
    int ID;
    int trainSeat;
    string trainName;
    int trainDepartureYear;
    int trainDepartureMonth;
    int trainDepartureDay;
    int trainDepartureHour;
    int trainDepartureMinute;
    int newID;
    int deletionID;
    int changeID;
protected:
    vector <int> ids;
    vector <int> seats;
    vector <string> names;
    vector <string> dates;
    vector <string> times;
};

#endif
