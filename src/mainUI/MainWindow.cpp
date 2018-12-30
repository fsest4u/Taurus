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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>

#include "MgrCSV.h"
#include "MgrLotto.h"
#include "misc/SettingData.h"

#include "mainwindow.h"
#include "ui_MainWindow.h"

static const QString SETTINGS_GROUP = "mainWindow";

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
	, m_LastFolderOpen("")
	, m_CSVFileName("")
	, m_CSV(NULL)
	, m_Lotto(NULL)
	, m_RemainCount(5)
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

	ui->rbBonusOn->setChecked(settings.value("bbonus", false).toBool());
	ui->rbBonusOff->setChecked(!settings.value("bbonus", false).toBool());
	ui->cbNumber->setChecked(settings.value("bnumber", false).toBool());
	ui->cbColor->setChecked(settings.value("bcolor", false).toBool());
	ui->cbSection->setChecked(settings.value("bsection", false).toBool());
	ui->cbPeriod->setChecked(settings.value("bperiod", false).toBool());
	ui->cbSniffling->setChecked(settings.value("bsniffling", false).toBool());
	ui->cbContinue->setChecked(settings.value("bcontinue", false).toBool());

	//m_RemainCount = settings.value("count", 5).toInt();

	settings.endGroup();

}

void MainWindow::WriteSettings()
{
	SettingData settings;
	settings.beginGroup(SETTINGS_GROUP);
	// The size of the window and it's full screen status
	settings.setValue("geometry", saveGeometry());

	// The last folders used for saving and opening files
	settings.setValue("lastfolderopen", m_LastFolderOpen);
	settings.setValue("lastcsvfile", m_CSVFileName);

	settings.setValue("bbonus", ui->rbBonusOn->isChecked());
	settings.setValue("bnumber", ui->cbNumber->isChecked());
	settings.setValue("bcolor", ui->cbColor->isChecked());
	settings.setValue("bsection", ui->cbSection->isChecked());
	settings.setValue("bperiod", ui->cbPeriod->isChecked());
	settings.setValue("bsniffling", ui->cbSniffling->isChecked());
	settings.setValue("bcontinue", ui->cbContinue->isChecked());

	//settings.setValue("count", m_RemainCount);

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

	ui->remainCount->setText(QString::number(m_RemainCount));

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

	for (int i = m_CSV->GetSrcData().firstKey(); i <= m_CSV->GetSrcData().lastKey(); i++) {
		ui->cbStart->addItem(QString("%1").arg(i), i);
		ui->cbEnd->addItem(QString("%1").arg(i), i);
	}
	ui->cbStart->setCurrentIndex(ui->cbStart->count() - 1);
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
	if (ui->cbEnd->currentIndex() < index) {
		ui->cbEnd->setCurrentIndex(index);
	}
}

void MainWindow::SetEndTurn(int index)
{
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
	m_Lotto->GenerateInfo(condition, m_CSV->GetSrcData());

	QList<int> lotto = m_Lotto->ExportData();
	ui->lotto0->setText(QString::number(lotto.at(0)));
	ui->lotto1->setText(QString::number(lotto.at(1)));
	ui->lotto2->setText(QString::number(lotto.at(2)));
	ui->lotto3->setText(QString::number(lotto.at(3)));
	ui->lotto4->setText(QString::number(lotto.at(4)));
	ui->lotto5->setText(QString::number(lotto.at(5)));

}