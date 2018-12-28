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
#ifndef MGR_LOTTO_H
#define MGR_LOTTO_H

#include <QtCore/QObject>

class ProgressWidget;

class MgrLotto : public QObject
{
	Q_OBJECT

public:

	enum Condition
	{
		CON_NUMBER = 0, 
		CON_COLOR,
		CON_SECTION,
		CON_PERIOD,
		CON_SNIFFLING,
		CON_COUTINUE,
		CON_MAX = 100
	};

	enum TURN_WEEK
	{
		TURN_WEEK_5 = 5,
		TURN_WEEK_10 = 10,
		TURN_WEEK_15 = 15,
		TURN_WEEK_MAX = 100
	};

	enum SectionUnit10
	{
		UNIT_10_1 = 1,
		UNIT_10_10 = 10,
		UNIT_10_20 = 20,
		UNIT_10_30 = 30,
		UNIT_10_40 = 40,
		UNIT_10_MAX = 100
	};


	/**
	* Constructor.
	*/
	MgrLotto();
	~MgrLotto();

	void SetPreference(bool bBonus = true, int start = 1, int end = 5, int lastweek = TURN_WEEK_5);
	void GenerateInfo(QList<bool> condition, QMap<int, QList<int>> srcData);

	void ExportData();



private slots:


private:



	///////////////////////////////
	// PRIVATE MEMBER VARIABLES
	///////////////////////////////

	bool				m_bBonus;
	int					m_StartTurn;
	int					m_EndTurn;
	int					m_LastWeek;

	ProgressWidget*		m_ProgressWidget;

};

#endif // MGR_LOTTO_H
