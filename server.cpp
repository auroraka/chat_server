#include "server.h"
#include "tcp.h"
#include "userinfo.h"
#include "enviroment.h"
#include "ui_server.h"

Server::Server(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);    


    loadUserInfo();

    tcp->makeServer();
    ui->label->setText(tr("服务器已创建在\n\nIP: %1\n端口: %2\n\n"
                            "可以打开客户端登陆了.")
                         .arg(getIP()).arg(tcp->server->serverPort()));
}

Server::~Server()
{
    delete ui;
}

void Server::loadUserInfo(){
    UserInfo admin;
    admin.account="admin";
    admin.password="admin";
    admin.nickname="admin";
    admin.sign="none";
    addUser(admin);

    UserInfo user1;
    user1.account="zhangsan";
    user1.password="123456";
    user1.nickname="张三";
    user1.sign="呵呵哒";
    addUser(user1);

    UserInfo user2;
    user2.account="zhangzhe";
    user2.password="123456";
    user2.nickname="长者";
    user2.sign="你们哪...Naive!";
    addUser(user2);
}

void Server::on_pushButton_clicked()
{
    tcp->server->close();
    exit(0);
}
