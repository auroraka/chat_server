#ifndef ENVIROMENT
#define ENVIROMENT

#include <QString>
#include <QHostInfo>
#include <QTextEdit>

QString getIP();

QString getHostName();

bool checkIP(QString ip);

void SystemError(QWidget* obj=0);

extern QTextEdit *debugWindow;

void makeDebugWindow();
void Debug(QString info);

#endif // ENVIROMENT

