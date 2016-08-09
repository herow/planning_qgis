#include "qgsfactorsettingpage.h"
#include <QLabel>
#include <QMap>

QgsFactorSettingPage::QgsFactorSettingPage(QWidget *parent) :
    QWizardPage(parent)
{
	setWindowTitle(QString::fromLocal8Bit("����Ȩ������"));

	QMap<QString,QString> data;
	data.insert(QString::fromLocal8Bit("�߳�"),QString::number(0.15));
	data.insert(QString::fromLocal8Bit("�¶�"),QString::number(0.13));
	data.insert(QString::fromLocal8Bit("�����ֺ�"),QString::number(0.13));
	data.insert(QString::fromLocal8Bit("ֲ��"),QString::number(0.17));
	data.insert(QString::fromLocal8Bit("ˮ��"),QString::number(0.10));
	data.insert(QString::fromLocal8Bit("����"),QString::number(0.17));
	data.insert(QString::fromLocal8Bit("�˿�"),QString::number(0.15));

	QStringList heads;
	heads<<QString::fromLocal8Bit("����")<<QString::fromLocal8Bit("Ȩ��");

	mSettingWidget = new QgsSettingWidget(heads,data);
	layout = new QGridLayout;
	layout->addWidget(mSettingWidget);
	setLayout(layout);
}

QgsFactorSettingPage::~QgsFactorSettingPage()
{
	delete mSettingWidget;
	delete layout;
}
QMap<QString,QString> QgsFactorSettingPage::getTableDate()
{
	QMap<QString,QString> maps;
	
	QTableWidget *tableWidget = mSettingWidget->getTableWidget();
	int cols = tableWidget->columnCount();
	int rows = tableWidget->rowCount();
	for (int i = 0;i<rows;i++)
	{		
		maps.insert(tableWidget->item(i,0)->text(),tableWidget->item(i,1)->text());
	}
	return maps;
}
QStringList QgsFactorSettingPage::getFactors()
{
	QStringList factors;

	QTableWidget *tableWidget = mSettingWidget->getTableWidget();
	int cols = tableWidget->columnCount();
	int rows = tableWidget->rowCount();
	for (int i = 0;i<rows;i++)
	{		
		factors<<tableWidget->item(i,0)->text();
	}
	return factors;

}