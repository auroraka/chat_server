#include "userinfo.h"
#include "enviroment.h"

UserInfo::UserInfo(){
    id=-1;
    talkingTo=-1;
}

void addUser(const UserInfo &user){
    qDebug()<<"add user:  account:"<<user.account<<" nickname:"<<user.nickname<<" userTot:"<<userL.size();
    userL.push_back(user);
}

int findUser(QString account){
    Debug("finding acount...");
    for (int i=0;i<userL.size();i++) if (userL[i].account==account){
        Debug(QString("account %1 find.").arg(account));
        return i;
    }
    Debug(QString("no account :%1").arg(account));
    return -1;
}
