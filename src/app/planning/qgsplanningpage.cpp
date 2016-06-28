#include "qgsplanningpage.h"
#include "qgsecologicalindexdialog.h"

#include"qgsecologicalindexdialog.h"

QgsPlanningPage::QgsPlanningPage()
{
    this->setupUi(this);
    connect(this->mFactorBtn,SIGNAL(clicked()),this,SLOT(ecologicalIndex()));
}


void QgsPlanningPage::ecologicalIndex()
{
    QgsEcologicalIndexDialog* dlg = new QgsEcologicalIndexDialog();
    dlg->show();
}
