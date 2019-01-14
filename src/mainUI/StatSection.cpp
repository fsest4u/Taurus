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
#include "StatSection.h"
//#include "taurus_constants.h"

const int ARRAY_SIZE_SECTION = 30;


StatSection::StatSection()
{
}

StatSection::~StatSection()
{
}

void StatSection::Generate(QMap<int, QList<int>> srcData, bool bBonus, int lastweek)
{
	//qDebug() << "StatSection::Generate()";
	m_Stat3.clear();
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
			if (*iter < MgrLotto::UNIT_10_11) {
				m_Stat3.insertMulti(MgrLotto::UNIT_10_1, 1);
			}
			else if (*iter < MgrLotto::UNIT_10_21) {
				m_Stat3.insertMulti(MgrLotto::UNIT_10_11, 1);
			}
			else if (*iter < MgrLotto::UNIT_10_31) {
				m_Stat3.insertMulti(MgrLotto::UNIT_10_21, 1);
			}
			else if (*iter < MgrLotto::UNIT_10_41) {
				m_Stat3.insertMulti(MgrLotto::UNIT_10_31, 1);
			}
			else {
				m_Stat3.insertMulti(MgrLotto::UNIT_10_41, 1);
			}
		}
	}

	// for debug
	//qDebug() << "=======================";
	int amount = m_Stat3.count();

	QList<int> keys = m_Stat3.uniqueKeys();
	for (QList<int>::const_iterator iter = keys.cbegin(); iter != keys.constEnd(); ++iter) {
		//double avg = m_Stat3.values(*iter).count() * 100 / amount;
		//qDebug() << "[StatSection] key : " << *iter << ", value : " << m_Stat3.values(*iter).count() << ", percent : " << avg;
		m_Stat4.insert(m_Stat3.values(*iter).count(), *iter);
	}

	QMapIterator<int, int> iterator2(m_Stat4);
	iterator2.toBack();
	while (iterator2.hasPrevious()) {
		iterator2.previous();

		int avg = iterator2.key() * 100 / amount;
		//qDebug() << "[StatSection] Win : " << iterator2.key() << ", Number Area : " << iterator2.value() << ", percent : " << avg;
	}

}QList<int> StatSection::GetList(QList<int> baseList)
{
	int amount = m_Stat3.count();

	m_Ret.clear();
	QMapIterator<int, int> iterator2(m_Stat4);
	iterator2.toBack();
	while (iterator2.hasPrevious()) {
		iterator2.previous();

		int avg = iterator2.key() * 100 / amount;
		// 구할 항목 개수와 전체 항목 개수를 비교하여 제일 작은 값으로 설정
		int count = qMin(baseList.count() - 5, ARRAY_SIZE_SECTION) * avg / 100;
		//qDebug() << "[GetList] Number Area : " << iterator2.value() << ", count : " << count;
		for (QList<int>::const_iterator iter = baseList.constBegin(); iter != baseList.constEnd(); ++iter) {

			if (count <= 0) break;

			if (*iter >= iterator2.value() && *iter < iterator2.value() + 10) {
				m_Ret.append(*iter);
				count--;
			}
		}
	}

	return m_Ret;
}

QList<int> StatSection::GetListRandom(QList<int> baseList)
{
	SettingData settings;
	int limitCount = 10000;

	int amount = m_Stat3.count();

	m_Ret.clear();
	QMapIterator<int, int> iterator2(m_Stat4);
	iterator2.toBack();
	while (iterator2.hasPrevious()) {
		iterator2.previous();

		int avg = iterator2.key() * 100 / amount;
		// 구할 항목 개수와 전체 항목 개수를 비교하여 제일 작은 값으로 설정
		int count = qMin(baseList.count() - 5, ARRAY_SIZE_SECTION) * avg / 100;
		//qDebug() << "[GetListRandom] Number Area : " << iterator2.value() << ", count : " << count;
		while (count > 0 && limitCount > 0) {
			limitCount--;

			int random = settings.RandInt(0, baseList.count() - 1);

			if (baseList.at(random) >= iterator2.value()
				&& baseList.at(random) < iterator2.value() + 10
				&& !m_Ret.contains(baseList.at(random))) {
				m_Ret.append(baseList.at(random));
				count--;
			}
		}
		if (count > 0) {
			m_Ret.clear();
		}
	}

	return m_Ret;
}

