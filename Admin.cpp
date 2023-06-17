#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include "Admin.h"
using namespace std;
Admin::Admin(){
    randomPassword=0;
    enteredPassword=0;
    newPassword=0;
    newPasswordAgain=0;
    checkPassword=0;
}

Admin::~Admin()= default;

int Admin::randomPasswordGenerator(){
    srand(time(nullptr));
    randomPassword=1000+rand()%(10000-1000+1);

    ofstream password;
    password.open("password.txt", ios::out|ios::app);
    if(!password){
        password.open("password.txt", ios::out|ios::app);
        password << "";
        password.close();
    }
    else{
        password << randomPassword<<endl;
        password.close();
    }
    cout<<"\n\n\t\tRandom Password had been generated."<<"\n\t\tPassword: "<<randomPassword;
    fflush(stdin);
    return randomPassword;
}

int Admin::login(){
    start:
    system("CLS");
    cout<<"\n\n\t\tWelcome to Railway Reservation System";
    int response;
    ifstream password;
    password.open ("password.txt", ios::in);
    if (!password){
        randomPasswordGenerator();
        cout<<"\n\n\t\tNote: You should change your password after enter system."<<"\n\t\tEnter any button and enter to continue.";
        string temp;
        cin>>temp;
        fflush(stdin);
        goto start;
    }
    else{
        cout<<"\n\t\t1.Admin Login";
        cout<<"\n\t\t2.User Login\n";
        cout<<"\n\t\t0.Exit System";
        cout<<"\n\n\t\tChoose an option: ";
        cin>>response;
        fflush(stdin);
        while (response !=1 && response !=2 && response!=0){
            cout<<"\n\t\tWrong selection. Choose properly: ";
            cin>>response;
            fflush(stdin);
        }
        if (response == 1){
            password>>checkPassword;
            cout<<"\n\t\tEnter Password: ";
            char ch;
            for (int i = 0; i < 4; ++i) {
                ch = _getch();
                cout << '*';
                enteredPassword = enteredPassword * 10 + (ch - '0');
            }
            if (enteredPassword==checkPassword)
                return 1;
            else
                return 3;
        }
        else if (response == 2)
            return 2;
        else
            return 0;
    }
}

bool Admin::passwordChange()
{
    bool successful=false;
    ifstream password;
    ofstream changePassword;
    password.open("password.txt", ios::in);
    changePassword.open("editPassword.txt", ios::out|ios::app);
    if (!password){
        cout<<"\n\n\t\tThe password file doesn't exist."
              "\n\t\tYou must have deleted the password file while the system was running."
              "\n\t\tExit system and recreate password file."
              "\n\t\tEnter any button and enter to continue.";
        string temp;
        cin>>temp;
        fflush(stdin);
        changePassword.close();
        remove("editPassword.txt");
        return successful;
    }
    else{
        int response;
        cout<<"\n\n\t\tDo you want to change password Manual or Random?"
              "\n\t\t1. Manual"
              "\n\t\t2. Random"
              "\n\t\tChoose an option: ";
        cin>>response;
        while (response !=1 && response !=2){
            cout<<"\n\t\tWrong selection. 1 -> Manual - 2 -> Random";
            cin>>response;
        }
        if (response==1)
        {
            int attempt=1;
            do {
                cout<<"\n\t\tEnter New Password (4 digit): ";
                for (int i = 0; i < 4; ++i) {
                    char ch = _getch();
                    cout << '*';
                    newPassword = newPassword * 10 + (ch - '0');
                }
            } while (newPassword<1000 || newPassword >9999);
            do {
                cout<<"\n\t\tEnter New Password Again (4 digit): ";
                for (int i = 0; i < 4; ++i) {
                    char ch = _getch();
                    cout << '*';
                    newPasswordAgain = newPasswordAgain * 10 + (ch - '0');
                }
            } while (newPasswordAgain<1000 || newPasswordAgain >9999);
            start:
            if (attempt == 3){
                cout<<"\n\t\tThis is your last attempt. If you enter wrong password again, you will be logged out.";
            }

            if(attempt == 4){
                cout<<"\n\t\tYour passwords doesn't match 3 times in a row."
                      "\n\t\tYou will be logged out.";
            }
            else if (newPassword==newPasswordAgain){
                changePassword<< newPassword<<endl;
                successful=true;
            }
            else{
                attempt++;
                cout<<"\n\t\tPassword doesn't match.";
                cout<<"\n\t\tPlease enter same password: ";
                do {
                    newPassword=0;
                    for (int i = 0; i < 4; ++i) {
                        char ch = _getch();
                        cout << '*';
                        newPassword = newPassword * 10 + (ch - '0');
                    }
                    if (newPassword<1000 || newPassword >9999)
                        cout<<"\n\t\tPassword must be 4 digit:";
                } while (newPassword<1000 || newPassword >9999);
                cout<<"Enter password again: ";
                do {
                    newPasswordAgain=0;
                    char ch = _getch();
                    cout << '*';
                    newPasswordAgain = newPasswordAgain * 10 + (ch - '0');
                    if (newPasswordAgain<1000 || newPasswordAgain >9999)
                        cout<<"\n\t\tPassword must be 4 digit:";
                } while (newPasswordAgain<1000 || newPasswordAgain >9999);
                goto start;
            }
        }
        else
        {
            newPassword=randomPasswordGenerator();
            changePassword<<newPassword<<endl;
            successful=true;
        }
    }
    password.close();
    changePassword.close();
    remove("password.txt");
    rename("editPassword.txt","password.txt");
    return successful;
}
