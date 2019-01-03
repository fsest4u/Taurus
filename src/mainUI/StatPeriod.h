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
#ifndef STAT_PERIOD_H
#define STAT_PERIOD_H

#include <QtCore/QObject>

#include "MgrLotto.h"

class StatPeriod : public QObject
{
	Q_OBJECT

public:


	/**
	* Constructor.
	*/
	StatPeriod();
	~StatPeriod();

	void Generate(QMap<int, QList<int>> srcData, bool bBonus = true, int lastweek = MgrLotto::TURN_WEEK_5);
	QList<int> GetList();
	QList<int> GetListRandom();


private slots:


private:


	///////////////////////////////
	// PRIVATE MEMBER VARIABLES
	///////////////////////////////

	// StatPeriod
	QMap<int, bool>					m_Stat1;		// 기간별 미출현 번호, 미출현 여부

	QList<int>						m_Ret;			// 반환 데이타

};

#endif // STAT_PERIOD_H
