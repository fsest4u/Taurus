/************************************************************************
**
**  Copyright (C) 2018  Daniel Lee <fsest4u@gmail.com>
**
**  This file is part of Taurus.
**
**  Taurus is analysis tool for lotto.
**
*************************************************************************/

#pragma once
#ifndef STAT_SNIFFLING_H
#define STAT_SNIFFLING_H

#include <QtCore/QObject>


class StatSniffling : public QObject
{
	Q_OBJECT

public:


	/**
	* Constructor.
	*/
	StatSniffling();
	~StatSniffling();

	void Generate(QMap<int, QList<int>> srcData, bool bBonus = false, int start = 1, int end = 1);
	QList<int> GetList(QList<int> baseList);
	QList<int> GetListRandom(QList<int> baseList);

	//void Generate_Old(QMap<int, QList<int>> srcData, bool bBonus = false, int start = 1, int end = 1);
	//QList<int> GetList_Old(QList<int> baseList);
	//QList<int> GetListRandom_Old(QList<int> baseList);


private slots:


private:


	///////////////////////////////
	// PRIVATE MEMBER VARIABLES
	///////////////////////////////

	// StatSniffling
	QMap<int, QMap<bool, int>>		m_Stat1;		// 회차순, 홀짝, 숫자
	QMap<int, QList<int>>			m_Stat2;		// 홀수 개수순, 당첨 회수, 번호합
	QMap<int, QList<int>>			m_Stat3;		// 당첨 회수순, 홀수 개수, 번호합의 평균

	QList<int>						m_Ret;			// 반환 데이타

};

#endif // STAT_SNIFFLING_H
