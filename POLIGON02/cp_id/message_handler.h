#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include <QAbstractMessageHandler>

class message_handler : public QAbstractMessageHandler
{
public:
        message_handler();
        QString statusMessage() const;
        int line() const;
        int column() const;

protected:
        virtual void handleMessage(QtMsgType type, const QString &description, const QUrl &identifier, const QSourceLocation &sourceLocation);

private:
        QtMsgType m_messageType;
        QString m_description;
        QSourceLocation m_sourceLocation;
};

#endif // MESSAGE_HANDLER
