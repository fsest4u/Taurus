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
	QList<int> GetList() { return m_Ret; }



private slots:


private:


	///////////////////////////////
	// PRIVATE MEMBER VARIABLES
	///////////////////////////////

	// StatContinue
	QMap<int, QList<int>>			m_Stat1;		// 회차, 연속번호 쌍
	QMap<int, int>					m_Stat2;		// 연속번호 쌍, 출현 회수
	QMap<int, int>					m_Stat3;		// 출현 회수, 연속번호 쌍

	QList<int>						m_Ret;			// 반환 데이타

};

#endif // STAT_CONTINUE_H
