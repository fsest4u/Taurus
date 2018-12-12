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

#include "misc/ProgressWidget.h"
#include "MgrCSV.h"
#include "MgrLotto.h"
//#include "taurus_constants.h"


MgrLotto::MgrLotto() :
	 m_ProgressWidget(NULL)
{
	m_LottoData.clear();

	m_ProgressWidget = new ProgressWidget();
}

MgrLotto::~MgrLotto()
{

	if (m_ProgressWidget) {
		delete m_ProgressWidget;
		m_ProgressWidget = NULL;
	}
}

void MgrLotto::SetData(int start, QList<QStringList> data)
{
	m_StratRow = start;
	m_LottoData = data;
};


void MgrLotto::ExportData()
{
	qDebug() << "ExportData()";
	for (int i = m_StratRow; i < m_LottoData.size(); i++) {
		qDebug() << "[" << m_LottoData.at(i).value(MgrCSV::COL_TURN) << "] "
			<< m_LottoData.at(i).value(MgrCSV::COL_1ST_NUM) << ", "
			<< m_LottoData.at(i).value(MgrCSV::COL_2ND_NUM) << ", "
			<< m_LottoData.at(i).value(MgrCSV::COL_3RD_NUM) << ", "
			<< m_LottoData.at(i).value(MgrCSV::COL_4TH_NUM) << ", "
			<< m_LottoData.at(i).value(MgrCSV::COL_5TH_NUM) << ", "
			<< m_LottoData.at(i).value(MgrCSV::COL_6TH_NUM) << ", "
			<< m_LottoData.at(i).value(MgrCSV::COL_BONUS_NUM) << ".! ";
	}

}


