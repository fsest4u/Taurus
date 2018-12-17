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
	, m_StartRow(0)
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

	ui->dataFilepath->setText(m_CSVFileName);

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
}


void MainWindow::ConnectSignalsToSlots()
{

	connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(Analyze()));

}

void MainWindow::Analyze()
{
	qDebug() << "Analyze()";

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
	m_SrcData = m_CSV->GetData();
	m_StartRow = m_CSV->GetStartRow();


	if (!m_Lotto) {
		m_Lotto = new MgrLotto();
	}

	m_Lotto->SetBonus(ui->rbBonusOn->isChecked());
	m_Lotto->SetStartRow(m_StartRow);
	m_Lotto->SetSourceData(m_SrcData);

	m_Lotto->SetStatNumber(ui->cbNumber->isChecked());
	m_Lotto->SetStatColor(ui->cbColor->isChecked());
	m_Lotto->SetStatSection(ui->cbSection->isChecked());
	m_Lotto->SetStatPeriod(ui->cbPeriod->isChecked());
	m_Lotto->SetStatSniffling(ui->cbSniffling->isChecked());
	m_Lotto->SetStatContinue(ui->cbContinue->isChecked());

	//m_Lotto->ExportData();

}