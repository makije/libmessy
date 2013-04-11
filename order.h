#ifndef ORDER_H
#define ORDER_H

#include <string>

using namespace std;

class Order
{
private:
    int red;
    int blue;
    int yellow;
    string orderId;
    string status;
    string ticket;
public:
    Order();

    int getRed();
    int getBlue();
    int getYellow();
    string getStatus();
    string getTicket();
    string getOrderId();

    void setRed(int);
    void setBlue(int);
    void setYellow(int);
    void setStatus(string);
    void setTicket(string);
    void setOrderId(string);
};

#endif // ORDER_H
