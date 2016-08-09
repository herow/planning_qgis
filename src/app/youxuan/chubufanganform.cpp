#include "chubufanganform.h"
#include "ui_chubufanganform.h"

ChuBuFangAnForm::ChuBuFangAnForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChuBuFangAnForm)
{
    ui->setupUi(this);
}

ChuBuFangAnForm::~ChuBuFangAnForm()
{
    delete ui;
}
