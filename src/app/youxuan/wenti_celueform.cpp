#include "wenti_celueform.h"
#include "ui_wenti_celueform.h"

WenTi_CeLueForm::WenTi_CeLueForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WenTi_CeLueForm)
{
    ui->setupUi(this);
}

WenTi_CeLueForm::~WenTi_CeLueForm()
{
    delete ui;
}
