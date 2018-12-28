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
#ifndef STAT_CONTINUE_H
#define STAT_CONTINUE_H

#include <QtCore/QObject>


class StatContinue : public QObject
{
	Q_OBJECT

public:


	/**
	* Constructor.
	*/
	StatContinue();
	~StatContinue();

	void Generate(QMap<int, QList<int>> srcData, bool bBonus = false, int start = 1, int end = 1);



private slots:


private:


	///////////////////////////////
	// PRIVATE MEMBER VARIABLES
	///////////////////////////////

	// StatContinue
	QMap<int, QList<int>>			m_Stat1;		// 연속번호

};

#endif // STAT_CONTINUE_H
