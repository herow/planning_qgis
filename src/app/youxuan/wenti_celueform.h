#ifndef WENTI_CELUEFORM_H
#define WENTI_CELUEFORM_H

#include <QWidget>

namespace Ui {
class WenTi_CeLueForm;
}

class WenTi_CeLueForm : public QWidget
{
    Q_OBJECT

public:
    explicit WenTi_CeLueForm(QWidget *parent = 0);
    ~WenTi_CeLueForm();

private:
    Ui::WenTi_CeLueForm *ui;
};

#endif // WENTI_CELUEFORM_H
