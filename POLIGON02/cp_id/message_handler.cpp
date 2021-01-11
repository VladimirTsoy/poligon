#include "message_handler.h"

message_handler::message_handler(): QAbstractMessageHandler(0)
{
}

QString message_handler::statusMessage() const
{
    return m_description;
}

int message_handler::line() const
{
    return m_sourceLocation.line();
}

int message_handler::column() const
{
    return m_sourceLocation.column();
}

void message_handler::handleMessage(QtMsgType type, const QString &description, const QUrl &identifier, const QSourceLocation &sourceLocation)
{
    Q_UNUSED(type);
    Q_UNUSED(identifier);

    m_messageType = type;
    m_description = description;
    m_sourceLocation = sourceLocation;
}
