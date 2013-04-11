#ifndef ORDERRESPONSEHANDLER_H
#define ORDERRESPONSEHANDLER_H

#include <QString>
#include <QXmlDefaultHandler>

class OrderResponseHandler : public  QXmlDefaultHandler
{

private:
    QString ticket;

    bool inTicket;

public:
    OrderResponseHandler();

    bool startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts);
    bool endElement(const QString &namespaceURI, const QString &localName, const QString &qName);
    bool characters(const QString &ch);

    QString getTicket();
};

#endif // ORDERRESPONSEHANDLER_H
