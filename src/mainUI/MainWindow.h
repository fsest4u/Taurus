/************************************************************************
**
**  Copyright (C) 2018  Daniel Lee <fsest4u@gmail.com>
**
**  This file is part of Taurus.
**
**  Taurus is analysis tool for lotto.
**
*************************************************************************/

#pragma once
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore/QMap>
#include <QtCore/QList>

namespace Ui {
	class MainWindow;
}

class MgrCSV;
class MgrLotto;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

	void on_actionNew_triggered();
	void on_actionOpen_triggered();
	void on_actionSave_triggered();
	void on_actionExit_triggered();
	void on_actionAbout_triggered();

	void on_dataButton_clicked();

	void SetStartTurn(int index);
	void SetEndTurn(int index);
	void Analyze();

	void ExportGame1();
	void ExportGame2();
	void ExportGame3();
	void ExportGame4();
	void ExportGame5();

private:
	/**
	* Reads all the stored application settings like
	* window position, geometry etc.
	*/
	void ReadSettings();

	/**
	* Writes all the stored application settings like
	* window position, geometry etc.
	*/
	void WriteSettings();

	void InitUI();

	void ConnectSignalsToSlots();

	bool OnCheckLimited();


	QString						m_LastFolderOpen;
	QString						m_CSVFileName;

	int							m_RemainCount;
	int							m_WeekNumber;

	MgrCSV						*m_CSV;
	MgrLotto					*m_Lotto;

	QMap<int, QList<int>>		m_SrcData;

    Ui::MainWindow *ui; 
};

#endif // MAINWINDOW_H
