#ifndef FANGTANG_H
#define FANGTANG_H

#include <QWidget>

namespace Ui {
class fangtang;
}

class fangtang : public QWidget
{
    Q_OBJECT

public:
    explicit fangtang(QWidget *parent = 0);
    ~fangtang();

private:
    Ui::fangtang *ui;
};

#endif // FANGTANG_H
