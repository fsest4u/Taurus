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

#include "StatColor.h"
#include "MgrLotto.h"
//#include "taurus_constants.h"


StatColor::StatColor()
{
}

StatColor::~StatColor()
{
}


void StatColor::Generate(QMap<int, QList<int>> srcData)
{
	qDebug() << "StatColor::Generate()";
	m_Stat1.clear();
	m_Stat2.clear();

	QMapIterator<int, QList<int>> iterator1(srcData);
	while (iterator1.hasNext()) {
		iterator1.next();
		QList<int> numData = iterator1.value();

		QHash<int, int> tempData;
		tempData.clear();
		int count = 0;

		for (QList<int>::const_iterator iter = numData.cbegin(); iter != numData.constEnd(); ++iter) {
			if (*iter <= MgrLotto::UNIT_10_10) {
				count = tempData.value(MgrLotto::UNIT_10_1, 0);
				tempData.insert(MgrLotto::UNIT_10_1, ++count);
			}
			else if (*iter <= MgrLotto::UNIT_10_20) {
				count = tempData.value(MgrLotto::UNIT_10_10, 0);
				tempData.insert(MgrLotto::UNIT_10_10, ++count);
			}
			else if (*iter <= MgrLotto::UNIT_10_30) {
				count = tempData.value(MgrLotto::UNIT_10_20, 0);
				tempData.insert(MgrLotto::UNIT_10_20, ++count);
			}
			else if (*iter <= MgrLotto::UNIT_10_40) {
				count = tempData.value(MgrLotto::UNIT_10_30, 0);
				tempData.insert(MgrLotto::UNIT_10_30, ++count);
			}
			else {
				count = tempData.value(MgrLotto::UNIT_10_40, 0);
				tempData.insert(MgrLotto::UNIT_10_40, ++count);
			}
		}

		// 색상별
		m_Stat1.insert(iterator1.key(), tempData);
		// 색상별 합계
		int total = 0;
		QHashIterator<int, int> iterator2(tempData);
		while (iterator2.hasNext()) {
			iterator2.next();
			total = m_Stat2.value(iterator2.key(), 0);
			m_Stat2.insert(iterator2.key(), iterator2.value() + total);
		}
	}

	// for debug
	QMapIterator<int, QHash<int, int>> iterator3(m_Stat1);
	while (iterator3.hasNext()) {
		iterator3.next();
		QHashIterator<int, int> val(iterator3.value());
		while (val.hasNext()) {
			val.next();
			qDebug() << "[iterator3] iterator3.key : " << iterator3.key() << ", key : " << val.key() << ", value : " << val.value();
		}
	}
	qDebug() << "=======================";
	QHashIterator<int, int> iterator4(m_Stat2);
	int amount = 0;
	while (iterator4.hasNext()) {
		iterator4.next();
		amount += iterator4.value();
		qDebug() << "[iterator4] key : " << iterator4.key() << ", value : " << iterator4.value();
	}
	qDebug() << "======================= amount : " << amount;
	QHashIterator<int, int> iterator5(m_Stat2);
	while (iterator5.hasNext()) {
		iterator5.next();
		double avg = iterator5.value() * 100 / amount;
		//qDebug() << "[iterator5] key : " << iterator5.key() << ", value : " << iterator5.value() << ", percent : " << QString("Total Amount : %L1").arg(avg, 0, 'f', 0);
		qDebug() << "[iterator5] key : " << iterator5.key() << ", value : " << iterator5.value() << ", percent : " << avg;
	}

}
