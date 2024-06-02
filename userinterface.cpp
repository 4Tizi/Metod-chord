#include "userinterface.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>

UserInterface::UserInterface(QWidget *parent) : QWidget(parent), client(new ClientInterface(this))
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    usernameInput = new QLineEdit(this);
    passwordInput = new QLineEdit(this);
    emailInput = new QLineEdit(this);
    QPushButton *loginButton = new QPushButton("Login", this);
    QPushButton *registerButton = new QPushButton("Register", this);
    responseLabel = new QLabel(this);

    layout->addWidget(new QLabel("Username:", this));
    layout->addWidget(usernameInput);
    layout->addWidget(new QLabel("Password:", this));
    layout->addWidget(passwordInput);
    layout->addWidget(new QLabel("Email (for registration):", this));
    layout->addWidget(emailInput);
    layout->addWidget(loginButton);
    layout->addWidget(registerButton);
    layout->addWidget(responseLabel);

    connect(loginButton, &QPushButton::clicked, this, &UserInterface::onLoginButtonClicked);
    connect(registerButton, &QPushButton::clicked, this, &UserInterface::onRegisterButtonClicked);
    connect(client, &ClientInterface::responseReceived, this, &UserInterface::onResponseReceived);

    client->connectToServer("127.0.0.1", 33333);
}

void UserInterface::onLoginButtonClicked()
{
    QString username = usernameInput->text();
    QString password = passwordInput->text();
    client->sendAuthRequest(username, password);
}

void UserInterface::onRegisterButtonClicked()
{
    QString username = usernameInput->text();
    QString password = passwordInput->text();
    QString email = emailInput->text();
    client->sendRegRequest(username, password, email);
}

void UserInterface::onResponseReceived(const QString& response)
{
    responseLabel->setText(response);
}
