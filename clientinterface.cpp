#include "clientinterface.h"
#include <QHostAddress>

ClientInterface::ClientInterface(QObject *parent) : QObject(parent), mTcpSocket(new QTcpSocket(this))
{
    connect(mTcpSocket, &QTcpSocket::readyRead, this, &ClientInterface::onReadyRead);
}

void ClientInterface::connectToServer(const QString& host, quint16 port)
{
    mTcpSocket->connectToHost(QHostAddress(host), port);
    if (mTcpSocket->waitForConnected(3000)) {
        qDebug() << "Connected to server";
    } else {
        qDebug() << "Failed to connect to server";
    }
}

void ClientInterface::sendAuthRequest(const QString& username, const QString& password)
{
    QString request = QString("auth&%1&%2").arg(username, password);
    mTcpSocket->write(request.toUtf8());
}

void ClientInterface::sendRegRequest(const QString& username, const QString& password, const QString& email)
{
    QString request = QString("reg&%1&%2&%3").arg(username, password, email);
    mTcpSocket->write(request.toUtf8());
}

void ClientInterface::onReadyRead()
{
    QByteArray response = mTcpSocket->readAll();
    emit responseReceived(QString::fromUtf8(response));
}
