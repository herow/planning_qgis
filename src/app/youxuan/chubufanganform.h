#ifndef CHUBUFANGANFORM_H
#define CHUBUFANGANFORM_H

#include <QWidget>

namespace Ui {
class ChuBuFangAnForm;
}

class ChuBuFangAnForm : public QWidget
{
    Q_OBJECT

public:
    explicit ChuBuFangAnForm(QWidget *parent = 0);
    ~ChuBuFangAnForm();

private:
    Ui::ChuBuFangAnForm *ui;
};

#endif // CHUBUFANGANFORM_H
