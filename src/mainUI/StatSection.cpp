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

#include "StatSection.h"
#include "MgrLotto.h"
//#include "taurus_constants.h"


StatSection::StatSection()
{
}

StatSection::~StatSection()
{
}


void StatSection::Generate(QMap<int, QList<int>> srcData)
{
	qDebug() << "StatSection::Generate()";
	m_Stat1.clear();
	int turn = 0;

	QMapIterator<int, QList<int>> iterator1(srcData);
	iterator1.toBack();
	while (iterator1.hasPrevious() && turn < MgrLotto::TURN_WEEK_10) {
		iterator1.previous();
		turn++;
		QList<int> numData = iterator1.value();

		int count = 0;

		for (QList<int>::const_iterator iter = numData.cbegin(); iter != numData.constEnd(); ++iter) {
			if (*iter <= MgrLotto::UNIT_10_10) {
				count = m_Stat1.value(MgrLotto::UNIT_10_1, 0);
				m_Stat1.insert(MgrLotto::UNIT_10_1, ++count);
			}
			else if (*iter <= MgrLotto::UNIT_10_20) {
				count = m_Stat1.value(MgrLotto::UNIT_10_10, 0);
				m_Stat1.insert(MgrLotto::UNIT_10_10, ++count);
			}
			else if (*iter <= MgrLotto::UNIT_10_30) {
				count = m_Stat1.value(MgrLotto::UNIT_10_20, 0);
				m_Stat1.insert(MgrLotto::UNIT_10_20, ++count);
			}
			else if (*iter <= MgrLotto::UNIT_10_40) {
				count = m_Stat1.value(MgrLotto::UNIT_10_30, 0);
				m_Stat1.insert(MgrLotto::UNIT_10_30, ++count);
			}
			else {
				count = m_Stat1.value(MgrLotto::UNIT_10_40, 0);
				m_Stat1.insert(MgrLotto::UNIT_10_40, ++count);
			}
		}
	}

	// for debug
	qDebug() << "=======================";
	QHashIterator<int, int> iterator2(m_Stat1);
	int amount = 0;
	while (iterator2.hasNext()) {
		iterator2.next();
		amount += iterator2.value();
		qDebug() << "[iterator2] key : " << iterator2.key() << ", value : " << iterator2.value();
	}
	qDebug() << "======================= amount : " << amount;
	QHashIterator<int, int> iterator3(m_Stat1);
	while (iterator3.hasNext()) {
		iterator3.next();
		double avg = iterator3.value() * 100 / amount;
		//qDebug() << "[iterator3] key : " << iterator3.key() << ", value : " << iterator3.value() << ", percent : " << QString("Total Amount : %L1").arg(avg, 0, 'f', 0);
		qDebug() << "[iterator3] key : " << iterator3.key() << ", value : " << iterator3.value() << ", percent : " << avg;
	}

}
