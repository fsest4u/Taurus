/************************************************************************
**
**  Copyright (C) 2018  Daniel Lee <fsest4u@gmail.com>
**
**  This file is part of Taurus.
**
**  Taurus is analysis tool for lotto.
**
*************************************************************************/

#include <QtDebug>
#include <QtCore/QStandardPaths>
#include <QtCore/QDate>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>

#include "MgrCSV.h"
#include "MgrLotto.h"
#include "misc/SettingData.h"
#include "Misc/LimitDate.h"

#include "mainwindow.h"
#include "ui_MainWindow.h"

static const QString SETTINGS_GROUP = "mainWindow";

const int REMAIN_COUNT = 100;

const int TURN_COUNT = 15;

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
	, m_LastFolderOpen("")
	, m_CSVFileName("")
	, m_CSV(NULL)
	, m_Lotto(NULL)
	, m_WeekNumber(0)
	, m_RemainCount(REMAIN_COUNT)
{
    ui->setupUi(this);

   	ReadSettings();
	InitUI();
}

MainWindow::~MainWindow()
{
	WriteSettings();
	delete ui;

	if (m_CSV) {
		delete m_CSV;
		m_CSV = 0;
	}

	if (m_Lotto) {
		delete m_Lotto;
		m_Lotto = 0;
	}
}

void MainWindow::ReadSettings()
{
	SettingData settings;
	settings.beginGroup(SETTINGS_GROUP);
	// The size of the window and it's full screen status
	QByteArray geometry = settings.value("geometry").toByteArray();

	if (!geometry.isNull()) {
		restoreGeometry(geometry);
	}

	// The last folder used for saving and opening files
	m_LastFolderOpen = settings.value("lastfolderopen", QDir::homePath()).toString();
	m_CSVFileName = settings.value("lastcsvfile", QDir::homePath()).toString();
	m_WeekNumber = settings.value("weeknumber", QDate::currentDate().weekNumber()).toByteArray().toInt();
	m_RemainCount = settings.value("count", REMAIN_COUNT).toByteArray().toInt();

	ui->rbBonusOn->setChecked(settings.value("bbonus", false).toBool());
	ui->rbBonusOff->setChecked(!settings.value("bbonus", false).toBool());
	ui->cbNumber->setChecked(settings.value("bnumber", false).toBool());
	ui->cbColor->setChecked(settings.value("bcolor", false).toBool());
	ui->cbSection->setChecked(settings.value("bsection", false).toBool());
	ui->cbPeriod->setChecked(settings.value("bperiod", false).toBool());
	ui->cbSniffling->setChecked(settings.value("bsniffling", false).toBool());
	ui->cbContinue->setChecked(settings.value("bcontinue", false).toBool());

	settings.endGroup();

}

void MainWindow::WriteSettings()
{
	SettingData settings;
	settings.beginGroup(SETTINGS_GROUP);
	// The size of the window and it's full screen status
	settings.setValue("geometry", saveGeometry());

	QByteArray temp;
	// The last folders used for saving and opening files
	settings.setValue("lastfolderopen", m_LastFolderOpen);
	settings.setValue("lastcsvfile", m_CSVFileName);
	settings.setValue("weeknumber", temp.setNum(m_WeekNumber));
	settings.setValue("count", temp.setNum(m_RemainCount));

	settings.setValue("bbonus", ui->rbBonusOn->isChecked());
	settings.setValue("bnumber", ui->cbNumber->isChecked());
	settings.setValue("bcolor", ui->cbColor->isChecked());
	settings.setValue("bsection", ui->cbSection->isChecked());
	settings.setValue("bperiod", ui->cbPeriod->isChecked());
	settings.setValue("bsniffling", ui->cbSniffling->isChecked());
	settings.setValue("bcontinue", ui->cbContinue->isChecked());

	settings.endGroup();
}

void MainWindow::InitUI()
{
	ui->toolBar->setVisible(false);
	ui->statusBar->setVisible(false);

	ui->actionNew->setVisible(false);
	ui->actionOpen->setVisible(false);
	ui->actionSave->setVisible(false);

	ui->buttonBox->button(QDialogButtonBox::Ok)->setText(tr("Analyze"));

	ConnectSignalsToSlots();

	ui->dataFilepath->setText("");

	ui->cbNumber->setChecked(true);

	ui->cbLastWeek->addItem(tr("5 Week"), MgrLotto::TURN_WEEK_5);
	ui->cbLastWeek->addItem(tr("10 Week"), MgrLotto::TURN_WEEK_10);
	ui->cbLastWeek->addItem(tr("15 Week"), MgrLotto::TURN_WEEK_15);
	ui->cbLastWeek->setCurrentIndex(ui->cbLastWeek->count() - 1);

	//m_WeekNumber -= 1;// temp code
	if (m_WeekNumber < QDate::currentDate().weekNumber()
		|| m_RemainCount > REMAIN_COUNT) {
		m_WeekNumber = QDate::currentDate().weekNumber();
		m_RemainCount = REMAIN_COUNT;	// reset remain count
	}
	ui->remainCount->setText(QString::number(m_RemainCount));

	m_SrcData.clear();
}

void MainWindow::on_actionNew_triggered()
{
	qDebug() << "on_actionNew_triggered()";
}

void MainWindow::on_actionOpen_triggered()
{
	qDebug() << "on_actionOpen_triggered()";
}

void MainWindow::on_actionSave_triggered()
{
	qDebug() << "on_actionSave_triggered()";
}

void MainWindow::on_actionExit_triggered()
{
	qDebug() << "on_actionExit_triggered()";
	QMessageBox::StandardButton btn;
	btn = QMessageBox::question(this, tr(QCoreApplication::applicationName().toStdString().c_str()), tr("Are you sure you want to exit the application?"), QMessageBox::Ok | QMessageBox::Cancel);

	if (btn == QMessageBox::Ok) {
		this->close();
		return;
	}
}

void MainWindow::on_actionAbout_triggered()
{
	qDebug() << "on_actionAbout_triggered()";
	QMessageBox::information(this
		, tr(QCoreApplication::applicationName().toStdString().c_str())
		, tr("%1 %2").arg(QCoreApplication::applicationName())
					.arg(QCoreApplication::applicationVersion()));

}

void MainWindow::on_dataButton_clicked()
{
	QString filepath;
	filepath = m_CSVFileName;

	// Get the filename to use
	QString default_filter = "*";
	QString basename = QFileInfo(ui->dataFilepath->text()).baseName();
	QString filename = QFileDialog::getOpenFileName(this,
													tr("Open CSV File"),
													m_LastFolderOpen + "/" + basename,
													tr("CSV Files (*.csv)"),
													&default_filter);

	m_CSVFileName = filename;
	ui->dataFilepath->setText(filename);

	if (!filename.isEmpty()) {
		m_LastFolderOpen = QFileInfo(filename).absolutePath();
	}
	else {
		QMessageBox::warning(this
			, tr(QCoreApplication::applicationName().toStdString().c_str())
			, tr("Please, Select a data file."));

	}

	if (!m_CSV) {
		m_CSV = new MgrCSV();
	}

	bool ret = m_CSV->ReadFile(m_CSVFileName);
	if (!ret) {
		QMessageBox::warning(this
			, tr(QCoreApplication::applicationName().toStdString().c_str())
			, tr("File isn't exist. Check a file."));
		return;
	}
	m_SrcData = m_CSV->GetSrcData();

	// 충분한 데이타를 입력받기 위해서 최소 5회차의 입력값을 설정
	for (int i = m_CSV->GetSrcData().firstKey(); i <= m_CSV->GetSrcData().lastKey() - TURN_COUNT; i++) {
		ui->cbStart->addItem(QString("%1").arg(i), i);
	}
	for (int i = m_CSV->GetSrcData().firstKey() + TURN_COUNT; i <= m_CSV->GetSrcData().lastKey(); i++) {
		ui->cbEnd->addItem(QString("%1").arg(i), i);
	}
	ui->cbStart->setCurrentIndex(0);
	ui->cbEnd->setCurrentIndex(ui->cbEnd->count() - 1);
}


void MainWindow::ConnectSignalsToSlots()
{
	connect(ui->cbStart, SIGNAL(currentIndexChanged(int)), this, SLOT(SetStartTurn(int)));
	connect(ui->cbEnd, SIGNAL(currentIndexChanged(int)), this, SLOT(SetEndTurn(int)));

	connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(Analyze()));

}

void MainWindow::SetStartTurn(int index)
{
	qDebug() << "SetStartTurn() end current " << ui->cbEnd->currentIndex() << ", start index " << index;
	if (ui->cbEnd->currentIndex() < index) {
		ui->cbEnd->setCurrentIndex(index);
	}
}

void MainWindow::SetEndTurn(int index)
{
	qDebug() << "SetEndTurn() start current " << ui->cbStart->currentIndex() << ", end index " << index;
	if (ui->cbStart->currentIndex() > index) {
		ui->cbStart->setCurrentIndex(index);
	}
}


void MainWindow::Analyze()
{
	qDebug() << "Analyze()";
	if (ui->dataFilepath->text().isEmpty()) {
		QMessageBox::warning(this
			, tr(QCoreApplication::applicationName().toStdString().c_str())
			, tr("Please, Select a data file."));
		return;
	}
	if (m_RemainCount <= 0) {
		QMessageBox::warning(this
			, tr(QCoreApplication::applicationName().toStdString().c_str())
			, tr("You have exceeded the number available."));
		return;
	}

	if (!OnCheckLimited()) { return; }

	WriteSettings();
	m_RemainCount--;
	ui->remainCount->setText(QString::number(m_RemainCount));

	if (!m_Lotto) {
		m_Lotto = new MgrLotto();
	}

	m_Lotto->SetPreference(ui->rbBonusOn->isChecked()
						, ui->cbStart->currentData().toInt()
						, ui->cbEnd->currentData().toInt()
						, ui->cbLastWeek->currentData().toInt());

	QList<bool> condition;
	condition.insert(0, ui->cbNumber->isChecked());
	condition.insert(1, ui->cbColor->isChecked());
	condition.insert(2, ui->cbSection->isChecked());
	condition.insert(3, ui->cbPeriod->isChecked());
	condition.insert(4, ui->cbSniffling->isChecked());
	condition.insert(5, ui->cbContinue->isChecked());
	bool ret1 = m_Lotto->GenerateInfo(condition, m_SrcData);
	if (!ret1) {
		QMessageBox::warning(this
			, tr(QCoreApplication::applicationName().toStdString().c_str())
			, tr("Please, Change to analysis conditions."));
		return;
	}

	QList<int> lotto = m_Lotto->ExportData();

	ui->lotto0->setText(QString::number(lotto.at(0)));
	ui->lotto1->setText(QString::number(lotto.at(1)));
	ui->lotto2->setText(QString::number(lotto.at(2)));
	ui->lotto3->setText(QString::number(lotto.at(3)));
	ui->lotto4->setText(QString::number(lotto.at(4)));
	ui->lotto5->setText(QString::number(lotto.at(5)));

	// 과거 당첨확인 조회 (보너스 번호 제외)
	//bool ret2 = m_CSV->ReadFile(m_CSVFileName, false);
	//if (!ret2) {
	//	QMessageBox::warning(this
	//		, tr(QCoreApplication::applicationName().toStdString().c_str())
	//		, tr("File isn't exist. Check a file."));
	//	return;
	//}
	//m_SrcData = m_CSV->GetSrcData();

	//QList<int> keys = m_SrcData.keys(lotto);
	//if (!keys.isEmpty()) {
	//	QMessageBox::warning(this
	//		, tr(QCoreApplication::applicationName().toStdString().c_str())
	//		, tr("Congratulations. The %1 th").arg(keys.at(0)));
	//}

}

bool MainWindow::OnCheckLimited()
{
	bool ret = false;

	LimitDate* limitDate = new LimitDate();
	if (limitDate->CheckExpiredDate()) {
		QDate date = limitDate->GetExpiredDate();
		QMessageBox::critical(this
			, tr(QCoreApplication::applicationName().toStdString().c_str())
			, tr("The function has expired. %1.%2.%3").arg(date.year()).arg(date.month()).arg(date.day()));

		ret = false;
	}
	else {
		ret = true;
	}

	if (limitDate) {
		delete limitDate;
		limitDate = 0;
	}

	return ret;
}
