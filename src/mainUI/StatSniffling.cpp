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
#include "StatSniffling.h"
#include "MgrLotto.h"
//#include "taurus_constants.h"

const int SNIFFLING_COUNT = 0;
const int SNIFFLING_TOTAL = 1;

const int ARRAY_SIZE_SNIFFLING = 25;
const int ARRAY_SIZE_SNIFFLING_TIME = 2;



StatSniffling::StatSniffling()
{
}

StatSniffling::~StatSniffling()
{
}


void StatSniffling::Generate(QMap<int, QList<int>> srcData, bool bBonus, int start, int end)
{
	//qDebug() << "StatSniffling::Generate()";
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
		//qDebug() << "[StatSniffling] Turn : " << iterator2.key() 
		//	<< ", Odd : " << sniffling.values(true).count()
		//	<< ", Even : " << sniffling.values(false).count()
		//	<< ", Total : " << total;

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
		newList.append(oldList.at(SNIFFLING_TOTAL) / oldList.at(SNIFFLING_COUNT));
		//qDebug() << "Total : " << oldList.at(SNIFFLING_TOTAL);

		m_Stat3.insert(oldList.at(SNIFFLING_COUNT), newList);
	}
	QMapIterator<int, QList<int>> iterator4(m_Stat3);
	iterator4.toBack();
	while (iterator4.hasPrevious()) {
		iterator4.previous();
		//qDebug() << "[StatSniffling] Win : " << iterator4.key()
		//	<< ", Odd : " << iterator4.value().at(SNIFFLING_COUNT)
		//	<< ", Average : " << iterator4.value().at(SNIFFLING_TOTAL);

	}
}

QList<int> StatSniffling::GetList(QList<int> baseList)
{
	int amount = 6;

	QMapIterator<int, QList<int>> iterator4(m_Stat3);
	iterator4.toBack();
	while (iterator4.hasPrevious()) {
		iterator4.previous();
		//qDebug() << "[StatSniffling] Win : " << iterator4.key()
		//	<< ", Odd : " << iterator4.value().at(SNIFFLING_COUNT)
		//	<< ", Average : " << iterator4.value().at(SNIFFLING_TOTAL);
	
		int countOdd = 0;
		// 전체 항목의 홀수 개수 체크
		for (QList<int>::const_iterator iter = baseList.constBegin(); iter != baseList.constEnd(); ++iter) {
			if (*iter % 2) {
				countOdd++;
			}
		}
		int countEvent = baseList.count() - countOdd;
		//qDebug() << "[StatSniffling] countOdd : " << countOdd << ", countEvent : " << countEvent;


		int avgOdd = iterator4.value().at(SNIFFLING_COUNT) * 100 / amount;
		int avgEven = 100 - avgOdd;
		//qDebug() << "[StatSniffling] avgOdd : " << avgOdd << ", avgEven : " << avgEven;

		// 구할 홀수 개수와 전체 홀수 개수를 비교하여 제일 작은 값으로 설정
		countOdd = qMin(countOdd, (baseList.count() - 5) * avgOdd / 100);
		countEvent = qMin(countEvent, (baseList.count() - 5) * avgEven / 100);
		//qDebug() << "[StatSniffling] countOdd : " << countOdd << ", countEvent : " << countEvent;
		for (QList<int>::const_iterator iter = baseList.constBegin(); iter != baseList.constEnd(); ++iter) {
	
			if (countOdd <= 0 && countEvent <= 0) break;
	
			if (*iter % 2) {
				m_Ret.append(*iter);
				countOdd--;
			}
			else {
				m_Ret.append(*iter);
				countEvent--;
			}
		}
	
		break;    // only one time...
	}
	
	return m_Ret;
}

QList<int> StatSniffling::GetListRandom(QList<int> baseList)
{
	//SettingData settings;
	//int limitCount = 10000;

	//QMapIterator<int, QList<int>> iterator4(m_Stat3);
	//iterator4.toBack();
	//while (iterator4.hasPrevious()) {
	//	iterator4.previous();
	//	qDebug() << "[StatSniffling] Win : " << iterator4.key()
	//		<< ", Odd : " << iterator4.value().at(SNIFFLING_COUNT)
	//		<< ", Average : " << iterator4.value().at(SNIFFLING_TOTAL);

	//	int count = 0;
	//	// 전체 항목의 홀수 개수 체크
	//	for (QList<int>::const_iterator iter = baseList.constBegin(); iter != baseList.constEnd(); ++iter) {
	//		if (*iter % 2) {
	//			count++;
	//		}
	//	}
	//	// 구할 홀수 개수와 전체 홀수 개수를 비교하여 제일 작은 값으로 설정
	//	count = qMin(count, iterator4.value().at(SNIFFLING_COUNT) * ARRAY_SIZE_SNIFFLING_TIME);
	//	while (count > 0 && limitCount > 0) {
	//		limitCount--;

	//		int random = settings.RandInt(0, baseList.count() - 1);

	//		if (baseList.at(random) % 2) {
	//			if (!m_Ret.contains(baseList.at(random))) {
	//				m_Ret.append(baseList.at(random));
	//				count--;
	//			}
	//		}
	//		else {
	//			if (!m_Ret.contains(baseList.at(random))) {
	//				m_Ret.append(baseList.at(random));
	//			}
	//		}
	//	}
	//	if (count > 0) {
	//		m_Ret.clear();
	//	}

	//	break;	// only one time...
	//}

	return m_Ret;
}


//
//QList<int> StatSniffling::GetList_Old(QList<int> baseList)
//{
//	QMapIterator<int, QList<int>> iterator4(m_Stat3);
//	iterator4.toBack();
//	while (iterator4.hasPrevious()) {
//		iterator4.previous();
//		qDebug() << "[StatSniffling] Win : " << iterator4.key()
//			<< ", Odd : " << iterator4.value().at(SNIFFLING_COUNT)
//			<< ", Average : " << iterator4.value().at(SNIFFLING_TOTAL);
//
//		int count = 0;
//		// 전체 항목의 홀수 개수 체크
//		for (QList<int>::const_iterator iter = baseList.constBegin(); iter != baseList.constEnd(); ++iter) {
//			if (*iter % 2) {
//				count++;
//			}
//		}
//		// 구할 홀수 개수와 전체 홀수 개수를 비교하여 제일 작은 값으로 설정
//		count = qMin(count, iterator4.value().at(SNIFFLING_COUNT) * ARRAY_SIZE_SNIFFLING_TIME);
//		for (QList<int>::const_iterator iter = baseList.constBegin(); iter != baseList.constEnd(); ++iter) {
//
//			if (count <= 0) break;
//
//			if (*iter % 2) {
//				m_Ret.append(*iter);
//				count--;
//			}
//			else {
//				m_Ret.append(*iter);
//			}
//		}
//
//		break;    // only one time...
//	}
//
//	return m_Ret;
//}
//
//QList<int> StatSniffling::GetListRandom_Old(QList<int> baseList)
//{
//	SettingData settings;
//	int limitCount = 10000;
//
//	QMapIterator<int, QList<int>> iterator4(m_Stat3);
//	iterator4.toBack();
//	while (iterator4.hasPrevious()) {
//		iterator4.previous();
//		qDebug() << "[StatSniffling] Win : " << iterator4.key()
//			<< ", Odd : " << iterator4.value().at(SNIFFLING_COUNT)
//			<< ", Average : " << iterator4.value().at(SNIFFLING_TOTAL);
//
//		int count = 0;
//		// 전체 항목의 홀수 개수 체크
//		for (QList<int>::const_iterator iter = baseList.constBegin(); iter != baseList.constEnd(); ++iter) {
//			if (*iter % 2) {
//				count++;
//			}
//		}
//		// 구할 홀수 개수와 전체 홀수 개수를 비교하여 제일 작은 값으로 설정
//		count = qMin(count, iterator4.value().at(SNIFFLING_COUNT) * ARRAY_SIZE_SNIFFLING_TIME);
//		while (count > 0 && limitCount > 0) {
//			limitCount--;
//
//			int random = settings.RandInt(0, baseList.count() - 1);
//
//			if (baseList.at(random) % 2) {
//				if (!m_Ret.contains(baseList.at(random))) {
//					m_Ret.append(baseList.at(random));
//					count--;
//				}
//			}
//			else {
//				if (!m_Ret.contains(baseList.at(random))) {
//					m_Ret.append(baseList.at(random));
//				}
//			}
//		}
//		if (count > 0) {
//			m_Ret.clear();
//		}
//
//		break;	// only one time...
//	}
//
//	return m_Ret;
//}
