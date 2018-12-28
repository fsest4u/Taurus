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
#include <QtCore/QTime>
#include <QtCore/QtGlobal>

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
		m_BaseList = number.GetList();
		// for debug
		for (QList<int>::const_iterator iter = m_BaseList.cbegin(); iter != m_BaseList.constEnd(); ++iter) {
			qDebug() << "=== CON_NUMBER " << *iter;
		}
	}
	if (condition.at(CON_COLOR)) {
		StatColor color;
		color.Generate(srcData, true, m_StartTurn, m_EndTurn);
		m_BaseList = color.GetList(m_BaseList);
		// for debug
		for (QList<int>::const_iterator iter = m_BaseList.cbegin(); iter != m_BaseList.constEnd(); ++iter) {
			qDebug() << "=== CON_COLOR " << *iter;
		}
	}
	if (condition.at(CON_SECTION)) {
		StatSection section;
		section.Generate(srcData, true, m_LastWeek);
		m_BaseList = section.GetList(m_BaseList);
		// for debug
		for (QList<int>::const_iterator iter = m_BaseList.cbegin(); iter != m_BaseList.constEnd(); ++iter) {
			qDebug() << "=== CON_SECTION " << *iter;
		}
	}
	if (condition.at(CON_PERIOD)) {
		StatPeriod period;
		period.Generate(srcData, true, m_LastWeek);
		m_PeriodList = period.GetList();
		// for debug
		for (QList<int>::const_iterator iter = m_PeriodList.cbegin(); iter != m_PeriodList.constEnd(); ++iter) {
			qDebug() << "=== CON_PERIOD " << *iter;
		}
	}
	if (condition.at(CON_SNIFFLING)) {
		StatSniffling sniffling;
		sniffling.Generate(srcData, false, m_StartTurn, m_EndTurn);
		m_BaseList = sniffling.GetList(m_BaseList);
		// for debug
		for (QList<int>::const_iterator iter = m_BaseList.cbegin(); iter != m_BaseList.constEnd(); ++iter) {
			qDebug() << "=== CON_SNIFFLING " << *iter;
		}
	}
	if (condition.at(CON_COUTINUE)) {
		StatContinue conti;
		conti.Generate(srcData, false, m_StartTurn, m_EndTurn);
		conti.GetList();
	}
}


void MgrLotto::ExportData()
{
	qDebug() << "ExportData()";
	m_LottoList.clear();

	// Create seed for the random
	// That is needed only once on application startup
	QTime time = QTime::currentTime();
	qsrand((uint)time.msec());

	//qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

	//QList<int> tempList = m_BaseList + m_PeriodList;
	QList<int> tempList;
	for (QList<int>::const_iterator iter = m_BaseList.cbegin(); iter != m_BaseList.constEnd(); ++iter) {
		if (!tempList.contains(*iter)) {
			tempList.append(*iter);
		}
	}
	for (QList<int>::const_iterator iter = m_PeriodList.cbegin(); iter != m_PeriodList.constEnd(); ++iter) {
		if (!tempList.contains(*iter)) {
			tempList.append(*iter);
		}
	}
	// for debug
	for (QList<int>::const_iterator iter = tempList.cbegin(); iter != tempList.constEnd(); ++iter) {
		qDebug() << "=== tempList " << *iter;
	}

	int count = 6;
	for (int i = 0; i < tempList.count() - 1; i++) {

		if (count <= 0) break;

		int random = RandInt(0, tempList.count() - 1);
		qDebug() << "random " << random;
		if (!m_LottoList.contains(tempList[random])) {
			qDebug() << "lotto number [" << i << "] " << tempList[random];
			m_LottoList.append(tempList[random]);
			count--;
		}
	}
}

int MgrLotto::RandInt(int low, int high)
{
	// Random number between low and high
	return qrand() % ((high + 1) - low) + low;
}


