
#ifndef ARCHIVE_H
#define ARCHIVE_H


#include <QObject>
#include <QSettings>
#include "GraphicsButton.h"
#include <QGraphicsTextItem>
#include <QGraphicsScene>
#include <QFontDatabase>
class Archive : public QObject
{
    Q_OBJECT
public:
    explicit Archive(int index,QGraphicsScene *scence, QObject *parent = nullptr);
    void hideAndDestory();
signals:
    void saveArchive(int sign);
    void loadArchive(int sign);
private:
    int a_sign;
    GraphicsButton *a_Btn;
    QGraphicsTextItem *a_explain;
    QGraphicsScene *a_scence;
    QSettings *archive;

    void mouseClicked();

};

#endif // ARCHIVE_H
