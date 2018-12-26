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
	enum SectionUnit5
	{
		UNIT_5_1_5 = 1,
		UNIT_5_6_10 = 6,
		UNIT_5_11_15 = 11,
		UNIT_5_16_20 = 16,
		UNIT_5_21_25 = 21,
		UNIT_5_26_30 = 26,
		UNIT_5_31_35 = 31,
		UNIT_5_36_40 = 36,
		UNIT_5_41_45 = 41,
		UNIT_5_MAX = 100,
	};


	/**
	* Constructor.
	*/
	MgrLotto();
	~MgrLotto();

	void SetBonus(bool bBonus) { m_bBonus = bBonus; };
	void SetStartRow(int startRow) { m_StartRow = startRow; }
	void SetSourceData(QList<QStringList> srcData);

	void SetStatNumber(bool bNumbera);
	void SetStatColor(bool bColor);
	void SetStatSection(bool bSection);
	void SetStatPeriod(bool bPeriod);
	void SetStatSniffling(bool bSniffling);
	void SetStatContinue(bool bContinue);

	void ExportData();



private slots:


private:



	///////////////////////////////
	// PRIVATE MEMBER VARIABLES
	///////////////////////////////
	int								m_StartRow;

	QMap<int, QList<int>>			m_CompactData;
	// StatNumber
	QMap<int, int>					m_StatNumber;		// 번호순 (번호, 회수)
	QMap<int, int>					m_StatNumberWin;	// 당첨회수순 (회수, 번호)
	// StatColor
	QMap<int, QHash<int, int>>		m_StatColor;		// 색상별 (번호대역)
	QHash<int, int>					m_StatColorTot;		// 색상별 합계
	// StatSection
	QHash<int, int>					m_StatSec10;		// 구간별 10단위
	QHash<int, int>					m_StatSec5;			// 구간별 5단위
	// StatPeriod
	QHash<int, bool>				m_StatPeriod;		// 기간별 미출현 번호
	// StatSniffling
	QMap<int, QMap<bool, int>>		m_StatSniffling;	// 홀짝 
	// StatContinue
	QMap<int, QList<int>>			m_StatContinue;		// 연속번호


	bool				m_bBonus;
	bool				m_bNumber;
	bool				m_bColor;
	bool				m_bSection;
	bool				m_bPeriod;
	bool				m_bSniffling;
	bool				m_bContinue;

	ProgressWidget* m_ProgressWidget;

};

#endif // MGR_LOTTO_H
