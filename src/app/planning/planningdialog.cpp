#include <QMap>
#include <QSettings>
#include <QFileInfo>
#include <QFileDialog>
#include <QProgressDialog>

#include "qgsvectorlayer.h"
#include "qgsrasterlayer.h"
#include "qgszonalstatistics.h"
#include "qgsmaplayerregistry.h"
#include "qgsvectorfilewriter.h"
#include "qgsmessageviewer.h"
#include "qgsvectordataprovider.h"

#include "planningdialog.h"
#include "ui_planningdialog.h"

inline QString range(double x, double y) 
{
	return QString::number(x).append("-").append(QString::number(y));
}
PlanningDialog::PlanningDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlanningDialog)
{
    ui->setupUi(this);
	QMap<QString,QString> data;
	data.insert(range(0.77,2.86),QString::fromLocal8Bit("�������˿�������"));
	data.insert(range(2.86,3.48),QString::fromLocal8Bit("�����˿�������"));
	data.insert(range(3.48,4.19),QString::fromLocal8Bit("�������˿�������"));
	data.insert(range(4.19,5.68),QString::fromLocal8Bit("���˿�������"));
	QStringList heads;
	heads<<QString::fromLocal8Bit("�����ۺϵ÷�");
	heads<<QString::fromLocal8Bit("���۽��");
	mSettingWidget = new QgsSettingWidget(heads,data);
	mSettingWidget->layout()->setMargin(0);

	ui->horizontalLayout->addWidget(mSettingWidget);
	//ui->horizontalLayout->setMargin(0);

	ui->buttonBox->button(QDialogButtonBox::Ok)->setText(QString::fromLocal8Bit("ȷ��"));
	ui->buttonBox->button(QDialogButtonBox::Cancel)->setText(QString::fromLocal8Bit("ȡ��"));

	connect( ui->rasterOpenBtn, SIGNAL(clicked()), this, SLOT(openRaster()));
	connect( ui->vectorOpenBtn, SIGNAL(clicked()), this, SLOT(openVector()));
	connect( ui->vectorSaveBtn, SIGNAL(clicked()), this, SLOT(saveVector()));
	resize(450,450);

}

PlanningDialog::~PlanningDialog()
{
    delete ui;
}


void PlanningDialog::openRaster()
{
	QSettings settings;
	QString lastUsedDir = settings.value( "/UI/lastProjectDir", "." ).toString();
	QString fullPath = QFileDialog::getOpenFileName( this,
		QString::fromLocal8Bit("ѡ�������õ����������۵�ͼ"),
		lastUsedDir,
		tr( "GeoTiff" ) + " (*.tif)" );
	if ( fullPath.isNull() )
	{
		return ;
	}
	QFileInfo myFI( fullPath );
	QString myPath = myFI.path();
	settings.setValue( "/UI/lastProjectDir", myPath );
	ui->rasterFileEdit->setText(fullPath);
}
void PlanningDialog::openVector()
{
	QSettings settings;
	QString lastUsedDir = settings.value( "/UI/lastProjectDir", "." ).toString();
	QString fullPath = QFileDialog::getOpenFileName( this,
		QString::fromLocal8Bit("ѡ����������"),
		lastUsedDir,
		tr( "shapefile" ) + " (*.shp)" );
	if ( fullPath.isNull() )
	{
		return ;
	}
	QFileInfo myFI( fullPath );
	QString myPath = myFI.path();
	settings.setValue( "/UI/lastProjectDir", myPath );
	ui->vectorFileEdit->setText(fullPath);
}
void PlanningDialog::saveVector()
{
	QSettings settings;
	QString lastUsedDir = settings.value( "/UI/lastProjectDir", "." ).toString();
	QString fullPath = QFileDialog::getSaveFileName( this,
		QString::fromLocal8Bit("����"),
		lastUsedDir,
		tr( "shapefile" ) + " (*.shp)" );
	if ( fullPath.isNull() )
	{
		return ;
	}
	QFileInfo myFI( fullPath );
	QString myPath = myFI.path();
	settings.setValue( "/UI/lastProjectDir", myPath );
	ui->vectorSaveEdit->setText(fullPath);
}

void PlanningDialog::eval(QgsVectorLayer* vl)
{
	QgsVectorDataProvider* dp = vl->dataProvider();
	QString evalName("eval" );
	int n = 0;
	const QgsFields& providerFields = dp->fields();
	bool found = false;
	for ( int idx = 0; idx < providerFields.count(); ++idx )
	{
		
		if (providerFields[idx].name().contains(evalName))
		{
			QgsDebugMsg(providerFields[idx].name());
			n++;
		}
	}
	if (n)
	{
		evalName.append("_").append(QString::number(n+1));
	}
	QgsDebugMsg(evalName);
	QgsField evalField( evalName, QVariant::String, QString("varchar"),20 );
	QList<QgsField> newFieldList;
	newFieldList.push_back(evalField);
	dp->addAttributes( newFieldList );
	
	int evalIndex = 0;
	for ( int i = 0; i < providerFields.count(); ++i )
	{
		if ( QString::compare( providerFields[i].name(), evalName, Qt::CaseInsensitive ) == 0 )	
		{
			evalIndex=i;
			break;
		}
	}

	int meanIndex = 0;
	QStringList meanName;
	for ( int i = 0; i < providerFields.count(); ++i )
	{
		if ( providerFields[i].name().contains("mean"))
		{
			meanIndex=i;
			meanName<<providerFields[i].name();
			break;
		}
	}

    QgsFeatureRequest request;
    request.setSubsetOfAttributes(meanName,providerFields);
    QgsFeatureIterator fi = dp->getFeatures( request );
    QgsFeature f;
     
    int featureCounter = 0;
    while ( fi.nextFeature( f ) )
    {

		QgsGeometry* featureGeometry = f.geometry();
		if ( !featureGeometry )
		{
		  ++featureCounter;
		  continue;
		}
		double score = f.attribute(meanIndex).toDouble();
		QgsChangedAttributesMap changeMap;
		QgsAttributeMap changeAttributeMap;
		changeAttributeMap.insert( evalIndex, QVariant::fromValue(eval(score)));
		changeMap.insert( f.id(), changeAttributeMap );
		dp->changeAttributeValues( changeMap );

		++featureCounter;
	}
	vl->updateFields();
	
}

QString PlanningDialog::eval(double score){
	QMap<QString,QString> evalData = mSettingWidget->getData();
	QMap<QString,QString>::Iterator it = evalData.begin();
	for (;it!=evalData.end();it++)
	{
		const QString key = it.key();
		QStringList range = key.split('-');
		if (range[0].toDouble() < score && score < range[1].toDouble())
		{
			return it.value();
		}
	}
	return QString();
}

void PlanningDialog::accept()
{
	QApplication::setOverrideCursor( Qt::WaitCursor );
	QString rasterName = ui->rasterFileEdit->text();
	QString vectorName = ui->vectorFileEdit->text();

	QFileInfo vectorInfo(vectorName);
	QgsVectorLayer *vl = new QgsVectorLayer(vectorName, QFileInfo(vectorName).completeBaseName(), "ogr");
	if ( vl == NULL)
	{
		return;
	}
	if ( !vl->isValid() )
	{
		delete vl;
		return ;
	}
	QgsVectorFileWriter::WriterError error;
	QString errorMessage;
	QString newFilename;
	QString enc = vl->dataProvider()->encoding();
	error = QgsVectorFileWriter::writeAsVectorFormat(vl,ui->vectorSaveEdit->text(),enc,&(vl->crs()),
		QString("ESRI Shapefile"),false,&errorMessage,QStringList(),
		QStringList(),false,&(QFileInfo(ui->vectorSaveEdit->text()).completeBaseName()),QgsVectorFileWriter::NoSymbology,1.0,NULL);
	if ( error != QgsVectorFileWriter::NoError )
	{ 
		QgsMessageViewer *m = new QgsMessageViewer( 0 );
		m->setWindowTitle( tr( "Save error" ) );
		m->setMessageAsPlainText( tr( "Export to vector file failed.\nError: %1" ).arg( errorMessage ) );
		m->exec();
	}
	vl = new QgsVectorLayer(ui->vectorSaveEdit->text(), QFileInfo(ui->vectorSaveEdit->text()).completeBaseName(), "ogr");
	if ( vl == NULL)
	{
		return;
	}
	if ( !vl->isValid() )
	{
		delete vl;
		return ;
	}

	QgsZonalStatistics zs( vl, rasterName, "", 1 ); 
	QProgressDialog p( tr( "Calculating zonal statistics..." ), tr( "Abort..." ), 0, 0 );
	p.setWindowModality( Qt::WindowModal );
	zs.calculateStatistics( &p );

	eval(vl);

	QgsMapLayerRegistry::instance()->addMapLayer(vl, true); 
	QApplication::restoreOverrideCursor();
	QDialog::accept();
}