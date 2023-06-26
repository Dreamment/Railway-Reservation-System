#include <iostream>
#include <string>
#include <conio.h>
#include <random>
#include "Admin.h"
#include "sqlite/sqlite3.h"
using namespace std;
Admin::Admin(){
    randomPassword="";
    enteredPassword="";
    newPassword="";
    newPasswordAgain="";
    checkPassword="";
    username="";
}

Admin::~Admin()= default;

string Admin::randomPasswordGenerator(){
    int length=0;
    cout<< "\n\t\tPassword Length: ";
    cin>>length;
    while (length > 20 || length < 1){
            cout<<"\n\t\tInvalid length."
                  "\n\t\tPassword length should be between 1 and 20."
                  "\n\t\tPlease try again: ";
            cin>>length;
    }
    fflush(stdin);
    const string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890!@#$%^&*()";
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(0, characters.size() - 1);
    for (int i = 0; i < length; i++)
        randomPassword += characters[distribution(generator)];

    return randomPassword;
}

int Admin::login(){
    system("CLS");
    cout<<"\n\n\t\tWelcome to Railway Reservation System";

    bool check = checkAdmin();

    sqlite3* DB;
    int result = sqlite3_open("Railway Reservation System.db", &DB);

    if (result != SQLITE_OK)
        throw invalid_argument("Cannot open database");
    else {
        string query = "SELECT * FROM admin";
        sqlite3_stmt* statement;
        result = sqlite3_prepare_v2(DB, query.c_str(), -1, &statement, 0);

        if (result != SQLITE_OK)
            throw invalid_argument("Cannot create statement");
        else {
            int response;
            cout<<"\n\t\t1.Admin Login"
                  "\n\t\t2.User Login"
                  "\n\t\t0.Exit System"
                  "\n\n\t\tChoose an option: ";
            char ch = _getch();
            cout<<ch;
            response = ch - '0';
            while (response != 1 && response != 2 && response != 0) {
                cout << "\n\t\tInvalid option. Please try again: ";
                ch = _getch();
                response = ch - '0';
            }

            if(check){
                if (response == 1){
                    cout<<"\n\n\t\tEnter username: ";
                    cin>>username;
                    fflush(stdin);
                    cout<<"\n\t\tEnter password: ";
                    for(int i = 0; i< 20;){
                        char ch2 = _getch();
                        if(ch2== '\r'){
                            if(enteredPassword.empty()){
                                cout<<"\n\t\tYou need to enter at least 1 character."
                                      "\n\t\tPlease try again:";
                                i=0;
                                continue;
                            }
                            else
                                break;
                        }
                        else if (ch2 == '\b'){
                            if(!enteredPassword.empty()){
                                cout<<"\b \b";
                                enteredPassword.erase(enteredPassword.size()-1);
                                i--;
                            }
                            else{
                                cout<<"\n\t\t You need to enter at least 1 character."
                                      "\n\t\tPlease try again:";
                                i=0;
                                continue;
                            }
                        }
                        else{
                            cout<<"*";
                            enteredPassword += ch2;
                            i++;
                        }
                    }
                    fflush(stdin);
                    while (sqlite3_step(statement) == SQLITE_ROW) {
                        if (username == (char*)sqlite3_column_text(statement, 0) &&
                            enteredPassword == (char*)sqlite3_column_text(statement, 1)) {
                            cout << "\n\n\t\tLogin successful.";
                            sqlite3_finalize(statement);
                            sqlite3_close(DB);
                            return 1;
                        }
                    }

                    cout << "\n\n\t\tLogin failed. Please try again.";
                    sqlite3_finalize(statement);
                    sqlite3_close(DB);
                    return 3;
                }
            }

            if (response == 2){
                sqlite3_finalize(statement);
                sqlite3_close(DB);
                return 2;
            }
            if (response == 0){
                sqlite3_finalize(statement);
                sqlite3_close(DB);
                return 0;
            }
        }
    }

    cout<<"\n\n\t\tThere is no admin in the system."
          "\n\t\tYou are redirecting to admin registration page."
          "\n\t\tEnter any button and enter to continue.";
    getch();
    createAdmin();
    return 4;
}

bool Admin::passwordChange()
{
    bool successful=false;
    bool flag = false;

    sqlite3*DB;
    int result = sqlite3_open("Railway Reservation System.db", &DB);
    if (result != SQLITE_OK)
        throw invalid_argument("Cannot open database");
    else{
        string query = "UPDATE admin SET password = ? WHERE username = ?";
        sqlite3_stmt* statement;
        result = sqlite3_prepare_v2(DB, query.c_str(), -1, &statement, nullptr);
        if (result != SQLITE_OK)
            throw invalid_argument("Cannot create statement");
        else{
            int response;
            cout<<"\n\n\t\tDo you want to change password Manual or Random?"
                  "\n\t\t1. Manual"
                  "\n\t\t2. Random"
                  "\n\t\tChoose an option: ";
            char ch = _getch();
            response = ch - '0';
            while (response != 1 && response != 2) {
                cout << "\n\t\tInvalid option. Please try again: ";
                ch = _getch();
                response = ch - '0';
            }
            if (response==1)
            {
                int attempt=1;
                do {
                    password:
                    newPassword="";
                    cout<<"\n\t\tEnter New Password(Max 20 characters): ";
                    for (int i = 0; i < 20; i++){
                        char ch2 = _getch();
                        if (ch2 == 'r'){
                            if (newPassword.empty())
                            {
                                cout <<"\n\t\t You need to enter at least 1 character."
                                        "\n\t\t Please try again:";
                                i--;
                                continue;
                            }
                            else
                                break;
                        }
                        else if (ch2 == '\b'){
                            if (!newPassword.empty())
                            {
                                cout << "\b \b";
                                newPassword.erase(newPassword.size() - 1);
                            }
                            else{
                                cout<<"\n\t\t You need to enter at least 1 character."
                                        "\n\t\t Please try again:";
                                i--;
                                continue;
                            }
                        }
                        else{
                            newPassword += ch2;
                            cout << '*';
                        }
                    }
                } while (newPassword.length()<21 && newPassword.length()>0);
                do {
                    newPasswordAgain="";
                    cout<<"\n\t\tEnter New Password Again(Max 20 characters): ";
                    for (int i = 0; i < 20; i++){
                        char ch2 = _getch();
                        if (ch2 == 'r'){
                            if (newPassword.empty())
                            {
                                cout <<"\n\t\t You need to enter at least 1 character."
                                       "\n\t\t Please try again:";
                                i--;
                                continue;
                            }
                            else
                                break;
                        }
                        else if (ch2 == '\b'){
                            if (!newPasswordAgain.empty())
                            {
                                cout << "\b \b";
                                newPasswordAgain.erase(newPasswordAgain.size() - 1);
                            }
                            else{
                                cout<<"\n\t\t You need to enter at least 1 character."
                                      "\n\t\t Please try again:";
                                i--;
                                continue;
                            }
                        }
                        else{
                            newPasswordAgain += ch2;
                            cout << '*';
                        }
                    }
                } while (newPasswordAgain.length()<21 && newPasswordAgain.length()>0);
                if (attempt == 3){
                    cout<<"\n\t\tThis is your last attempt. If you enter wrong password again, you will be logged out.";
                }

                if(attempt == 4){
                    cout<<"\n\t\tYour passwords doesn't match 3 times in a row."
                          "\n\t\tYou will be logged out.";
                }
                else if (newPassword != newPasswordAgain){
                    attempt++;
                    cout<<"\n\t\tPassword doesn't match.";
                    cout<<"\n\t\tPlease enter same password: ";
                    goto password;
                }
                else
                    flag=true;
            }
            else
            {
                newPassword=randomPasswordGenerator();
                cout<<"\n\n\t\tYour new password is: "<<newPassword;
                flag = true;
            }
            if (flag){
                sqlite3_bind_text(statement, 1, newPassword.c_str(), -1, SQLITE_STATIC);
                sqlite3_bind_text(statement, 2, username.c_str(), -1, SQLITE_STATIC);
                result = sqlite3_step(statement);
                if (result != SQLITE_DONE)
                    throw invalid_argument("Cannot execute statement");
                else{
                    cout<<"\n\n\t\tPassword changed successfully.";
                    successful=true;
                }
            }
            sqlite3_finalize(statement);
        }
    }
    sqlite3_close(DB);
    return successful;
}

void Admin::createAdmin() {
    system("cls");
    cout <<"\n\n\t\tRailway Reservation System"
           "\n\t\tAdmin Registration Page";
    sqlite3* DB;
    int result = sqlite3_open("Railway Reservation System.db", &DB);
    if (result != SQLITE_OK)
        throw invalid_argument("Cannot open database");
    else {
        string query = "INSERT INTO Admin (user_name, password) VALUES (?, ?);";
        sqlite3_stmt* statement;
        result = sqlite3_prepare_v2(DB, query.c_str(), -1, &statement, 0);
        if (result != SQLITE_OK){
            const char* errorMessage = sqlite3_errmsg(DB);
            throw invalid_argument("Cannot prepare statement" + string(errorMessage));
        }
        else {
            cout<<"\n\n\t\tDou you want to add password randomly or normal?"
                  "\n\t\t1. Manuel"
                  "\n\t\t2. Random"
                  "\n\t\tChoose an option: ";
            char ch = _getch();
            fflush(stdin);
            int response = ch - '0';
            cout << response;
            while (response != 1 && response != 2){
                cout<<"\n\t\tInvalid option. Please try again: ";
                ch = _getch();
                fflush(stdin);
                response = ch - '0';
                cout << response;
            }
            cout<<"\n\n\t\tEnter username: ";
            string userName;
            cin>>userName;
            fflush(stdin);
            string password;
            if (response == 1){
                cout<<"\n\t\tEnter password: ";
                cin>>password;
            }
            else{
                password = randomPasswordGenerator();
                cout<<"\n\t\tYour password is: "<< password;
            }
            fflush(stdin);
            sqlite3_bind_text(statement, 1, userName.c_str(), -1, SQLITE_STATIC);
            sqlite3_bind_text(statement, 2, password.c_str(), -1, SQLITE_STATIC);

            result = sqlite3_step(statement);

            if (result != SQLITE_DONE)
                throw invalid_argument("Cannot insert data");
            else
                cout << "\n\n\t\tAdmin created successfully.";
        }
        sqlite3_finalize(statement);
    }
    sqlite3_close(DB);
    cout<<"\n\t\tPress something to continue.";
    _getch();
}

bool Admin::checkAdmin() {
    bool existOrNot = false;
    sqlite3 *DB;
    int result = sqlite3_open("Railway Reservation System.db", &DB);
    if (result != SQLITE_OK){
        const char* errorMessage = sqlite3_errmsg(DB);
        throw invalid_argument("Cannot open database: " + string(errorMessage));
    }
    else{
        string query = "SELECT COUNT(*) FROM admin";
        sqlite3_stmt *statement;
        result = sqlite3_prepare_v2(DB, query.c_str(), -1, &statement, 0);
        if (result != SQLITE_OK){
            const char* errorMessage = sqlite3_errmsg(DB);
            throw invalid_argument("Cannot prepare statement: " + string(errorMessage));
        }
        else{
            result = sqlite3_step(statement);
            if(result == SQLITE_ROW){
                int rowCount = sqlite3_column_int(statement, 0);
                if (rowCount > 0)
                    existOrNot = true;
            }
            else{
                const char* errorMessage = sqlite3_errmsg(DB);
                throw invalid_argument("Cannot execute statement: " + string(errorMessage));
            }
        }
        sqlite3_finalize(statement);
    }
    sqlite3_close(DB);
    return existOrNot;
}