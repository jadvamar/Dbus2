#include "dbusinterface.h"
#include <QDebug>

DbusInterface::DbusInterface(QObject *parent) : QObject(parent)
{
    if (QDBusConnection::sessionBus().isConnected()){

        qDebug() << "Successfully connected to the D-Bus session bus.";

        QDBusConnection::sessionBus().registerService("org.example.MessageService2");
        QDBusConnection::sessionBus().registerObject(
            "/org/example/MessageService2",
            this,
            QDBusConnection::ExportAllSlots | QDBusConnection::ExportAllSignals
            );
    }
    else{
        qDebug() << "Failed to connect to the D-Bus session bus:"
                 << QDBusConnection::sessionBus().lastError().message();
    }
}

void DbusInterface::sendMessageToApp1(const QString &message)
{
    QDBusMessage dbusMessage = QDBusMessage::createMethodCall(
        "org.example.MessageService1",
        "/org/example/MessageService1",
        "org.example.MessageService1",
        "receiveMessageFromApp2"
        );
    dbusMessage << message;

    QDBusMessage reply = QDBusConnection::sessionBus().call(dbusMessage);

    if (reply.type() == QDBusMessage::ErrorMessage) {
        qDebug() << "Error sending message to App1:" << reply.errorMessage();
    }
    else if()
}

void DbusInterface::receiveMessageFromApp1(const QString &message)
{
    qDebug() << "Message received from App1:" << message;
    emit messageReceivedFromApp1(message);
}
