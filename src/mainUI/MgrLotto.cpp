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
#include "misc/SettingData.h"
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
	// 순차적으로 설정
	if (condition.at(CON_NUMBER)) {
		StatNumber number;
		number.Generate(srcData, m_bBonus, m_StartTurn, m_EndTurn);
		m_BaseList = number.GetList();
		// for debug
		for (QList<int>::const_iterator iter = m_BaseList.cbegin(); iter != m_BaseList.constEnd(); ++iter) {
			qDebug() << "=== CON_NUMBER " << *iter;
		}
	}
	// 랜덤하게 설정
	if (condition.at(CON_COLOR)) {
		StatColor color;
		color.Generate(srcData, true, m_StartTurn, m_EndTurn);
		m_BaseList = color.GetList(m_BaseList);
		// for debug
		for (QList<int>::const_iterator iter = m_BaseList.cbegin(); iter != m_BaseList.constEnd(); ++iter) {
			qDebug() << "=== CON_COLOR " << *iter;
		}
	}
	// 순차적으로 설정
	if (condition.at(CON_SECTION)) {
		StatSection section;
		section.Generate(srcData, true, m_LastWeek);
		m_BaseList = section.GetList(m_BaseList);
		// for debug
		for (QList<int>::const_iterator iter = m_BaseList.cbegin(); iter != m_BaseList.constEnd(); ++iter) {
			qDebug() << "=== CON_SECTION " << *iter;
		}
	}
	// 랜덤하게 설정
	if (condition.at(CON_PERIOD)) {
		StatPeriod period;
		period.Generate(srcData, true, m_LastWeek);
		m_PeriodList = period.GetList();
		// for debug
		for (QList<int>::const_iterator iter = m_PeriodList.cbegin(); iter != m_PeriodList.constEnd(); ++iter) {
			qDebug() << "=== CON_PERIOD " << *iter;
		}
	}
	// 순차적으로 설정
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


QList<int> MgrLotto::ExportData()
{
	qDebug() << "ExportData()";

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

	m_LottoList.clear();
	SettingData settings;
	while (m_LottoList.count() < 6) {

		// 랜덤하게 설정
		int random = settings.RandInt(0, tempList.count() - 1);
		qDebug() << "random " << random;
		if (!m_LottoList.contains(tempList[random])) {
			qDebug() << "lotto number " << tempList[random];
			m_LottoList.append(tempList[random]);
		}
	}

	return m_LottoList;
}



