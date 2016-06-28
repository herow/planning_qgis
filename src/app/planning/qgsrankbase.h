#ifndef QGSRANKBASE_H
#define QGSRANKBASE_H

#include <QWidget>
#include "ui_rankbase.h"

class QgsRankBase : public QWidget,private Ui::QgsRank
{
    Q_OBJECT
public:
    explicit QgsRankBase(QWidget *parent = 0);

signals:

public slots:
};

#endif // QGSRANKBASE_H
