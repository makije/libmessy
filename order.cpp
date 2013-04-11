#include "order.h"

using namespace std;

Order::Order()
{
    this->blue = 0;
    this->red = 0;
    this->yellow = 0;
    this->status = "failed";
    this->orderId = "failed";
    this->ticket = "";
}

int Order::getRed()
{
    return this->red;
}
int Order::getBlue()
{
    return this->blue;
}

int Order::getYellow()
{
    return this->yellow;
}

string Order::getStatus()
{
    return this->status;
}

void Order::setRed(int amount)
{
    this->red = amount;
}

void Order::setBlue(int amount)
{
    this->blue = amount;
}

void Order::setYellow(int amount)
{
    this->yellow = amount;
}

void Order::setStatus(string name)
{
    this->status = name;
}

string Order::getTicket()
{
    return this->ticket;
}

void Order::setTicket(string ticket)
{
    this->ticket = ticket;
}

string Order::getOrderId()
{
    return this->orderId;
}

void Order::setOrderId(string orderId)
{
    this->orderId = orderId;
}
