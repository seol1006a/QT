/* kccistc aiot Sample Source */

//sudo apt-get install mplayer
#include "QtMplayer.h"

QtMplayer::QtMplayer(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	pProcMplayer = new QProcess(this);
	connect(pProcMplayer, SIGNAL(readyReadStandardError()), this, SLOT(procStdErr()) );
	connect(pProcMplayer, SIGNAL(readyReadStandardOutput()),this, SLOT(procStdOut()) );
}

QtMplayer::~QtMplayer()
{
	pProcMplayer->close();
}

void QtMplayer::on_pPbOpen_clicked()
{
	QString filename = QFileDialog::getOpenFileName(this,	tr("Open Movie"), "", tr("Movie Files (*.*)"));
	if (filename.isEmpty()) return;
/*
	QPoint vFramePos;
	vFramePos = ui.pVideoFrame->pos();
	vFramePos = mapToGlobal(vFramePos);
	vFrameX = vFramePos.x();
	vFrameY = vFramePos.y();
	vFrameWidth = ui.pVideoFrame->width();
	vFrameHeight = ui.pVideoFrame->height();
*/
	QPoint vFramePos;
	vFramePos = ui.pVideoFrame->pos();
	vFramePos = mapToGlobal(vFramePos);
	vFrameX = vFramePos.x()+ui.verticalLayout->spacing() * 2 ;
	vFrameY = vFramePos.y()+ui.verticalLayout->spacing() * 2;
	vFrameWidth = ui.pVideoFrame->width();
	vFrameHeight = ui.pVideoFrame->height();

    QString program = "/usr/bin/mplayer";
	QStringList arguments;
	arguments << "-slave"<<"-identify"<<"-quiet";
	arguments << "-zoom"<<"-vm"<<"-x"<<tr("%1").arg(vFrameWidth)<<"-y"<<tr("%1").arg(vFrameHeight)<<"-vo"<<"fbdev2";
	arguments << "-geometry" <<tr("%1:%2").arg(vFrameX).arg(vFrameY);
	arguments << filename;

	pProcMplayer->start(program,arguments);
}
void QtMplayer::on_pPbPause_clicked()
{
	pProcMplayer->write("p\n");
}

void QtMplayer::procStdErr()
{
	QByteArray result = pProcMplayer->readAllStandardError();
	if (result.isEmpty()) return;

	QString text = result.data();
	qDebug() << "MainFrm::procStdErr " << text;
}

void QtMplayer::procStdOut()
{
	QByteArray result = pProcMplayer->readAllStandardOutput();
	if (result.isEmpty()) return;

	QString text = result.data();
	qDebug() << "MainFrm::procStdErr " << text;
}

