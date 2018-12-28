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
//#include "taurus_constants.h"

const int ARRAY_SIZE_SECTION = 20;


StatSection::StatSection()
{
}

StatSection::~StatSection()
{
}

void StatSection::Generate(QMap<int, QList<int>> srcData, bool bBonus, int lastweek)
{
	qDebug() << "StatSection::Generate()";
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
	qDebug() << "=======================";
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
		qDebug() << "[StatSection] Win : " << iterator2.key() << ", Number Area : " << iterator2.value() << ", percent : " << avg;
	}

}

QList<int> StatSection::GetList(QList<int> baseList)
{
	int amount = m_Stat3.count();

	m_Ret.clear();
	QMapIterator<int, int> iterator2(m_Stat4);
	iterator2.toBack();
	while (iterator2.hasPrevious()) {
		iterator2.previous();

		int avg = iterator2.key() * 100 / amount;
		//qDebug() << "[StatSection] Win : " << iterator2.key() << ", Number Area : " << iterator2.value() << ", percent : " << avg;
		int count = ARRAY_SIZE_SECTION * avg / 100;
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

//void StatSection::Generate_old(QMap<int, QList<int>> srcData, bool bBonus, int lastweek)
//{
//	qDebug() << "StatSection::Generate()";
//	m_Stat1.clear();
//	int turn = 0;
//
//	QMapIterator<int, QList<int>> iterator1(srcData);
//	iterator1.toBack();
//	while (iterator1.hasPrevious() && turn < lastweek) {
//		iterator1.previous();
//		turn++;
//		QList<int> numData = iterator1.value();
//		// 보너스 조건
//		if (!bBonus) { numData.pop_back(); }
//
//		int count = 0;
//
//		for (QList<int>::const_iterator iter = numData.cbegin(); iter != numData.constEnd(); ++iter) {
//			if (*iter <= MgrLotto::UNIT_10_10) {
//				count = m_Stat1.value(MgrLotto::UNIT_10_1, 0);
//				m_Stat1.insert(MgrLotto::UNIT_10_1, ++count);
//			}
//			else if (*iter <= MgrLotto::UNIT_10_20) {
//				count = m_Stat1.value(MgrLotto::UNIT_10_10, 0);
//				m_Stat1.insert(MgrLotto::UNIT_10_10, ++count);
//			}
//			else if (*iter <= MgrLotto::UNIT_10_30) {
//				count = m_Stat1.value(MgrLotto::UNIT_10_20, 0);
//				m_Stat1.insert(MgrLotto::UNIT_10_20, ++count);
//			}
//			else if (*iter <= MgrLotto::UNIT_10_40) {
//				count = m_Stat1.value(MgrLotto::UNIT_10_30, 0);
//				m_Stat1.insert(MgrLotto::UNIT_10_30, ++count);
//			}
//			else {
//				count = m_Stat1.value(MgrLotto::UNIT_10_40, 0);
//				m_Stat1.insert(MgrLotto::UNIT_10_40, ++count);
//			}
//		}
//	}
//
//	// for debug
//	qDebug() << "=======================";
//	QMapIterator<int, int> iterator2(m_Stat1);
//	int amount = 0;
//	while (iterator2.hasNext()) {
//		iterator2.next();
//		amount += iterator2.value();
//		qDebug() << "[iterator2] key : " << iterator2.key() << ", value : " << iterator2.value();
//	}
//	qDebug() << "======================= amount : " << amount;
//	QMapIterator<int, int> iterator3(m_Stat1);
//	while (iterator3.hasNext()) {
//		iterator3.next();
//		double avg = iterator3.value() * 100 / amount;
//		//qDebug() << "[iterator3] key : " << iterator3.key() << ", value : " << iterator3.value() << ", percent : " << QString("Total Amount : %L1").arg(avg, 0, 'f', 0);
//		qDebug() << "[iterator3] key : " << iterator3.key() << ", value : " << iterator3.value() << ", percent : " << avg;
//	}
//
//}
