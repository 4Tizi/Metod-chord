#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>

class Client : public QObject
{
    Q_OBJECT

public:
    explicit Client(QObject *parent = nullptr);
    void connectToServer();
    void sendRegistration(const QString &username, const QString &password, const QString &email);
    void sendAuthentication(const QString &username, const QString &password);
    void sendTextAndImage(const QString &text, const QString &imagePath);

signals:
    void receivedResponse(const QString &response);
    void authenticationSuccess();
    void imageReceived(const QByteArray &imageData);

private slots:
    void onConnected();
    void onReadyRead();

private:
    QTcpSocket *mTcpSocket;
    QByteArray buffer;
};

#endif // CLIENT_H
