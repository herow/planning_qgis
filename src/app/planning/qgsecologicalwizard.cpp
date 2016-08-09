
#include <QFileInfo>
#include <QProgressDialog>
#include "qgsecologicalwizard.h"
#include "qgsapplication.h"
#include "qgsrastercalculator.h"
#include "qgsrasterlayer.h"
#include "qgisapp.h"

QgsEcologicalWizard::QgsEcologicalWizard(QWidget *parent) :
    QWizard(parent)
{
    mFactorsSetting = new QgsFactorSettingPage();
	mFilesSetting = new QgsFileSelectPage();

    setPage(QgsEcologicalWizard::factors,mFactorsSetting);
	setPage(QgsEcologicalWizard::files,mFilesSetting);
    //setPage(QgsEcologicalWizard::scores,mScoresSetting);

    this->setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
    setWizardStyle( QWizard::ModernStyle );
	setWindowTitle( tr("factors"));

    setOption( QWizard::NoBackButtonOnStartPage );
    setOption( QWizard::NoBackButtonOnLastPage );
 
    setTitleFormat(Qt::RichText);
    setSubTitleFormat(Qt::RichText);

    setButtonText(QWizard::NextButton, QString::fromLocal8Bit("��һ��>"));
	setButtonText(QWizard::CancelButton,QString::fromLocal8Bit("ȡ��"));
	setButtonText(QWizard::FinishButton,QString::fromLocal8Bit("��ʼ����"));

	setWindowTitle(QString::fromLocal8Bit("��̬����������"));
}

QgsEcologicalWizard::~QgsEcologicalWizard()
{
    delete mFactorsSetting;
    delete mScoresSetting;
}

void QgsEcologicalWizard::accept()
{
	//��ȡ������Ȩ��
	QMap<QString,QString> factorMap = mFactorsSetting->getTableDate();
	QStringList factorList = mFactorsSetting->getFactors();
	//��ȡ�ļ�·��
	QMap<QString,QString> filesMap = mFilesSetting->getTableData();
	//��ȡ�ļ�����·��
	QString savePath = mFilesSetting->getSavePath();
	//դ�����

	QString formatStr;
	QVector<QgsRasterCalculatorEntry> entries;
	QgsRectangle rect;
	int cols=0,rows=0;
	bool firstLayer = true;
	foreach(QString factor,factorList)
	{
		QFileInfo fileInfo(filesMap.value(factor));
		QString rasterdir = fileInfo.filePath();
		QString rasterbasename = fileInfo.completeBaseName();
		QgsRasterLayer* rlayer = new  QgsRasterLayer( rasterdir, rasterbasename );	
		if ( rlayer && rlayer->dataProvider() && rlayer->dataProvider()->name() == "gdal" )
		{
			QgsRasterCalculatorEntry entry;
			entry.raster = rlayer;
			entry.bandNumber = 1;
			entry.ref = rlayer->name();
			entries.push_back(entry);
			if ( firstLayer )
			{
				rect = rlayer->extent();
				cols = rlayer->width();
				rows = rlayer->height();
				formatStr.append("\"" + entry.ref + "\" * " + factorMap.value(factor));
				firstLayer = false;
			}
			else
			{
				formatStr.append("+ \"" + entry.ref + "\" * "+ factorMap.value(factor));
			}
		}
	}

	QgsRasterCalculator rc( formatStr, savePath,"GTiff", rect, cols, rows, entries);
	QProgressDialog p( tr( "Calculating..." ), tr( "Abort..." ), 0, 0 );
	p.setWindowModality( Qt::WindowModal );
	if ( rc.processCalculation( &p ) == 0 )
	{
		QgisApp::instance()->addRasterLayer(savePath,QFileInfo(savePath).baseName());
	}

	QDialog::accept();
}