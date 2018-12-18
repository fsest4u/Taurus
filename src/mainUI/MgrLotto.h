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
