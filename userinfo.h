#ifndef USERINFO_H
#define USERINFO_H

#include <QString>
#include <vector>
using std::vector;

class UserInfo
{
public:
    UserInfo();

    QString nickname;
    QString sign;
    int picture;
    QString account;
    QString password;
    int id;
    int talkingTo;
};

extern vector<UserInfo> userL;

void addUser(const UserInfo &user);
int findUser(QString account);


#endif // USERINFO_H
