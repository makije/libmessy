#include "orderresponsehandler.h"

OrderResponseHandler::OrderResponseHandler()
{

}

bool OrderResponseHandler::startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts)
{
    if (qName.compare("ticket") == 0)
        inTicket = true;

    return true;
}

bool OrderResponseHandler::endElement(const QString &namespaceURI, const QString &localName, const QString &qName)
{
    if (qName.compare("ticket") == 0)
        inTicket = false;

    return true;
}

bool OrderResponseHandler::characters(const QString &ch)
{
    if(inTicket)
        ticket = ch;

    return true;
}

QString OrderResponseHandler::getTicket()
{
    return this->ticket;
}

