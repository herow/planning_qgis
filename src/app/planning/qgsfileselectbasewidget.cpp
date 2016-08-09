#include "qgsfileselectbasewidget.h"
#include <QFileDialog>
#include <QSettings>

QgsFileSelectBaseWidget::QgsFileSelectBaseWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setupUi(this);
	connect( mSelectBtn, SIGNAL(clicked()), this, SLOT(setInputFile()));
}

QgsFileSelectBaseWidget::~QgsFileSelectBaseWidget()
{

}
void QgsFileSelectBaseWidget::setInputFile()
{
	QSettings settings;
	QString lastUsedDir = settings.value( "/UI/lastProjectDir", "." ).toString();
	QString fullPath = QFileDialog::getOpenFileName( this,
		tr( "Choose a QGIS project file to open" ),
		lastUsedDir,
		tr( "All Files" ) + " (*.* *.*)" );
	if ( fullPath.isNull() )
	{
		return;
	}
	QFileInfo myFI( fullPath );
	QString myPath = myFI.path();
	settings.setValue( "/UI/lastProjectDir", myPath );
	mInputFileEdit->setText(fullPath);
}