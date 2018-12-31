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

#include "misc/SettingData.h"
#include "StatPeriod.h"
//#include "taurus_constants.h"

const int ARRAY_SIZE_PERIOD = 2;


StatPeriod::StatPeriod()
{
}

StatPeriod::~StatPeriod()
{
}


void StatPeriod::Generate(QMap<int, QList<int>> srcData, bool bBonus, int lastweek)
{
	qDebug() << "StatPeriod::Generate()";
	m_Stat1.clear();
	for (int i = 1; i < (45 + 1); i++) {
		m_Stat1.insert(i, true);
	}
	int turn = 0;

	QMapIterator<int, QList<int>> iterator1(srcData);
	iterator1.toBack();
	while (iterator1.hasPrevious() && turn < lastweek) {
		iterator1.previous();
		turn++;
		QList<int> numData = iterator1.value();
		// 보너스 조건
		if (!bBonus) { numData.pop_back(); }

		for (QList<int>::const_iterator iter = numData.cbegin(); iter != numData.constEnd(); ++iter) {
			m_Stat1.insert(*iter, false);
		}
	}

	// for debug
	QMapIterator<int, bool> iterator2(m_Stat1);
	while (iterator2.hasNext()) {
		iterator2.next();
		if (iterator2.value()) {
			qDebug() << "[StatPeriod] Number : " << iterator2.key() << ", Not appearing : " << iterator2.value();
		}
	}

}

QList<int> StatPeriod::GetList()
{
	SettingData settings;

	m_Ret.clear();
	int count = ARRAY_SIZE_PERIOD;

	while (count > 0) {

		int random = settings.RandInt(0, m_Stat1.count() - 1);

		if (m_Stat1.value(random)) {
			//qDebug() << "[StatPeriod] Number : " << random << ", Not appearing : " << true;
			if (!m_Ret.contains(random)) {
				m_Ret.append(random);
				count--;
			}
		}
	}

	return m_Ret;
}
