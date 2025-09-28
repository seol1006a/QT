#include "tab1devcontrol.h"
#include "ui_tab1devcontrol.h"

Tab1DevControl::Tab1DevControl(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Tab1DevControl)
{
    ui->setupUi(this);
    pLedKeyDev = new LedKeyDev(this);
    pQTimer = new QTimer(this);
    connect(pQTimer,SIGNAL(timeout()), this, SLOT(updateDialValueSlot()));
    connect(ui->pDialLed, SIGNAL(valueChanged(int)), pLedKeyDev, SLOT(writeLedDataSlot(int)));
//    connect(ui->pDialLed, SIGNAL(valueChanged(int)), ui->pProgressBarLed,SLOT(setValue(int)));
    connect(ui->pDialLed, SIGNAL(valueChanged(int)), this,SLOT(updateProgressBarLedSlot(int)));
    connect(ui->pPBquit, SIGNAL(clicked()), qApp, SLOT(quit()));
}

void Tab1DevControl::updateProgressBarLedSlot(int value)
{
    ui->pProgressBarLed->setValue(value);
}
Tab1DevControl::~Tab1DevControl()
{
    delete ui;
}

void Tab1DevControl::on_pPBtimerStart_clicked(bool checked)
{
    if(checked)
    {
        QString strValue = ui->pCBtimerValue->currentText();
        pQTimer->start(strValue.toInt());
        ui->pPBtimerStart->setText("TimerStop");
    }
    else
    {
        pQTimer->stop();
        ui->pPBtimerStart->setText("TimerStart");
    }
}

void Tab1DevControl::updateDialValueSlot()
{
    int dialValue = ui->pDialLed->value();
    dialValue++;
    if(dialValue > ui->pDialLed->maximum())
        dialValue = 0;
    ui->pDialLed->setValue(dialValue);
}


void Tab1DevControl::on_pCBtimerValue_currentTextChanged(const QString &arg1)
{
    if(pQTimer->isActive())
    {
        pQTimer->stop();
        pQTimer->start(arg1.toInt());
    }
}

