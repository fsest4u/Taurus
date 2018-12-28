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



private slots:


private:


	///////////////////////////////
	// PRIVATE MEMBER VARIABLES
	///////////////////////////////

	// StatSniffling
	QMap<int, QMap<bool, int>>		m_Stat1;	// 홀짝 

};

#endif // STAT_SNIFFLING_H
