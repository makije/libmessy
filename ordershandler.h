#ifndef ORDERSHANDLER_H
#define ORDERSHANDLER_H

#include <QXmlDefaultHandler>
#include <QString>
#include <QVector>

class OrdersHandler : public QXmlDefaultHandler
{
private:
    bool inOrders;
    bool inOrder;

    QVector<QString> orders;

public:
    OrdersHandler();

    bool startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts);
    bool endElement(const QString &namespaceURI, const QString &localName, const QString &qName);
    bool characters(const QString &ch);

    QVector<QString> getOrders();
};

#endif // ORDERSHANDLER_H
