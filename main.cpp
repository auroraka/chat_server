#include "server.h"
#include "tcp.h"
#include "userinfo.h"
#include "enviroment.h"
#include <QApplication>
#include <QTextEdit>

QTextEdit *debugWindow;
Tcp *tcp;
vector<UserInfo> userL;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    debugWindow = new QTextEdit;
    makeDebugWindow();

    tcp = new Tcp;

    Server w;
    w.move(1500,500);
    w.show();

    return a.exec();
}
