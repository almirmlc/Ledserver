#ifndef LEDSERVER_H
#define LEDSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include "gpio.h"



class LedServer : public QObject
{
    Q_OBJECT
public:
    explicit LedServer(quint16 port, QObject *parent = nullptr);
    void start();

signals:

public slots:
    void myNewConnection();
    void myClientDisconnect();
    void myServerRead();

private:
    // Server:
    QTcpServer* m_server;
    QTcpSocket* m_socket;
    quint16 m_port;

    // Ansteuerung LEDs
    Gpio* m_gpio;

};

#endif // LEDSERVER_H
