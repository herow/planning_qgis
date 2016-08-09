#include "finalfanganform.h"
#include "ui_finalfanganform.h"

FinalFanganForm::FinalFanganForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FinalFanganForm)
{
    ui->setupUi(this);
}

FinalFanganForm::~FinalFanganForm()
{
    delete ui;
}
