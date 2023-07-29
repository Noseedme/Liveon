
#include "shop.h"



Shop::Shop(QString name, QPixmap icon, int price, int level, int max_level, QObject *parent)
    : QObject{parent},s_price(price),s_level(level),s_max_level(max_level)
{
    this->s_name = name;
    this->s_icon = icon;
}

void Shop::setPrice(int newPrice)
{
    s_price = newPrice;
}

int Shop::getPrice() const
{
    return s_price;
}

void Shop::setLevel(int newLevel)
{
    s_level = newLevel;
}

int Shop::getLevel() const
{
    return s_level;
}

int Shop::getMaxLevel() const
{
    return s_max_level;
}

QPixmap Shop::getIcon() const
{
    return s_icon;
}

QString Shop::getName() const
{
    return s_name;
}
