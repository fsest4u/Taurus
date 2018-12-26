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


class StatPeriod : public QObject
{
	Q_OBJECT

public:


	/**
	* Constructor.
	*/
	StatPeriod();
	~StatPeriod();

	void Generate(QMap<int, QList<int>> srcData);



private slots:


private:


	///////////////////////////////
	// PRIVATE MEMBER VARIABLES
	///////////////////////////////

	// StatPeriod
	QHash<int, bool>				m_Stat1;		// 기간별 미출현 번호

};

#endif // STAT_PERIOD_H
