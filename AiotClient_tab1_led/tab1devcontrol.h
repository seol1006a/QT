#ifndef TAB1DEVCONTROL_H
#define TAB1DEVCONTROL_H

#include <QWidget>
#include <QTimer>
#include "ledkeydev.h"

namespace Ui {
class Tab1DevControl;
}

class Tab1DevControl : public QWidget
{
    Q_OBJECT

public:
    explicit Tab1DevControl(QWidget *parent = nullptr);
    ~Tab1DevControl();

private slots:
    void updateProgressBarLedSlot(int);
    void on_pPBtimerStart_clicked(bool checked);
    void updateDialValueSlot();

    void on_pCBtimerValue_currentTextChanged(const QString &arg1);

private:
    Ui::Tab1DevControl *ui;
    LedKeyDev *pLedKeyDev;
    QTimer *pQTimer;
};

#endif // TAB1DEVCONTROL_H
