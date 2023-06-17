#ifndef RAILWAY_ADMIN_H
#define RAILWAY_ADMIN_H

#include <string>
using namespace std;
class Admin
{
public:
    explicit Admin ();
    ~Admin();
    int randomPasswordGenerator();
    int login();
    bool passwordChange();
private:
    int randomPassword;
    int enteredPassword;
    int newPassword;
    int newPasswordAgain;
    int checkPassword;
};

#endif
