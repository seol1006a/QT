/* Naitec Sample Source */
/* 2014.07.07           */

#ifndef QTMPLAYER_H
#define QTMPLAYER_H

#include <QWidget>
#include <QProcess>
#include <QFileDialog>
#include <QDebug>
#include "ui_QtMplayer.h"

class QtMplayer : public QWidget
{
	Q_OBJECT

public:
	QtMplayer(QWidget *parent = 0);
	~QtMplayer();

private:
	Ui::QtMplayerClass ui;
	QProcess* pProcMplayer;

	int vFrameX;
	int vFrameY;
	int vFrameWidth;
	int vFrameHeight;

protected slots:
	void procStdErr();
	void procStdOut();
	void on_pPbOpen_clicked();
	void on_pPbPause_clicked();
};

#endif // QTMPLAYER_H
