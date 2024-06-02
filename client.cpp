#include "client.h"

Client::Client(QObject *parent) : QObject(parent)
{
    mTcpSocket = new QTcpSocket(this);
    connect(mTcpSocket, &QTcpSocket::connected, this, &Client::onConnected);
    connect(mTcpSocket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
    connectToServer();
}

void Client::connectToServer()
{
    mTcpSocket->connectToHost("127.0.0.1", 33333);
}

void Client::sendRegistration(const QString &username, const QString &password, const QString &email)
{
    if (mTcpSocket->state() == QAbstractSocket::ConnectedState) {
        QString message = QString("reg&%1&%2&%3").arg(username).arg(password).arg(email);
        mTcpSocket->write(message.toUtf8());
    }
}

void Client::sendAuthentication(const QString &username, const QString &password)
{
    if (mTcpSocket->state() == QAbstractSocket::ConnectedState) {
        QString message = QString("auth&%1&%2").arg(username).arg(password);
        mTcpSocket->write(message.toUtf8());
    }
}

void Client::onConnected()
{
    qDebug() << "Connected to server";
}

void Client::onReadyRead()
{
    QByteArray data = mTcpSocket->readAll();
    QString response = QString::fromUtf8(data);
    emit receivedResponse(response);

    if (response.contains("Authentication successful")) {
        emit authenticationSuccess();
    }
}
