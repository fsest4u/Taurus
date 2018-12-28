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

#include "StatContinue.h"
#include "MgrLotto.h"
//#include "taurus_constants.h"


StatContinue::StatContinue()
{
}

StatContinue::~StatContinue()
{
}


void StatContinue::Generate(QMap<int, QList<int>> srcData, bool bBonus, int start, int end)
{
	qDebug() << "StatContinue::Generate()";
	m_Stat1.clear();

	QMapIterator<int, QList<int>> iterator1(srcData);
	while (iterator1.hasNext()) {
		iterator1.next();
		// 회차 조건
		if (iterator1.key() < start || iterator1.key() > end) { continue; }
		
		QList<int> numData = iterator1.value();
		// 보너스 조건
		if (!bBonus) { numData.pop_back(); }
		
		QList<int> tempData;
		tempData.clear();

		int previous = -1;

		for (QList<int>::const_iterator iter = numData.cbegin(); iter != numData.constEnd(); ++iter) {
			if (*iter == previous + 1) {
				tempData.insert(0, previous);
				tempData.insert(1, *iter);
				m_Stat1.insertMulti(iterator1.key(), tempData);
			}
			previous = *iter;
		}
	}

	// for debug
	QList<int> keys = m_Stat1.uniqueKeys();
	for (QList<int>::const_iterator iter = keys.cbegin(); iter != keys.constEnd(); ++iter) {
		qDebug() << "[StatContinue] Turn : " << *iter << ", Pair : " << m_Stat1.values(*iter).count();
	}

	//QMapIterator<int, QList<int>> iterator2(m_Stat1);
	//while (iterator2.hasNext()) {
	//	iterator2.next();
	//	QList<int> val(iterator2.value());
	//	qDebug() << "[StatContinue] Turn : " << iterator2.key() << ", conti1 : " << val.at(0) << ", conti2 : " << val.at(1);
	//}

}
