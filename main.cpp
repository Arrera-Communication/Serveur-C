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

    bool connect = QObject::connect(&server, &CArreraServeur::messageReceived, [&server](const QString nameSoft, const QString &message) {
        cout << nameSoft.toStdString() << " send " << message.toStdString();
        cout.flush();
        if (!server.sendMessage("socket-client", "Je suis ton maitre")) {
            cout << "Erreur" << endl;
        }
    });


    if (!connect){
        cout << "erreur" << endl;
    }




    return a.exec();
}
