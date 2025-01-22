#ifndef DBUSINTERFACE_H
#define DBUSINTERFACE_H

#include <QObject>
#include <QString>
#include <QDBusMessage>
#include <QDBusConnection>

class DbusInterface : public QObject
{
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "org.example.MessageService2")

public:
    explicit DbusInterface(QObject *parent = nullptr);
    Q_INVOKABLE void sendMessageToApp1(const QString &message);

signals:
    void messageReceivedFromApp1(const QString &message);

public slots:
    void receiveMessageFromApp1(const QString &message);
};

#endif //DBUSINTERFACE_H
