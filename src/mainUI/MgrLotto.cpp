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
#include "MgrLotto.h"
#include "StatColor.h"
#include "StatContinue.h"
#include "StatNumber.h"
#include "StatPeriod.h"
#include "StatSection.h"
#include "StatSniffling.h"
//#include "taurus_constants.h"


MgrLotto::MgrLotto() :
	 m_ProgressWidget(NULL)
{

	m_ProgressWidget = new ProgressWidget();
}

MgrLotto::~MgrLotto()
{

	if (m_ProgressWidget) {
		delete m_ProgressWidget;
		m_ProgressWidget = NULL;
	}
}

void MgrLotto::SetPreference(bool bBonus, int start, int end, int lastweek)
{
	qDebug() << "SetPreference() bonus : " << bBonus << 
		", start : " << start << 
		", end : " << end << 
		", lastweek : " << lastweek;
	m_bBonus = bBonus;
	m_StartTurn = start;
	m_EndTurn = end;
	m_LastWeek = lastweek;
}

void MgrLotto::GenerateInfo(QList<bool> condition, QMap<int, QList<int>> srcData)
{
	if (condition.at(CON_NUMBER)) {
		StatNumber number;
		number.Generate(srcData, m_bBonus, m_StartTurn, m_EndTurn);
	}
	if (condition.at(CON_COLOR)) {
		StatColor color;
		color.Generate(srcData, true, m_StartTurn, m_EndTurn);
	}
	if (condition.at(CON_SNIFFLING)) {
		StatSniffling sniffling;
		sniffling.Generate(srcData, false, m_StartTurn, m_EndTurn);
	}
	if (condition.at(CON_COUTINUE)) {
		StatContinue conti;
		conti.Generate(srcData, false, m_StartTurn, m_EndTurn);
	}
	if (condition.at(CON_SECTION)) {
		StatSection section;
		section.Generate(srcData, true, m_LastWeek);
	}
	if (condition.at(CON_PERIOD)) {
		StatPeriod period;
		period.Generate(srcData, true, m_LastWeek);
	}
}


void MgrLotto::ExportData()
{
	qDebug() << "ExportData()";

}


