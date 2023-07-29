
#ifndef HPLABEL_H
#define HPLABEL_H

#include <QLabel>


class HPLabel : public QLabel
{
public:
    HPLabel(QWidget *parent = nullptr);
    void loseHP();
    void gainHP();
private:
    QPixmap heartFull;
    QPixmap heartEmpty;
};

#endif // HPLABEL_H
