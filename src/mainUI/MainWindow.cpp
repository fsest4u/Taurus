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
{
    ui->setupUi(this);

   	ReadSettings();

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

	settings.endGroup();
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
}
