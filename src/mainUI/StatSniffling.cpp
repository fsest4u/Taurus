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

#include "StatSniffling.h"
#include "MgrLotto.h"
//#include "taurus_constants.h"

const int SNIFFLING_COUNT = 0;
const int SNIFFLING_TOTAL = 1;


StatSniffling::StatSniffling()
{
}

StatSniffling::~StatSniffling()
{
}


void StatSniffling::Generate(QMap<int, QList<int>> srcData, bool bBonus, int start, int end)
{
	qDebug() << "StatSniffling::Generate()";
	m_Stat1.clear();

	QMapIterator<int, QList<int>> iterator1(srcData);
	while (iterator1.hasNext()) {
		iterator1.next();
		// 회차 조건
		if (iterator1.key() < start || iterator1.key() > end) { continue; }

		QList<int> numData = iterator1.value();
		// 보너스 조건
		if (!bBonus) { numData.pop_back(); }

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
		m_Stat1.insert(iterator1.key(), sniffling);
	}

	// for debug
	m_Stat2.clear();
	QMapIterator<int, QMap<bool, int>> iterator2(m_Stat1);
	while (iterator2.hasNext()) {
		iterator2.next();
		int total = 0;
		QMapIterator<bool, int> val(iterator2.value());
		while (val.hasNext()) {
			val.next();
			total += val.value();
			//qDebug() << "[sniffling] 회차 : " << iterator2.key() << ", 홀짝 : " << val.key() << ", 숫자 : " << val.value();
		}

		QMap<bool, int> sniffling = iterator2.value();
		qDebug() << "[StatSniffling] Turn : " << iterator2.key() 
			<< ", Odd : " << sniffling.values(true).count()
			<< ", Even : " << sniffling.values(false).count()
			<< ", Total : " << total;

		QList<int> newList;
		newList.append(0);
		newList.append(0);
		QList<int> oldList = m_Stat2.value(sniffling.values(true).count(), newList);

		newList.clear();
		newList.append(oldList.at(SNIFFLING_COUNT) + 1);		// 홀수 개수의 회차 개수
		newList.append(oldList.at(SNIFFLING_TOTAL) + total);	// 숫자를 모두 더한 값
		m_Stat2.insert(sniffling.values(true).count(), newList);
	}

	m_Stat3.clear();
	QMapIterator<int, QList<int>> iterator3(m_Stat2);
	while (iterator3.hasNext()) {
		iterator3.next();
		QList<int> oldList(iterator3.value());
		QList<int> newList;
		newList.append(iterator3.key());
		qDebug() << "Total : " << oldList.at(SNIFFLING_TOTAL);
			newList.append(oldList.at(SNIFFLING_TOTAL) / oldList.at(SNIFFLING_COUNT));

		m_Stat3.insert(oldList.at(SNIFFLING_COUNT), newList);
	}
	QMapIterator<int, QList<int>> iterator4(m_Stat3);
	iterator4.toBack();
	while (iterator4.hasPrevious()) {
		iterator4.previous();
		qDebug() << "[StatSniffling] Win : " << iterator4.key()
			<< ", Odd : " << iterator4.value().at(SNIFFLING_COUNT)
			<< ", Average : " << iterator4.value().at(SNIFFLING_TOTAL);

	}
}
