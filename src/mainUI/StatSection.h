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
#ifndef STAT_SECTION_H
#define STAT_SECTION_H

#include <QtCore/QObject>

#include "MgrLotto.h"

class StatSection : public QObject
{
	Q_OBJECT

public:


	/**
	* Constructor.
	*/
	StatSection();
	~StatSection();

	void Generate(QMap<int, QList<int>> srcData, bool bBonus = true, int lastweek = MgrLotto::TURN_WEEK_5);
	//void Generate_old(QMap<int, QList<int>> srcData, bool bBonus = true, int lastweek = MgrLotto::TURN_WEEK_5);
	QList<int> GetList(QList<int> baseList);

private slots:


private:


	///////////////////////////////
	// PRIVATE MEMBER VARIABLES
	///////////////////////////////

	// StatSection
	//QMap<int, int>					m_Stat1;			// 구간별 10단위
	//QMap<int, int>					m_Stat2;			// 구간별 5단위

	QMap<int, int>					m_Stat3;			// 번호 대역, 당첨 회수
	QMap<int, int>					m_Stat4;			// 당첨 회수순, 번호 대역

	QList<int>						m_Ret;			// 반환 데이타

};

#endif // STAT_SECTION_H
