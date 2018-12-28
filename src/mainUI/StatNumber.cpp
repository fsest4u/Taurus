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

#include "StatNumber.h"
#include "MgrLotto.h"
//#include "taurus_constants.h"


StatNumber::StatNumber()
{
}

StatNumber::~StatNumber()
{
}


void StatNumber::Generate(QMap<int, QList<int>> srcData, bool bBonus, int start, int end)
{
	qDebug() << "StatNumber::Generate()";
	m_Stat1.clear();
	m_Stat2.clear();

	QMapIterator<int, QList<int>> iterator1(srcData);
	while (iterator1.hasNext()) {
		iterator1.next();
		// 회차 조건
		if (iterator1.key() < start || iterator1.key() > end) { continue; }

		QList<int> numData = iterator1.value();
		// 보너스 조건
		if (!bBonus) { numData.pop_back(); }

		for (QList<int>::const_iterator iter = numData.cbegin(); iter != numData.constEnd(); ++iter) {
			int count = m_Stat1.value(*iter, 0);
			m_Stat1.insert(*iter, ++count);

		}
	}

	qDebug() << "Order Number =======================";
	QMapIterator<int, int> iterator2(m_Stat1);
	while (iterator2.hasNext()) {
		iterator2.next();
		// for debug
		qDebug() << "Number : " << iterator2.key() << ", Win : " << iterator2.value();
		m_Stat2.insertMulti(iterator2.value(), iterator2.key());
	}

	// for debug
	qDebug() << "Order Win =======================";
	QMapIterator<int, int> iterator3(m_Stat2);
	iterator3.toBack();
	while (iterator3.hasPrevious()) {
		iterator3.previous();
		qDebug() << "Win : " << iterator3.key() << ", Number : " << iterator3.value();
	}


}
