#include "tcp.h"
#include "enviroment.h"
#include "userinfo.h"
#include <QString>
#include <QMessageBox>
#include <vector>
using std::vector;

vector<QString> cache;

Tcp::Tcp()
{
    myPort=10086;
    server = new QTcpServer;
}

void Tcp::makeServer(){
    server->listen(QHostAddress::Any,myPort);
    connect(server,SIGNAL(newConnection()),this,SLOT(newConnection()));
    Debug("listening...");
}


void Tcp::newConnection(){

    QTcpSocket *newSocket=server->nextPendingConnection();


    socket.push_back(newSocket);
    cache.push_back(QString(""));

    int id=socket.size()-1;

    connect(newSocket,&(newSocket->readyRead),[=](){
        receiveInfo(id);
    });
    connect(newSocket,&(newSocket->disconnected),[=]{
        connectionLost();
    });

    Debug(QString("server: new socket create on %1. socket size: %2 cache size %3").arg(id).arg(socket.size()).arg(cache.size()));
    sendInfo(id,"connect_success");

//    connect(&gameI->heartBeat,&QTimer::timeout,[=](){
//        Debug("check heart...");
//        sendInfo("heartbeat");
//        myheart.start(5*1000);
//    });
//    gameI->heartBeat.start(5*1000);

//    connect(&mytime,&QTimer::timeout,[=](){
//        gameI->saveNow("connectionLost.bak");
//        QMessageBox::critical(0,"糟糕,对方连接好像断开了呢","您的游戏已经保存至connectionLost.bak,请重新连接再来吧",QMessageBox::Yes);
//        exit(1);

//    });
//    connect(&myheart,&QTimer::timeout,[=](){
//        gameI->saveNow("connectionLost.bak");
//        QMessageBox::critical(0,"糟糕,对方连接好像断开了呢","您的游戏已经保存至connectionLost.bak,请重新连接再来吧",QMessageBox::Yes);
//        exit(2);
//    });



//    sendInfo("connect_success");
//    sendInfo("my_color",gameI->myColor);
//    sendInfo("now_color",gameI->nowColor);
//    waitingDialog->hide();
//    switcher->showInterface("game");

    emit tcpNewConnectionAdd();
}



void Tcp::connectionLost(){
    //more...
}
void Tcp::receiveInfo(int id)
{
    //Debug("tcp receive :"+QString::number(cache.size()));
    while (socket[id]->canReadLine()){
        QString info=socket[id]->readLine();
        if (info.contains("__START__")){
            //mytime.start(3*1000);
            cache[id]="";
        }else if (info.contains("__END__")){
            //mytime.stop();
            //emit tcpReceiveInfo(cache);
            dealInfo(id,cache[id]);
            //Debug("tcp receive info:"+cache);
//            package->packageReceive(cache[now]); !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            cache[id]="";
        }else{
            cache[id]+=info;
        }
    }

}

void Tcp::sendInfo(int id,QString info){
    Debug(QString("send info to %1: %2").arg(id).arg(info));
    info.replace(" ","@@");
    info.replace("\n","##");
    QString str=info;
    QTextStream(&info)<<"\n\n__START__\n\n"<<str<<"\n\n__END__\n\n";
    QByteArray byte;
    byte.append(info);
    socket[id]->write(byte.data());

}

void Tcp::sendInfo(int id,QString name,int num){
    QString info;
    QTextStream(&info)<<"\n"<<name<<"\n"<<num<<"\n";
    sendInfo(id,info);
}
void Tcp::sendInfo(int id,QString name, int num1,int num2){
    QString info;
    QTextStream(&info)<<"\n"<<name<<"\n"<<num1<<"\n"<<num2<<"\n";
    tcp->sendInfo(id,info);
}
void Tcp::sendInfo(int id,QString name,QString str){
    QString info;
    QTextStream(&info)<<"\n"<<name<<"\n"<<str<<"\n";
    tcp->sendInfo(id,info);
}

void Tcp::sendInfo(int id,QString name,QString info1,QString info2){
    QString info;
    QTextStream(&info)<<"\n"<<name<<"\n"<<info1<<"\n"<<info2<<"\n";
    tcp->sendInfo(id,info);
}

void Tcp::sendInfoStr(int id,QString name,QString info){
    info.replace(" ","$$");
    info.replace("\n","^^");
    sendInfo(id,name,info);
}



void Tcp::dealInfo(int id,QString info){
    info.trimmed();
    info.replace("@@"," ");
    info.replace("##","\n");
    Debug(QString("receive from %1: %2").arg(id).arg(info));

    QTextStream stream(&info);
    QString head;
    stream>>head;

    if (head=="shoudao"){
        Debug("hehe");
    }else if (head=="login_request"){
        QString account,password;
        stream>>account>>password;
        int now=findUser(account);
        if (now==-1){
            sendInfo(id,"reply_login_request","refuse","no_account");
        }else{
            if (userL[now].password!=password){
                sendInfo(id,"reply_login_request","refuse","pasword_wrong");
            }else{
                userL[now].id=id;
                sendInfo(id,"reply_login_request","success");
                sendInfo(id,"nickname",userL[now].nickname);
                sendInfo(id,"sign",userL[now].sign);
            //    sendInfo("picture",user.picture);
            }
        }
    }else if (head=="require_linkman"){
        QString info;
        QTextStream sm(&info);
        int count=0;
        for (int i=0;i<userL.size();i++) if (userL[i].id!=id) count++;
        sm<<"\n"<<count<<"\n";
        for (int i=0;i<userL.size();i++) if (userL[i].id!=id){
            sm<<"\n"<<userL[i].nickname<<"\n"<<userL[i].account<<"\n";
        }
        sendInfo(id,"reply_require_linkman",info);
    }else if (head=="require_newchat"){
        QString account;
        stream>>account;
        int now;
        findUser(account);
        if (now!=-1){
            sendInfo(now,"newchat_request",userL[i].account);
            sendInfo(id,"newchat_request",account);
        }
//        if (now==-1){
//            //sendInfo(id,"reply_require_newchat","fail");
//        }else{

//            QString info;
//            QTextStream sm(&info);
//            sm<<"\n"<<"success"<<"\n";
//            sm<<"\n"<<userL[now].account<<"\n";
//            sm<<"\n"<<userL[now].nickname<<"\n";
//            sm<<"\n"<<userL[now].sign<<"\n";
//            sendInfo(id,"reply_require_newchat",info);
//        }
    }else if (head=="talking_message"){
        QString account,info;
        stream>>account,info;
        int now=findUser(account);
        if (now!=-1) sendInfo(id,"message_from",account,info);
    }else if (head=="require_talking_userInfo"){
        QString account,info;
        int now=findUser(account);
        if (now!=-1){
            QTextStream sm(&info);
            sm<<"\n"<<userL[now].account<<"\n";
            sm<<"\n"<<userL[now].nickname<<"\n";
            sm<<"\n"<<userL[now].sign<<"\n";
            sendInfo(id,"talking_info",info);
        }
    }
}
