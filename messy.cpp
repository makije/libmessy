#include "messy.h"
#include <QNetworkAccessManager>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QEventLoop>
#include <QDateTime>
#include <QErrorMessage>

#include <stdio.h>

Messy::Messy(string orderUrl, string logUrl, QObject *parent) : QObject(parent)
{
    this->orderUrl = QString(orderUrl.c_str());
    this->logUrl = QString(logUrl.c_str());

    if(this->orderUrl.length() <= 0)
    {
        //errorHandler.showMessage("The order url is invalid");
        emit error("SIGNAL The order url is invalid");
    }

    if(this->logUrl.length() <= 0)
    {
        //errorHandler.showMessage("The log url is invalid");
        emit error("SIGNAL The log url is invalid");
    }

    this->manager = new QNetworkAccessManager(this);
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
}

Messy::~Messy()
{
    delete manager;
}

Order Messy::getOrder()
{
    reader.setContentHandler(&ordersHandler);
    reader.setErrorHandler(&ordersHandler);

    QXmlInputSource xmlSource;
    xmlSource.setData(getReplyAsPlainText(this->orderUrl));

    reader.parse(xmlSource);

    QVector<QString> orders = this->ordersHandler.getOrders();

    reader.setContentHandler(&orderHandler);
    reader.setErrorHandler(&orderHandler);

    int orderToProces = 0;

    foreach(QString s, orders)
    {
        xmlSource.setData(getReplyAsPlainText(s));
        reader.parse(xmlSource);

        QStringList list = s.split("/");
        Order order = orderHandler.getOrder();
        order.setOrderId(list.takeAt(list.size() - 1).toAscii().data());
        if(order.getStatus().compare("ready") == 0)
        {
            QString response = getReplyAsPlainTextFromPut(s, "<?xml version=\"1.0\" encoding=\"utf-8\"?><order><status>taken</status></order>");

            if(httpStatusCode == 200)
            {
                reader.setContentHandler(&orderResponseHandler);
                reader.setErrorHandler(&orderResponseHandler);
                xmlSource.setData(response);
                reader.parse(xmlSource);
                order.setTicket(orderResponseHandler.getTicket().toAscii().data());
                order.setStatus("taken");
                return order;
            }
            else
            {
                qDebug() << "We didnt get the order, damn";
            }
            orderToProces++;
            if(orderToProces > 0)
                break;
        }
    }

    Order order;
    order.setStatus("failed");

    return order;
}

void Messy::replyFinished(QNetworkReply *reply)
{
    if(reply->error())
    {
        //errorHandler.showMessage(reply->errorString());
        emit error("SIGNAL " + reply->errorString());
    }

    this->reply = QString(reply->readAll());
    this->httpStatusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    emit replyReady();
}

QString Messy::getReplyAsPlainText(QString s)
{
    QEventLoop loop;
    loop.connect(this, SIGNAL(replyReady()), SLOT(quit()));
    manager->get(QNetworkRequest(QUrl(s)));
    loop.exec();

    return this->reply;
}

QString Messy::getReplyAsPlainTextFromPost(QString url, QString data)
{
    QEventLoop loop;
    loop.connect(this, SIGNAL(replyReady()), SLOT(quit()));
    QNetworkRequest request = QNetworkRequest(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant(QString("text/xml")));
    request.setHeader(QNetworkRequest::ContentLengthHeader, QVariant(qulonglong(data.size())));
    manager->post(request, data.toAscii());
    loop.exec();

    return this->reply;
}

QString Messy::getReplyAsPlainTextFromPut(QString url, QString data)
{
    QEventLoop loop;
    loop.connect(this, SIGNAL(replyReady()), SLOT(quit()));
    QNetworkRequest request = QNetworkRequest(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, QVariant(QString("text/xml")));
    request.setHeader(QNetworkRequest::ContentLengthHeader, QVariant(qulonglong(data.size())));
    manager->put(request, data.toAscii());
    loop.exec();

    return this->reply;
}

void Messy::log(string event, string comment)
{
    QDateTime time = QDateTime::currentDateTime();

    QString data = QString("<?xml version=\"1.0\" encoding=\"utf-8\"?><log_entry><event>" + QString(event.c_str()) + "</event><time>" + time.toString("yyyy-MM-dd hh:mm:ss") + "</time><cell_id>4</cell_id><comment>" + QString(comment.c_str()) + "</comment></log_entry>");

    getReplyAsPlainTextFromPost(this->logUrl, data);
}

bool Messy::deleteOrder(Order o)
{
    QEventLoop loop;
    loop.connect(this, SIGNAL(replyReady()), SLOT(quit()));
    QString url = QString("http://192.168.0.100/orders/" + QString(o.getOrderId().c_str()) + "/" + QString(o.getTicket().c_str()));
    QNetworkRequest request = QNetworkRequest(QUrl(url));
    manager->deleteResource(request);
    loop.exec();

    if(httpStatusCode == 200)
        return true;
    else
        return false;
}
