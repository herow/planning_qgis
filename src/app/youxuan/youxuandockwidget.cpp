#include "youxuandockwidget.h"
#include "ui_youxuandockwidget.h"
#include "kongxinstatus.h"
#include "diaochaform.h"
#include "imagecollection.h"
#include "fangtang.h"
#include "teshustatusform.h"
#include "wenti_celueform.h"
#include "chubufanganform.h"
#include "cunminyijianform.h"
#include "zhengfuyaoqiuform.h"
#include "finalfanganform.h"
YouXuanDockWidget::YouXuanDockWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::YouXuanDockWidget)
{
    ui->setupUi(this);
    connect( ui->btnKongxinStatus, SIGNAL(clicked()), this, SLOT( show_kongxin_status() ) );

    connect( ui->btnSurveyForm, SIGNAL(clicked()), this, SLOT( show_surveyForm() ) );
    connect( ui->btnPictureCollet, SIGNAL(clicked()), this, SLOT( show_picturecollect() ) );
    connect( ui->btnSemiStructSurvey, SIGNAL(clicked()), this, SLOT( show_semisurvey() ) );

    connect( ui->btnSpecStatus, SIGNAL(clicked()), this, SLOT( show_specstatus() ) );

    connect( ui->btnProblemStrategy, SIGNAL(clicked()), this, SLOT( show_ProblemStrategy() ) );

    connect( ui->btnInitStrategy, SIGNAL(clicked()), this, SLOT( show_InitStrategy() ) );
    connect( ui->btnPublicOpinion, SIGNAL(clicked()), this, SLOT( show_PublicOpinion() ) );
    connect( ui->btnGovOpinion, SIGNAL(clicked()), this, SLOT( show_GovOpinion() ) );
    connect( ui->btnFinalSolution, SIGNAL(clicked()), this, SLOT( show_FinalSolution() ) );

}

YouXuanDockWidget::~YouXuanDockWidget()
{
    delete ui;
}

void YouXuanDockWidget::show_kongxin_status()
{
     KongXinStatus * wid = new KongXinStatus();
     wid->show();
}
void YouXuanDockWidget::show_surveyForm()
{
     DiaoChaForm * wid = new DiaoChaForm();
     wid->show();
}
void YouXuanDockWidget::show_picturecollect()
{
     ImageCollection * wid = new ImageCollection();
     wid->show();
}
void YouXuanDockWidget::show_semisurvey()
{
     fangtang * wid = new fangtang();
     wid->show();
}
void YouXuanDockWidget::show_specstatus()
{
     TeShuStatusForm * wid = new TeShuStatusForm();
     wid->show();
}
void YouXuanDockWidget::show_ProblemStrategy()
{
    WenTi_CeLueForm * wid = new WenTi_CeLueForm();
    wid->show();
}
void YouXuanDockWidget::show_InitStrategy()
{
    ChuBuFangAnForm * wid = new ChuBuFangAnForm();
    wid->show();
}
void YouXuanDockWidget::show_PublicOpinion()
{
    CunMinYIjianForm * wid = new CunMinYIjianForm();
    wid->show();
}
void YouXuanDockWidget::show_GovOpinion()
{
    ZhengFuYaoqiuForm * wid = new ZhengFuYaoqiuForm();
    wid->show();
}
void YouXuanDockWidget::show_FinalSolution()
{
    FinalFanganForm * wid = new FinalFanganForm();
    wid->show();
}
