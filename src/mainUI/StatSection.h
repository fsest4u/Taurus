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


class StatSection : public QObject
{
	Q_OBJECT

public:


	/**
	* Constructor.
	*/
	StatSection();
	~StatSection();

	void Generate(QMap<int, QList<int>> srcData);



private slots:


private:


	///////////////////////////////
	// PRIVATE MEMBER VARIABLES
	///////////////////////////////

	// StatSection
	QHash<int, int>					m_Stat1;			// 구간별 10단위
	QHash<int, int>					m_Stat2;			// 구간별 5단위

};

#endif // STAT_SECTION_H
