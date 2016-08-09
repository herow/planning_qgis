#include "qgsplanningtoolbox.h"

#include "qgsecologicalwizard.h"
#include "qgsrasterreclassify.h"
#include "planningdialog.h"

QgsPlanningToolBox::QgsPlanningToolBox()
{
	this->setupUi(this);
	connect( mEcologicalToolBtn, SIGNAL(clicked()), this, SLOT(ecologyWizard()));
	connect( mPlanningToolBtn, SIGNAL(clicked()), this, SLOT(planningWizard()));
	connect( mDirectionToolBtn, SIGNAL(clicked()), this, SLOT(direction()));
	connect( mPatternToolBtn, SIGNAL(clicked()), this, SLOT(pattern()));
	connect( mScoreToolBtn, SIGNAL(clicked()), this, SLOT(score()));
}
void QgsPlanningToolBox::ecologyWizard()
{
	QgsEcologicalWizard *dlg = new QgsEcologicalWizard();
	dlg->show();
	
}
void QgsPlanningToolBox::planningWizard()
{
	PlanningDialog *dlg = new PlanningDialog();
	dlg->show();
}
void QgsPlanningToolBox::direction()
{
	QStringList heads;
	heads<<"type"<<"files";
	QStringList files;
	files<<"regions"<<"scores"<<"polulation"<<"result";
	QgsFilesSelectWidget *dlg = new QgsFilesSelectWidget(heads,files);
	dlg->show();
}
void QgsPlanningToolBox::pattern()
{
	QStringList heads;
	heads<<"type"<<"files";
	QStringList files;
	files<<"regions"<<"scores"<<"result";
	QgsFilesSelectWidget *dlg = new QgsFilesSelectWidget(heads,files);
	dlg->show();
}

inline QString range(double x, double y) 
{
	return QString::number(x).append("-").append(QString::number(y));
}


void QgsPlanningToolBox::score()
{
	QMap<QString,QString> data;
	data.insert(range(0.77,2.86),QString::number(1));
	data.insert(range(2.86,3.48),QString::number(2));
	data.insert(range(3.48,4.19),QString::number(3));
	data.insert(range(4.19,5.68),QString::number(4));
	QgsRasterReclassify *dlg = new QgsRasterReclassify(QString::fromLocal8Bit("生态适宜性综合得分"),data);
	dlg->show();
}