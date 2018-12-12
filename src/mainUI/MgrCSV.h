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
#ifndef MGR_CSV_H
#define MGR_CSV_H

#include <QtCore/QObject>
#include <QAbstractItemModel>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QtWidgets/QVBoxLayout>
#include <QDateTime>
#include <QtWidgets/QTableView>

class ProgressWidget;

class MgrCSV : public QObject
{
	Q_OBJECT

public:

	enum COL_TYPE {
		COL_YEAR = 0,
		COL_TURN,
		COL_LOTTERY_DAY,
		COL_1ST_CNT,
		COL_1ST_AMT,
		COL_2ND_CNT,
		COL_2ND_AMT,
		COL_3RD_CNT,
		COL_3RD_AMT,
		COL_4TH_CNT,
		COL_4TH_AMT,
		COL_5TH_CNT,
		COL_5TH_AMT,
		COL_1ST_NUM,
		COL_2ND_NUM,
		COL_3RD_NUM,
		COL_4TH_NUM,
		COL_5TH_NUM,
		COL_6TH_NUM,
		COL_BONUS_NUM,
		COL_MAX
	};

	/**
	* Constructor.
	*/
	MgrCSV();
	~MgrCSV();

	bool ReadFile(QString filepath);
	void WriteFile(QString filepath);


private slots:


private:



	///////////////////////////////
	// PRIVATE MEMBER VARIABLES
	///////////////////////////////
	QList<QStringList> m_CSVData;

	QStringList		m_CSVHeader;

	ProgressWidget* m_ProgressWidget;

};

#endif // MGR_CSV_H
