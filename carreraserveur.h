#ifndef CARRERASERVEUR_H
#define CARRERASERVEUR_H

#include <QObject>
#include <QWebSocketServer>
#include <QWebSocket>
#include <QJsonDocument>
#include <QJsonObject>

class CArreraServeur : public QObject
{
    Q_OBJECT
private:
    QWebSocketServer *serverWebSocket;
    QList <QWebSocket*> webSocketClients;
    volatile bool signalEmitted = false;
public:
    explicit CArreraServeur(QObject *parent = nullptr);
    ~CArreraServeur();
    bool startServeur(quint16 port);
    bool stopServeur();
private slots:
    void onNewConnectionOfClient();
    void onMessageReceived(const QString &message);
    void onClientDeconected();
signals:
    void messageReceived(const QString &message);
};

#endif // CARRERASERVEUR_H
