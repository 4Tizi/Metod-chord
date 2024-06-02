#include <QApplication>
#include "mainwindow.h"
#include "loginwindow.h"
#include "authwindow.h"
#include "registerwindow.h"
#include "client.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Client client;
    LoginWindow loginWindow(&client);
    AuthWindow authWindow(&client);
    RegisterWindow registerWindow(&client);

    QObject::connect(&loginWindow, &LoginWindow::showAuthWindow, [&]() {
        loginWindow.hide();
        authWindow.show();
    });

    QObject::connect(&loginWindow, &LoginWindow::showRegisterWindow, [&]() {
        loginWindow.hide();
        registerWindow.show();
    });

    QObject::connect(&authWindow, &AuthWindow::backToLogin, [&]() {
        authWindow.hide();
        loginWindow.show();
    });

    QObject::connect(&registerWindow, &RegisterWindow::backToLogin, [&]() {
        registerWindow.hide();
        loginWindow.show();
    });

    QObject::connect(&authWindow, &AuthWindow::showMainWindow, [&]() {
        authWindow.hide();
        MainWindow *mainWindow = new MainWindow;
        mainWindow->show();
    });

    loginWindow.show();
    return a.exec();
}
