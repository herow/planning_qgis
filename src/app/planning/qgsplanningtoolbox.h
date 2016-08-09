#ifndef QGSPLANNINGTOOLBOX_H
#define QGSPLANNINGTOOLBOX_H

#include <QDockWidget>
#include "ui_planningtoolbox.h"

class QgsPlanningToolBox : public QDockWidget,private Ui::QgsPlanningDockWindow
{
    Q_OBJECT
public:
    explicit QgsPlanningToolBox();

signals:

public slots:
	void planningWizard();
	void ecologyWizard();
	void direction();
	void pattern();
	void score();
};

#endif // QGSPLANNINGTOOLBOX_H