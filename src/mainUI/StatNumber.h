﻿/************************************************************************
**
**  Copyright (C) 2018  Daniel Lee <fsest4u@gmail.com>
**
**  This file is part of Taurus.
**
**  Taurus is analysis tool for lotto.
**
*************************************************************************/

#pragma once
#ifndef STAT_NUMBER_H
#define STAT_NUMBER_H

#include <QtCore/QObject>


class StatNumber : public QObject
{
	Q_OBJECT

public:


	/**
	* Constructor.
	*/
	StatNumber();
	~StatNumber();

	void Generate(QMap<int, QList<int>> srcData, bool bBonus = true, int start = 1, int end = 1);
	QList<int> GetList() { return m_Ret; }



private slots:


private:


	///////////////////////////////
	// PRIVATE MEMBER VARIABLES
	///////////////////////////////

	// StatNumber
	QMap<int, int>					m_Stat1;		// 번호순, 당첨 회수
	QMap<int, int>					m_Stat2;		// 당첨 회수순, 번호

	QList<int>						m_Ret;			// 반환 데이타
};

#endif // STAT_NUMBER_H
