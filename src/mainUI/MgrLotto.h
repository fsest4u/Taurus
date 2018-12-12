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

	void SetData(int start, QList<QStringList> data);
	void ExportData();



private slots:


private:



	///////////////////////////////
	// PRIVATE MEMBER VARIABLES
	///////////////////////////////
	int					m_StratRow;
	QList<QStringList>	m_LottoData;


	ProgressWidget* m_ProgressWidget;

};

#endif // MGR_LOTTO_H
