#include "carreraserveur.h"
#include <iostream>

using namespace std;

CArreraServeur::CArreraServeur(QObject *parent)
    : QObject{parent}
{}

CArreraServeur::~CArreraServeur(){}

bool CArreraServeur::startServeur(quint16 port)
{
    serverWebSocket = new QWebSocketServer(QStringLiteral("WebSocket Server"),
                                           QWebSocketServer::NonSecureMode, this);

    connect(serverWebSocket,&QWebSocketServer::newConnection,
            this,&CArreraServeur::onNewConnectionOfClient);

    if (serverWebSocket->listen(QHostAddress::Any,port)){
        return true;
    }else{
        return false;
    }
}

bool CArreraServeur::stopServeur(){
    if (serverWebSocket && serverWebSocket->isListening())
    {
        serverWebSocket->close(); // Fermeture du serveur

        // Fermeture de tout les connection au client
        for (QWebSocket *client : webSocketClients) {
            client->close();
            client->deleteLater();
        }

        // Clear de la list
        webSocketClients.clear();

        return true;
    }
    else{
        return false;
    }
}

void CArreraServeur::onNewConnectionOfClient(){
    QWebSocket *client = serverWebSocket->nextPendingConnection();
    connect(client,&QWebSocket::textFrameReceived, this,&CArreraServeur::onMessageReceived);
    connect(client,&QWebSocket::disconnected, this,&CArreraServeur::onClientDeconected);

    webSocketClients.append(client);
}

void CArreraServeur::onMessageReceived(const QString &message){
    QWebSocket *client = qobject_cast<QWebSocket *>(sender());
    if (!client) return;

    // Émettre un signal lorsqu'un message est reçu :
    emit messageReceived(message);

    // Préparer et envoyer une réponse JSON comme avant :
    QJsonObject response;
    response["message"] = "WebSocket response: Message Received";
    QString jsonResponse = QJsonDocument(response).toJson(QJsonDocument::Compact);

    client->sendTextMessage(jsonResponse);
}

void CArreraServeur::onClientDeconected(){
    QWebSocket *client = qobject_cast<QWebSocket *>(sender());
    if (client)
    {
        webSocketClients.removeAll(client);
        client->deleteLater();
    }
}
