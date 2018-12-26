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
	m_CompactData.clear();
	m_StatNumber.clear();

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
	m_bBonus = bBonus;
	m_StartTurn = start;
	m_EndTurn = end;
	m_LastWeek = lastweek;
}

void MgrLotto::GenerateInfo(QList<bool> condition, QMap<int, QList<int>> srcData)
{
	if (condition.at(CON_NUMBER)) {
		StatNumber number;
		number.Generate(srcData);
	}
	else if (condition.at(CON_COLOR)) {
		StatColor color;
		color.Generate(srcData);
	}
	else if (condition.at(CON_SECTION)) {
		StatSection section;
		section.Generate(srcData);
	}
	else if (condition.at(CON_PERIOD)) {
		StatPeriod period;
		period.Generate(srcData);
	}
	else if (condition.at(CON_SNIFFLING)) {
		StatSniffling sniffling;
		sniffling.Generate(srcData);
	}
	else {	// CON_CONTINUE
		StatContinue conti;
		conti.Generate(srcData);
	}
}

void MgrLotto::SetStatNumber(bool bNumber)
{
	qDebug() << "m_bBonus : " << m_bBonus;
	if (!bNumber) return;
	qDebug() << "SetStatNumber()";
	m_StatNumber.clear();
	m_StatNumberWin.clear();

	QMapIterator<int, QList<int>> iterator1(m_CompactData);
	while (iterator1.hasNext()) {
		iterator1.next();
		QList<int> numData = iterator1.value();

		for (QList<int>::const_iterator iter = numData.cbegin(); iter != numData.constEnd(); ++iter) {
			//// update
			//if (m_StatNumber.contains(*iter)) {
			//	int count = m_StatNumber.value(*iter);
			//	m_StatNumber.insert(*iter, ++count);

			//}
			//// create
			//else {
			//	m_StatNumber.insert(*iter, 1);
			//}
			int count = m_StatNumber.value(*iter, 0);
			m_StatNumber.insert(*iter, ++count);

		}
	}

	QMapIterator<int, int> iterator2(m_StatNumber);
	while (iterator2.hasNext()) {
		iterator2.next();
		// for debug
		qDebug() << "[iterator1] key : " << iterator2.key() << ", value : " << iterator2.value();
		m_StatNumberWin.insertMulti(iterator2.value(), iterator2.key());
	}

	// for debug
	qDebug() << "=======================";
	QMapIterator<int, int> iterator3(m_StatNumberWin);
	while (iterator3.hasNext()) {
		iterator3.next();
		qDebug() << "[iterator3] key : " << iterator3.key() << ", value : " << iterator3.value();
	}


}
void MgrLotto::SetStatColor(bool bColor)
{
	if (!bColor) return;
	qDebug() << "SetStatColor()";
	m_StatColor.clear();
	m_StatColorTot.clear();

	QMapIterator<int, QList<int>> iterator1(m_CompactData);
	while (iterator1.hasNext()) {
		iterator1.next();
		QList<int> numData = iterator1.value();

		QHash<int, int> statColor;
		statColor.clear();
		int count = 0;

		for (QList<int>::const_iterator iter = numData.cbegin(); iter != numData.constEnd(); ++iter) {
			if (*iter <= UNIT_10_10) {
				count = statColor.value(UNIT_10_1, 0);
				statColor.insert(UNIT_10_1, ++count);
			}
			else if (*iter <= UNIT_10_20) {
				count = statColor.value(UNIT_10_10, 0);
				statColor.insert(UNIT_10_10, ++count);
			}
			else if (*iter <= UNIT_10_30) {
				count = statColor.value(UNIT_10_20, 0);
				statColor.insert(UNIT_10_20, ++count);
			}
			else if (*iter <= UNIT_10_40) {
				count = statColor.value(UNIT_10_30, 0);
				statColor.insert(UNIT_10_30, ++count);
			}
			else {
				count = statColor.value(UNIT_10_40, 0);
				statColor.insert(UNIT_10_40, ++count);
			}
		}

		// 색상별
		m_StatColor.insert(iterator1.key(), statColor);
		// 색상별 합계
		int total = 0;
		QHashIterator<int, int> iterator2(statColor);
		while (iterator2.hasNext()) {
			iterator2.next();
			total = m_StatColorTot.value(iterator2.key(), 0);
			m_StatColorTot.insert(iterator2.key(), iterator2.value() + total);
		}
	}

	// for debug
	QMapIterator<int, QHash<int, int>> iterator3(m_StatColor);
	while (iterator3.hasNext()) {
		iterator3.next();
		QHashIterator<int, int> val(iterator3.value());
		while (val.hasNext()) {
			val.next();
			qDebug() << "[iterator3] iterator3.key : " << iterator3.key() << ", key : " << val.key() << ", value : " << val.value();
		}
	}
	qDebug() << "=======================";
	QHashIterator<int, int> iterator4(m_StatColorTot);
	int amount = 0;
	while (iterator4.hasNext()) {
		iterator4.next();
		amount += iterator4.value();
		qDebug() << "[iterator4] key : " << iterator4.key() << ", value : " << iterator4.value();
	}
	qDebug() << "======================= amount : " << amount;
	QHashIterator<int, int> iterator5(m_StatColorTot);
	while (iterator5.hasNext()) {
		iterator5.next();
		double avg = iterator5.value() * 100 / amount;
		//qDebug() << "[iterator5] key : " << iterator5.key() << ", value : " << iterator5.value() << ", percent : " << QString("Total Amount : %L1").arg(avg, 0, 'f', 0);
		qDebug() << "[iterator5] key : " << iterator5.key() << ", value : " << iterator5.value() << ", percent : " << avg;
	}

}
void MgrLotto::SetStatSection(bool bSection)
{
	if (!bSection) return;
	qDebug() << "SetStatSection()";
	m_StatSec10.clear();
	int turn = 0;

	QMapIterator<int, QList<int>> iterator1(m_CompactData);
	iterator1.toBack();
	while (iterator1.hasPrevious() && turn < TURN_WEEK_10) {
		iterator1.previous();
		turn++;
		QList<int> numData = iterator1.value();

		int count = 0;

		for (QList<int>::const_iterator iter = numData.cbegin(); iter != numData.constEnd(); ++iter) {
			if (*iter <= UNIT_10_10) {
				count = m_StatSec10.value(UNIT_10_1, 0);
				m_StatSec10.insert(UNIT_10_1, ++count);
			}
			else if (*iter <= UNIT_10_20) {
				count = m_StatSec10.value(UNIT_10_10, 0);
				m_StatSec10.insert(UNIT_10_10, ++count);
			}
			else if (*iter <= UNIT_10_30) {
				count = m_StatSec10.value(UNIT_10_20, 0);
				m_StatSec10.insert(UNIT_10_20, ++count);
			}
			else if (*iter <= UNIT_10_40) {
				count = m_StatSec10.value(UNIT_10_30, 0);
				m_StatSec10.insert(UNIT_10_30, ++count);
			}
			else {
				count = m_StatSec10.value(UNIT_10_40, 0);
				m_StatSec10.insert(UNIT_10_40, ++count);
			}
		}
	}

	// for debug
	qDebug() << "=======================";
	QHashIterator<int, int> iterator2(m_StatSec10);
	int amount = 0;
	while (iterator2.hasNext()) {
		iterator2.next();
		amount += iterator2.value();
		qDebug() << "[iterator2] key : " << iterator2.key() << ", value : " << iterator2.value();
	}
	qDebug() << "======================= amount : " << amount;
	QHashIterator<int, int> iterator3(m_StatSec10);
	while (iterator3.hasNext()) {
		iterator3.next();
		double avg = iterator3.value() * 100 / amount;
		//qDebug() << "[iterator3] key : " << iterator3.key() << ", value : " << iterator3.value() << ", percent : " << QString("Total Amount : %L1").arg(avg, 0, 'f', 0);
		qDebug() << "[iterator3] key : " << iterator3.key() << ", value : " << iterator3.value() << ", percent : " << avg;
	}

}
void MgrLotto::SetStatPeriod(bool bPeriod)
{
	if (!bPeriod) return;
	qDebug() << "SetStatPeriod()";
	m_StatPeriod.clear();
	for (int i = 1; i < (45+1); i++) {
		m_StatPeriod.insert(i, true);
	}
	int turn = 0;

	QMapIterator<int, QList<int>> iterator1(m_CompactData);
	iterator1.toBack();
	while (iterator1.hasPrevious() && turn < TURN_WEEK_10) {
		iterator1.previous();
		turn++;
		QList<int> numData = iterator1.value();

		int count = 0;

		for (QList<int>::const_iterator iter = numData.cbegin(); iter != numData.constEnd(); ++iter) {
			m_StatPeriod.insert(*iter, false);
		}
	}

	// for debug
	qDebug() << "=======================";
	QHashIterator<int, bool> iterator2(m_StatPeriod);
	int amount = 0;
	while (iterator2.hasNext()) {
		iterator2.next();
		if (iterator2.value()) {
			qDebug() << "[iterator2] key : " << iterator2.key() << ", value : " << iterator2.value();
		}
	}

}
void MgrLotto::SetStatSniffling(bool bSniffling)
{
	if (!bSniffling) return;
	qDebug() << "SetStatSniffling()";
	m_StatSniffling.clear();

	QMapIterator<int, QList<int>> iterator1(m_CompactData);
	while (iterator1.hasNext()) {
		iterator1.next();
		QList<int> numData = iterator1.value();

		QMap<bool, int>  sniffling;
		sniffling.clear();
		for (QList<int>::const_iterator iter = numData.cbegin(); iter != numData.constEnd(); ++iter) {
			if (*iter % 2) {
				sniffling.insertMulti(true, *iter);// odd number
			}
			else {
				sniffling.insertMulti(false, *iter);// even number
			}
		}
		m_StatSniffling.insert(iterator1.key(), sniffling);
	}

	// for debug
	QMapIterator<int, QMap<bool, int>> iterator2(m_StatSniffling);
	while (iterator2.hasNext()) {
		iterator2.next();
		QMapIterator<bool, int> val(iterator2.value());
		while (val.hasNext()) {
			val.next();
			qDebug() << "[sniffling] iterator2.key : " << iterator2.key() << ", key : " << val.key() << ", value : " << val.value();
		}
	}

}
void MgrLotto::SetStatContinue(bool bContinue)
{
	if (!bContinue) return;
	qDebug() << "SetStatContinue()";
	m_StatContinue.clear();

	QMapIterator<int, QList<int>> iterator1(m_CompactData);
	while (iterator1.hasNext()) {
		iterator1.next();
		QList<int> numData = iterator1.value();
		QList<int> continueNum;
		continueNum.clear();

		int previous = -1;

		for (QList<int>::const_iterator iter = numData.cbegin(); iter != numData.constEnd(); ++iter) {
			if (*iter == previous + 1) {
				continueNum.insert(0, previous);
				continueNum.insert(1, *iter);
				m_StatContinue.insert(iterator1.key(), continueNum);
			}
			previous = *iter;
		}
	}

	// for debug
	QMapIterator<int, QList<int>> iterator2(m_StatContinue);
	while (iterator2.hasNext()) {
		iterator2.next();
		QList<int> val(iterator2.value());
		//for (int i = 0; i< val.count(); i++) {
			qDebug() << "[continue] iterator2.key : " << iterator2.key() << ", key : " << val.at(0) << ", value : " << val.at(1);
		//}
	}

}


void MgrLotto::ExportData()
{
	qDebug() << "ExportData()";

}


