
#include "hpLabel.h"

HPLabel::HPLabel(QWidget *parent):QLabel{parent}
{
    heartFull = QPixmap(":/source/picture/startGame/heartFull.png");
    heartEmpty = QPixmap(":/source/picture/startGame/heartEmpty.png");
    setPixmap(heartFull);
    setGeometry(1220, 44, 32, 32);
    show();
}

void HPLabel::loseHP()
{
     setPixmap(heartEmpty);
}

void HPLabel::gainHP()
{
 setPixmap(heartFull);
}

