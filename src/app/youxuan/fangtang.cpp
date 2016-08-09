#include "fangtang.h"
#include "ui_fangtang.h"

fangtang::fangtang(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fangtang)
{
    ui->setupUi(this);
}

fangtang::~fangtang()
{
    delete ui;
}
