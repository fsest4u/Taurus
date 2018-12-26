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

	void Generate(QMap<int, QList<int>> srcData);



private slots:


private:


	///////////////////////////////
	// PRIVATE MEMBER VARIABLES
	///////////////////////////////

	// StatSniffling
	QMap<int, QMap<bool, int>>		m_StatSniffling;	// 홀짝 

};

#endif // STAT_SNIFFLING_H
