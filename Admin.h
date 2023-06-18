#ifndef RAILWAY_ADMIN_H
#define RAILWAY_ADMIN_H

#include <string>
using namespace std;
class Admin
{
public:
    explicit Admin ();
    ~Admin();
    string randomPasswordGenerator();
    int login();
    bool passwordChange();
    void createAdmin();
private:
    string randomPassword;
    string enteredPassword;
    string newPassword;
    string newPasswordAgain;
    string checkPassword;
    string username;
};

#endif
