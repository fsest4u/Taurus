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

		m_CompactData.insert(srcData.at(i).value(MgrCSV::COL_TURN), lottoNums);
	}

}

void MgrLotto::SetStatNumber(bool bNumber)
{
	qDebug() << "m_bBonus : " << m_bBonus;
	if (!bNumber) return;
	qDebug() << "SetStatNumber()";
	m_StatNumber.clear();

	QMapIterator<QString, QList<int>> num(m_CompactData);
	while (num.hasNext()) {
		num.next();
		QList<int> lottoNums = num.value();

		for (QList<int>::const_iterator iter = lottoNums.cbegin(); iter != lottoNums.constEnd(); ++iter) {
			// update
			if (m_StatNumber.contains(*iter)) {
				int count = m_StatNumber.value(*iter);
				m_StatNumber.insert(*iter, ++count);

			}
			// create
			else {
				m_StatNumber.insert(*iter, 1);
			}
		}
	}

	m_StatNumberWin.clear();
	QMapIterator<int, int> num2(m_StatNumber);
	while (num2.hasNext()) {
		num2.next();
		qDebug() << "[num] key : " << num2.key() << ", value : " << num2.value();
		m_StatNumberWin.insert(num2.value(), num2.key());
	}

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

}
void MgrLotto::SetStatSection(bool bSection)
{
	if (!bSection) return;
	qDebug() << "SetStatSection()";

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


