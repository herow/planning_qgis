#include "qgsdirectionpage.h"
#include "qgsdevelopindexdialog.h"
QgsDirectionPage::QgsDirectionPage()
{
    this->setupUi(this);
    connect(this->mDevelopFactorBtn,SIGNAL(clicked()),this,SLOT(developFactors()));
}
void QgsDirectionPage::developFactors()
{
    QgsDevelopIndexDialog* dlg = new QgsDevelopIndexDialog();
    dlg->show();
}
