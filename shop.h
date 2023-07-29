
#ifndef SHOP_H
#define SHOP_H


#include <QObject>
#include <QPixmap>

class Shop : public QObject
{
    Q_OBJECT
public:
    explicit Shop(QString name,QPixmap icon,int price,int level,int max_level,QObject *parent = nullptr);

    void setPrice(int newPrice);
    int getPrice() const;

    void setLevel(int newLevel);
    int getLevel() const;
    int getMaxLevel()const;

    QPixmap getIcon() const;

    QString getName() const;

signals:
private:
    int s_price;
    int s_level;
    int s_max_level;
    QPixmap s_icon;
    QString s_name;
};

#endif // SHOP_H
