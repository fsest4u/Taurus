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

#include "StatPeriod.h"
#include "MgrLotto.h"
//#include "taurus_constants.h"


StatPeriod::StatPeriod()
{
}

StatPeriod::~StatPeriod()
{
}


void StatPeriod::Generate(QMap<int, QList<int>> srcData)
{
	qDebug() << "StatPeriod::Generate()";
	m_Stat1.clear();
	for (int i = 1; i < (45 + 1); i++) {
		m_Stat1.insert(i, true);
	}
	int turn = 0;

	QMapIterator<int, QList<int>> iterator1(srcData);
	iterator1.toBack();
	while (iterator1.hasPrevious() && turn < MgrLotto::TURN_WEEK_10) {
		iterator1.previous();
		turn++;
		QList<int> numData = iterator1.value();

		int count = 0;

		for (QList<int>::const_iterator iter = numData.cbegin(); iter != numData.constEnd(); ++iter) {
			m_Stat1.insert(*iter, false);
		}
	}

	// for debug
	qDebug() << "=======================";
	QHashIterator<int, bool> iterator2(m_Stat1);
	int amount = 0;
	while (iterator2.hasNext()) {
		iterator2.next();
		if (iterator2.value()) {
			qDebug() << "[iterator2] key : " << iterator2.key() << ", value : " << iterator2.value();
		}
	}

}
