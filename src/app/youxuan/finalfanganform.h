#ifndef FINALFANGANFORM_H
#define FINALFANGANFORM_H

#include <QWidget>

namespace Ui {
class FinalFanganForm;
}

class FinalFanganForm : public QWidget
{
    Q_OBJECT

public:
    explicit FinalFanganForm(QWidget *parent = 0);
    ~FinalFanganForm();

private:
    Ui::FinalFanganForm *ui;
};

#endif // FINALFANGANFORM_H
