#ifndef YOUXUANDOCKWIDGET_H
#define YOUXUANDOCKWIDGET_H

#include <QDockWidget>

namespace Ui {
class YouXuanDockWidget;
}

class YouXuanDockWidget : public QDockWidget
{
    Q_OBJECT

public:
    explicit YouXuanDockWidget(QWidget *parent = 0);
    ~YouXuanDockWidget();

private:
    Ui::YouXuanDockWidget *ui;
private slots:
    void show_kongxin_status();
    void show_surveyForm();
    void show_picturecollect();
    void show_ProblemStrategy();
    void show_specstatus();
    void show_semisurvey();
    void show_InitStrategy();
    void show_PublicOpinion();
    void show_GovOpinion();
    void show_FinalSolution();

};

#endif // YOUXUANDOCKWIDGET_H
