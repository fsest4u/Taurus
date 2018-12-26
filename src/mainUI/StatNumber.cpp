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


void StatNumber::Generate(QMap<int, QList<int>> srcData)
{
	qDebug() << "StatNumber::Generate()";
	m_Stat1.clear();
	m_Stat2.clear();

	QMapIterator<int, QList<int>> iterator1(srcData);
	while (iterator1.hasNext()) {
		iterator1.next();
		QList<int> numData = iterator1.value();

		for (QList<int>::const_iterator iter = numData.cbegin(); iter != numData.constEnd(); ++iter) {
			int count = m_Stat1.value(*iter, 0);
			m_Stat1.insert(*iter, ++count);

		}
	}

	QMapIterator<int, int> iterator2(m_Stat1);
	while (iterator2.hasNext()) {
		iterator2.next();
		// for debug
		qDebug() << "[iterator2] key : " << iterator2.key() << ", value : " << iterator2.value();
		m_Stat2.insertMulti(iterator2.value(), iterator2.key());
	}

	// for debug
	qDebug() << "=======================";
	QMapIterator<int, int> iterator3(m_Stat2);
	while (iterator3.hasNext()) {
		iterator3.next();
		qDebug() << "[iterator3] key : " << iterator3.key() << ", value : " << iterator3.value();
	}


}
