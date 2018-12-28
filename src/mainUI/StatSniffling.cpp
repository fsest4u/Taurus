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
	}

}
