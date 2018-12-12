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
	m_CSVData.clear();
	m_CSVHeader << "";

	m_ProgressWidget = new ProgressWidget();
}

MgrCSV::~MgrCSV()
{

	if (m_ProgressWidget) {
		delete m_ProgressWidget;
		m_ProgressWidget = NULL;
	}
}

bool MgrCSV::ReadFile(QString filepath)
{
	qDebug() << "[ReadFile]-----------------------------";
	m_CSVData = QtCSV::Reader::readToList(filepath);
	qDebug() << "[ReadFile]-----------------------------" << m_CSVData.at(CSV_START_ROW).size();
	if (m_CSVData.at(CSV_START_ROW).size() == COL_MAX) {

		for (int i = CSV_START_ROW; i < m_CSVData.size(); i++) {
			//for (int j = 0; j < m_CSVData.at(i).size(); j++) {
			//	qDebug() << "[" << i << ", " << j << "]" << m_CSVData.at(i).value(j);
			//}
			qDebug() << "[" << m_CSVData.at(i).value(COL_TURN) <<"] "
				<< m_CSVData.at(i).value(COL_1ST_NUM) << ", "
				<< m_CSVData.at(i).value(COL_2ND_NUM) << ", "
				<< m_CSVData.at(i).value(COL_3RD_NUM) << ", "
				<< m_CSVData.at(i).value(COL_4TH_NUM) << ", "
				<< m_CSVData.at(i).value(COL_5TH_NUM) << ", "
				<< m_CSVData.at(i).value(COL_6TH_NUM) << ", "
				<< m_CSVData.at(i).value(COL_BONUS_NUM) << ".! ";
		}
		return true;
	}

	return false;
}

void MgrCSV::WriteFile(QString filepath)
{
	qDebug() << "[WriteFile]-----------------------------";

}

