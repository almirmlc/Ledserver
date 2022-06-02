#include "ledserver.h"
#include "config.h"

LedServer::LedServer(quint16 port, QObject *parent) : QObject(parent), m_port(port)
{
    m_gpio = new Gpio(this);
    m_server = new QTcpServer(this);
    connect(m_server, &QTcpServer::newConnection, this, &LedServer::myNewConnection);
}

void LedServer::start()
{
    m_server->listen(QHostAddress::Any, m_port);
}

// Client hat Verbindung zum Server aufgebaut
void LedServer::myNewConnection()
{
    qDebug() << "Client hat Verbindung zum Server aufgebaut";

    m_socket = m_server->nextPendingConnection();
    qDebug() << "Bitte Zahl von 0 bis 15 eingeben: ";
    connect(m_socket, &QTcpSocket::disconnected, this, &LedServer::myClientDisconnect);
    connect(m_socket, &QTcpSocket::readyRead, this, &LedServer::myServerRead);

}

// Client hat Verbindung zum Server getrennt
void LedServer::myClientDisconnect()
{
    qDebug() << "Client hat Verbindung zum Server getrennt";
    m_socket->close();

    for (int a = 0; a < 4; a++)
        {
            m_gpio->set(LEDS[a], 0);
        }
}

// Client hat eine Zahl (0...15) zum Server gesendet
void LedServer::myServerRead()
{
    while (m_socket->bytesAvailable())
    {
        QString message = m_socket->readAll();

        int zahl = message.toInt();
        qDebug() << zahl;

        if (zahl >= 0 && zahl < 16)
        {
            qDebug() << "OK";
            m_gpio->set(zahl);
        }

        qDebug() << "Bitte Zahl von 0 bis 15 eingeben: ";

    }
}
