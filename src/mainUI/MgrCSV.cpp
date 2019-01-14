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
#include <QtCore/QCoreApplication>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QMessageBox>

#include "qtcsv/reader.h"
#include "qtcsv/writer.h"
#include "qtcsv/stringdata.h"

#include "misc/ProgressWidget.h"
#include "MgrCSV.h"
//#include "taurus_constants.h"

const int CSV_START_ROW = 3;

MgrCSV::MgrCSV() :
	 m_ProgressWidget(NULL)
{
	m_ProgressWidget = new ProgressWidget();
}

MgrCSV::~MgrCSV()
{

	if (m_ProgressWidget) {
		delete m_ProgressWidget;
		m_ProgressWidget = NULL;
	}
}

bool MgrCSV::ReadFile(QString filepath, bool bBonus)
{
	if (!QFileInfo(filepath).exists()) {
		return false;
	}
	QList<QStringList> readData = QtCSV::Reader::readToList(filepath);
	if (readData.at(CSV_START_ROW).size() == COL_MAX) {

		m_SrcData.clear();
		QList<int> numData;

		for (int i = CSV_START_ROW; i < readData.size(); i++) {
			numData.clear();
			numData.insert(0, readData.at(i).value(MgrCSV::COL_1ST_NUM).toInt());
			numData.insert(1, readData.at(i).value(MgrCSV::COL_2ND_NUM).toInt());
			numData.insert(2, readData.at(i).value(MgrCSV::COL_3RD_NUM).toInt());
			numData.insert(3, readData.at(i).value(MgrCSV::COL_4TH_NUM).toInt());
			numData.insert(4, readData.at(i).value(MgrCSV::COL_5TH_NUM).toInt());
			numData.insert(5, readData.at(i).value(MgrCSV::COL_6TH_NUM).toInt());
			if (bBonus)
				numData.insert(6, readData.at(i).value(MgrCSV::COL_BONUS_NUM).toInt());

			m_SrcData.insert(readData.at(i).value(MgrCSV::COL_TURN).toInt(), numData);
		}

		return true;
	}

	return false;
}

void MgrCSV::WriteFile(QString filepath)
{
	//qDebug() << "[WriteFile]-----------------------------";

}
