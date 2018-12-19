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

void MgrLotto::SetSourceData(QList<QStringList> srcData)
{
	m_CompactData.clear();
	QList<int> lottoNums;
	lottoNums.clear();

	for (int i = m_StartRow; i < srcData.size(); i++) {
		lottoNums.clear();
		lottoNums.insert(0, srcData.at(i).value(MgrCSV::COL_1ST_NUM).toInt());
		lottoNums.insert(1, srcData.at(i).value(MgrCSV::COL_2ND_NUM).toInt());
		lottoNums.insert(2, srcData.at(i).value(MgrCSV::COL_3RD_NUM).toInt());
		lottoNums.insert(3, srcData.at(i).value(MgrCSV::COL_4TH_NUM).toInt());
		lottoNums.insert(4, srcData.at(i).value(MgrCSV::COL_5TH_NUM).toInt());
		lottoNums.insert(5, srcData.at(i).value(MgrCSV::COL_6TH_NUM).toInt());
		if (m_bBonus) 
			lottoNums.insert(6, srcData.at(i).value(MgrCSV::COL_BONUS_NUM).toInt());

		m_CompactData.insert(srcData.at(i).value(MgrCSV::COL_TURN).toInt(), lottoNums);
	}

}

void MgrLotto::SetStatNumber(bool bNumber)
{
	qDebug() << "m_bBonus : " << m_bBonus;
	if (!bNumber) return;
	qDebug() << "SetStatNumber()";
	m_StatNumber.clear();
	m_StatNumberWin.clear();

	QMapIterator<int, QList<int>> num(m_CompactData);
	while (num.hasNext()) {
		num.next();
		QList<int> lottoNums = num.value();

		for (QList<int>::const_iterator iter = lottoNums.cbegin(); iter != lottoNums.constEnd(); ++iter) {
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

	QMapIterator<int, int> num2(m_StatNumber);
	while (num2.hasNext()) {
		num2.next();
		// for debug
		qDebug() << "[num] key : " << num2.key() << ", value : " << num2.value();
		m_StatNumberWin.insertMulti(num2.value(), num2.key());
	}

	// for debug
	qDebug() << "=======================";
	QMapIterator<int, int> win(m_StatNumberWin);
	while (win.hasNext()) {
		win.next();
		qDebug() << "[win] key : " << win.key() << ", value : " << win.value();
	}


}
void MgrLotto::SetStatColor(bool bColor)
{
	if (!bColor) return;
	qDebug() << "SetStatColor()";
	m_StatColor.clear();
	m_StatColorTot.clear();

	QMapIterator<int, QList<int>> num(m_CompactData);
	while (num.hasNext()) {
		num.next();
		QList<int> lottoNums = num.value();

		QHash<int, int> statColor;
		statColor.clear();
		int count = 0;

		for (QList<int>::const_iterator iter = lottoNums.cbegin(); iter != lottoNums.constEnd(); ++iter) {
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
		m_StatColor.insert(num.key(), statColor);
		// 색상별 합계
		int total = 0;
		QHashIterator<int, int> colorItem(statColor);
		while (colorItem.hasNext()) {
			colorItem.next();
			total = m_StatColorTot.value(colorItem.key(), 0);
			m_StatColorTot.insert(colorItem.key(), colorItem.value() + total);
		}
	}

	// for debug
	QMapIterator<int, QHash<int, int>> col(m_StatColor);
	while (col.hasNext()) {
		col.next();
		QHashIterator<int, int> val(col.value());
		while (val.hasNext()) {
			val.next();
			qDebug() << "[col] col.key : " << col.key() << ", key : " << val.key() << ", value : " << val.value();
		}
	}
	qDebug() << "=======================";
	QHashIterator<int, int> tot(m_StatColorTot);
	int amount = 0;
	while (tot.hasNext()) {
		tot.next();
		amount += tot.value();
		qDebug() << "[tot] key : " << tot.key() << ", value : " << tot.value();
	}
	qDebug() << "======================= amount : " << amount;
	QHashIterator<int, int> tot2(m_StatColorTot);
	while (tot2.hasNext()) {
		tot2.next();
		double avg = tot2.value() * 100 / amount;
		//qDebug() << "[tot2] key : " << tot2.key() << ", value : " << tot2.value() << ", percent : " << QString("Total Amount : %L1").arg(avg, 0, 'f', 0);
		qDebug() << "[tot2] key : " << tot2.key() << ", value : " << tot2.value() << ", percent : " << avg;
	}

}
void MgrLotto::SetStatSection(bool bSection)
{
	if (!bSection) return;
	qDebug() << "SetStatSection()";
	m_StatSec10.clear();
	int turn = 0;

	QMapIterator<int, QList<int>> num(m_CompactData);
	num.toBack();
	while (num.hasPrevious() && turn < 10) {
		num.previous();
		turn++;
		QList<int> lottoNums = num.value();

		int count = 0;

		for (QList<int>::const_iterator iter = lottoNums.cbegin(); iter != lottoNums.constEnd(); ++iter) {
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
	QHashIterator<int, int> tot(m_StatSec10);
	int amount = 0;
	while (tot.hasNext()) {
		tot.next();
		amount += tot.value();
		qDebug() << "[tot] key : " << tot.key() << ", value : " << tot.value();
	}
	qDebug() << "======================= amount : " << amount;
	QHashIterator<int, int> tot2(m_StatSec10);
	while (tot2.hasNext()) {
		tot2.next();
		double avg = tot2.value() * 100 / amount;
		//qDebug() << "[tot2] key : " << tot2.key() << ", value : " << tot2.value() << ", percent : " << QString("Total Amount : %L1").arg(avg, 0, 'f', 0);
		qDebug() << "[tot2] key : " << tot2.key() << ", value : " << tot2.value() << ", percent : " << avg;
	}

}
void MgrLotto::SetStatPeriod(bool bPeriod)
{
	if (!bPeriod) return;
	qDebug() << "SetStatPeriod()";

}
void MgrLotto::SetStatSniffling(bool bSniffling)
{
	if (!bSniffling) return;
	qDebug() << "SetStatSniffling()";

}
void MgrLotto::SetStatContinue(bool bContinue)
{
	if (!bContinue) return;
	qDebug() << "SetStatContinue()";

}


void MgrLotto::ExportData()
{
	qDebug() << "ExportData()";

}


