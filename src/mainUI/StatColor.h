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

	void Generate(QMap<int, QList<int>> srcData, bool bBonus = true, int start = 1, int end = 1);
	//void Generate_old(QMap<int, QList<int>> srcData, bool bBonus = true, int start = 1, int end = 1);
	QList<int> GetList(QList<int>);



private slots:


private:


	///////////////////////////////
	// PRIVATE MEMBER VARIABLES
	///////////////////////////////

	// StatColor
	//QMap<int, QMap<int, int>>		m_Stat1;		// 색상별 (번호대역)
	//QMap<int, int>					m_Stat2;		// 색상별 (합계)

	QMap<int, int>					m_Stat3;		// 번호 대역순, 당첨 회수
	QMap<int, int>					m_Stat4;		// 당첨 회수순, 번호 대역

	QList<int>						m_Ret;			// 반환 데이타

};

#endif // STAT_COLOR_H
