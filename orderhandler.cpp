
#include <QDebug>

#include "orderhandler.h"

OrderHandler::OrderHandler()
{
    this->inOrder = false;
    this->inBricks = false;
    this->inRed = false;
    this->inBlue = false;
    this->inYellow = false;
    this->inStatus = false;
}

bool OrderHandler::startElement(const QString &namespaceURI, const QString &localName, const QString &qName, const QXmlAttributes &atts)
{
    if(qName.compare("order") == 0)
        inOrder = true;
    else if(qName.compare("bricks") == 0)
        inBricks = true;
    else if(qName.compare("red") == 0)
        inRed = true;
    else if(qName.compare("blue") == 0)
        inBlue = true;
    else if(qName.compare("yellow") == 0)
        inYellow = true;
    else if(qName.compare("status") == 0)
        inStatus = true;

    return true;
}

bool OrderHandler::endElement(const QString &namespaceURI, const QString &localName, const QString &qName)
{
    if(qName.compare("order") == 0)
        inOrder = false;
    else if(qName.compare("bricks") == 0)
        inBricks = false;
    else if(qName.compare("red") == 0)
        inRed = false;
    else if(qName.compare("blue") == 0)
        inBlue = false;
    else if(qName.compare("yellow") == 0)
        inYellow = false;
    else if(qName.compare("status") == 0)
        inStatus = false;

    return true;
}

bool OrderHandler::characters(const QString &ch)
{
    if(inOrder && inBricks && inRed)
        order.setRed(ch.toInt());
    else if(inOrder && inBricks && inBlue)
        order.setBlue(ch.toInt());
    else if(inOrder && inBricks && inYellow)
        order.setYellow(ch.toInt());
    else if(inOrder && inStatus)
        order.setStatus(ch.toAscii().data());

    return true;
}

Order OrderHandler::getOrder()
{
    return this->order;
}
