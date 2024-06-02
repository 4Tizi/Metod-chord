#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <QWidget>
#include "clientinterface.h"
#include <QLineEdit>
#include <QLabel>

class UserInterface : public QWidget
{
    Q_OBJECT

public:
    explicit UserInterface(QWidget *parent = nullptr);

private slots:
    void onLoginButtonClicked();
    void onRegisterButtonClicked();
    void onResponseReceived(const QString& response);

private:
    QLineEdit *usernameInput;
    QLineEdit *passwordInput;
    QLineEdit *emailInput;
    QLabel *responseLabel;
    ClientInterface *client;
};

#endif // USERINTERFACE_H
