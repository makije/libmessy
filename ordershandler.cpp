#include "ordershandler.h"

OrdersHandler::OrdersHandler()
{
    this->inOrders = false;
    this->inOrder = false;
}

bool OrdersHandler::startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts)
{
    if (qName.compare("orders") == 0)
        inOrders = true;
    else if (qName.compare("order") == 0)
        inOrder = true;

    return true;
}

bool OrdersHandler::endElement(const QString &namespaceURI, const QString &localName, const QString &qName)
{
    if (qName.compare("orders") == 0)
        inOrders = false;
    else if (qName.compare("order") == 0)
        inOrder = false;

    return true;
}

bool OrdersHandler::characters(const QString &ch)
{
    if (inOrders && inOrder)
    {
        orders.push_back(ch);
    }
    return true;
}

QVector<QString> OrdersHandler::getOrders()
{
    return this->orders;
}
