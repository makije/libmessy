#ifndef MESSY_H
#define MESSY_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QString>
#include <QNetworkReply>
#include <QXmlSimpleReader>
#include <QErrorMessage>

#include <string.h>

#include "ordershandler.h"
#include "orderhandler.h"
#include "orderresponsehandler.h"
#include "order.h"

class Messy : public QObject
{
    Q_OBJECT

private:
    //QErrorMessage errorHandler;
    QString orderUrl;
    QString logUrl;


    QNetworkAccessManager* manager;
    QString reply;
    int httpStatusCode;

    OrdersHandler ordersHandler;
    OrderHandler orderHandler;
    OrderResponseHandler orderResponseHandler;
    QXmlSimpleReader reader;

    QString getReplyAsPlainText(QString);
    QString getReplyAsPlainTextFromPost(QString, QString);
    QString getReplyAsPlainTextFromPut(QString, QString);


public:
    explicit Messy(string orderurl, string logurl, QObject *parent = 0);
    ~Messy();
    Order getOrder();
    bool deleteOrder(Order);
    void log(string, string);

signals:
    void replyReady();
    void error(QString);

public slots:
    void replyFinished(QNetworkReply* reply);

};

#endif // MESSY_H
