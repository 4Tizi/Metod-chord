#include "client.h"
#include <QFile>
#include <QFileInfo>

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
        qDebug() << "Sent registration data to server:" << message;
    }
}

void Client::sendAuthentication(const QString &username, const QString &password)
{
    if (mTcpSocket->state() == QAbstractSocket::ConnectedState) {
        QString message = QString("auth&%1&%2").arg(username).arg(password);
        mTcpSocket->write(message.toUtf8());
        qDebug() << "Sent authentication data to server:" << message;
    }
}

void Client::sendTextAndImage(const QString &text, const QString &imagePath)
{
    if (mTcpSocket->state() == QAbstractSocket::ConnectedState) {
        QFile file(imagePath);
        if (file.open(QIODevice::ReadOnly)) {
            QByteArray imageData = file.readAll();
            qDebug() << "Image data size:" << imageData.size();
            QString message = QString("image&%1&%2&").arg(imagePath).arg(text);
            mTcpSocket->write(message.toUtf8() + imageData);
            qDebug() << "Sent text and image data to server.";
            file.close();
        } else {
            qDebug() << "Failed to open image file.";
        }
    } else {
        qDebug() << "Socket not connected.";
    }
}


void Client::onConnected()
{
    qDebug() << "Connected to server";
}

void Client::onReadyRead()
{
    buffer.append(mTcpSocket->readAll());

    // Check if the buffer contains a PNG image header
    if (buffer.startsWith("\x89PNG")) {
        qDebug() << "Received image data of size:" << buffer.size();
        emit imageReceived(buffer);
        buffer.clear();
    } else {
        QString response = QString::fromUtf8(buffer);
        qDebug() << "Received text data:" << response;
        emit receivedResponse(response);

        if (response.contains("Authentication successful")) {
            emit authenticationSuccess();
        }

        buffer.clear();
    }
}
