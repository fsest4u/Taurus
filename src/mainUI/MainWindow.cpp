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

#include "misc/SettingData.h"

#include "mainwindow.h"
#include "ui_MainWindow.h"

static const QString SETTINGS_GROUP = "mainWindow";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
	, m_LastFolderOpen("")
	, m_CSVFileName("")
{
    ui->setupUi(this);

   	ReadSettings();
	InitUI();
}

MainWindow::~MainWindow()
{
	WriteSettings();
	delete ui;
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

	ui->ResultFilepath->setText(m_CSVFileName);
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

void MainWindow::on_ResultFileButton_clicked()
{
	QString filepath;
	filepath = m_CSVFileName;

	// Get the filename to use
	QString default_filter = "*";
	QString basename = QFileInfo(ui->ResultFilepath->text()).baseName();
	QString filename = QFileDialog::getOpenFileName(this,
													tr("Open CSV File"),
													m_LastFolderOpen + "/" + basename,
													tr("CSV Files (*.csv)"),
													&default_filter);

	m_CSVFileName = filename;
	ui->ResultFilepath->setText(filename);

	if (!filename.isEmpty())
		m_LastFolderOpen = QFileInfo(filename).absolutePath();
}


void MainWindow::ConnectSignalsToSlots()
{

	connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(AnalyzeData()));

}

void MainWindow::AnalyzeData()
{
	qDebug() << "AnalyzeData()";

}