#ifndef ORDERHANDLER_H
#define ORDERHANDLER_H

#include <QXmlDefaultHandler>
#include "order.h"

class OrderHandler : public  QXmlDefaultHandler
{
private:

    bool inOrder;
    bool inBricks;
    bool inRed;
    bool inBlue;
    bool inYellow;
    bool inStatus;

    Order order;

public:
    OrderHandler();

    bool startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts);
    bool endElement(const QString &namespaceURI, const QString &localName, const QString &qName);
    bool characters(const QString &ch);

    Order getOrder();
};

#endif // ORDERHANDLER_H
