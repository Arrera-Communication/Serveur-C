#include <QCoreApplication>
#include "carreraserveur.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CArreraServeur server;

    server.startServeur(12345);

    cout.flush();

    bool connect = QObject::connect(&server, &CArreraServeur::messageReceived, [](const QString nameSoft,const QString &message){
        cout << nameSoft.toStdString() << " send " << message.toStdString();
        cout.flush();
    });

    if (!connect){
        cout << "erreur" << endl;
    }



    return a.exec();
}
