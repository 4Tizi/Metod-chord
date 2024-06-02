#ifndef CLIENTINTERFACE_H
#define CLIENTINTERFACE_H

#include <QObject>
#include <QTcpSocket>

class ClientInterface : public QObject
{
    Q_OBJECT

public:
    explicit ClientInterface(QObject *parent = nullptr);
    void connectToServer(const QString& host, quint16 port);
    void sendAuthRequest(const QString& username, const QString& password);
    void sendRegRequest(const QString& username, const QString& password, const QString& email);

signals:
    void responseReceived(const QString& response);

private slots:
    void onReadyRead();

private:
    QTcpSocket *mTcpSocket;
};

#endif // CLIENTINTERFACE_H
