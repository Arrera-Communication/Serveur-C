#include <QCoreApplication>
#include "carreraserveur.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CArreraServeur server;

    server.startServeur(12345);

    QObject::connect(&server, &CArreraServeur::messageReceived, [](const QString &message){
        cout << "Message :" << message.toStdString();
    });



    return a.exec();
}
