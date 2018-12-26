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
#ifndef STAT_COLOR_H
#define STAT_COLOR_H

#include <QtCore/QObject>


class StatColor : public QObject
{
	Q_OBJECT

public:


	/**
	* Constructor.
	*/
	StatColor();
	~StatColor();

	void Generate(QMap<int, QList<int>> srcData);



private slots:


private:


	///////////////////////////////
	// PRIVATE MEMBER VARIABLES
	///////////////////////////////

	// StatColor
	QMap<int, QHash<int, int>>		m_Stat1;		// 색상별 (번호대역)
	QHash<int, int>					m_Stat2;		// 색상별 (합계)
};

#endif // MGR_LOTTO_H
