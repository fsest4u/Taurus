/************************************************************************
**
**  Copyright (C) 2018  Daniel Lee <fsest4u@gmail.com>
**
**  This file is part of Taurus.
**
**  Taurus is analysis tool for lotto.
**
*************************************************************************/

#include <QtDebug>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QApplication>

#include "misc/ProgressWidget.h"
#include "misc/SettingData.h"
#include "MgrLotto.h"
#include "StatColor.h"
#include "StatContinue.h"
#include "StatNumber.h"
#include "StatPeriod.h"
#include "StatSection.h"
#include "StatSniffling.h"
//#include "taurus_constants.h"


MgrLotto::MgrLotto() :
	 m_ProgressWidget(NULL)
{

	m_ProgressWidget = new ProgressWidget();
}

MgrLotto::~MgrLotto()
{

	if (m_ProgressWidget) {
		delete m_ProgressWidget;
		m_ProgressWidget = NULL;
	}
}

void MgrLotto::SetPreference(bool bBonus, int start, int end, int lastweek)
{
	//qDebug() << "SetPreference() bonus : " << bBonus << 
	//	", start : " << start << 
	//	", end : " << end << 
	//	", lastweek : " << lastweek;
	m_bBonus = bBonus;
	m_StartTurn = start;
	m_EndTurn = end;
	m_LastWeek = lastweek;
}

bool MgrLotto::GenerateInfo(QList<bool> condition, QMap<int, QList<int>> srcData)
{
	QApplication::setOverrideCursor(Qt::WaitCursor);
	m_ProgressWidget->InitProgress("Analyze Data", CON_NUMBER, CON_COUTINUE, CON_NUMBER, CON_COUTINUE);

	m_ProgressWidget->SetValue(CON_NUMBER, CON_COUTINUE, QString("number"));
	// 순차적으로 설정
	if (condition.at(CON_NUMBER)) {
		StatNumber number;
		number.Generate(srcData, m_bBonus, m_StartTurn, m_EndTurn);
		m_BaseList = number.GetList();
		// for debug
		qDebug() << "[CON_NUMBER] count : " << m_BaseList.count();
		if (m_BaseList.count() <= 0) {
			m_ProgressWidget->Accept();
			QMessageBox::warning(this
				, tr(QCoreApplication::applicationName().toStdString().c_str())
				, tr("Please, Retry to analyze. (Not enough data, CON_NUMBER)"));
			QApplication::restoreOverrideCursor();
			return false;
		}
		for (QList<int>::const_iterator iter = m_BaseList.cbegin(); iter != m_BaseList.constEnd(); ++iter) {
			//qDebug() << "[CON_NUMBER] " << *iter;
		}
	}
	// 순차적으로 설정
	if (condition.at(CON_COLOR)) {
		m_ProgressWidget->SetValue(CON_COLOR, CON_COUTINUE, QString("color"));

		StatColor color;
		color.Generate(srcData, true, m_StartTurn, m_EndTurn);
		m_BaseList = color.GetList(m_BaseList);
		// for debug
		qDebug() << "[CON_COLOR] count : " << m_BaseList.count();
		if (m_BaseList.count() <= 0) {
			m_ProgressWidget->Accept();
			QMessageBox::warning(this
				, tr(QCoreApplication::applicationName().toStdString().c_str())
				, tr("Please, Retry to analyze. (Not enough data, CON_COLOR)"));
			QApplication::restoreOverrideCursor();
			return false;
		}
		for (QList<int>::const_iterator iter = m_BaseList.cbegin(); iter != m_BaseList.constEnd(); ++iter) {
			//qDebug() << "[CON_COLOR] " << *iter;
		}
	}
	// 순차적으로 설정
	if (condition.at(CON_SECTION)) {
		m_ProgressWidget->SetValue(CON_SECTION, CON_COUTINUE, QString("section"));

		StatSection section;
		section.Generate(srcData, true, m_LastWeek);
		m_BaseList = section.GetList(m_BaseList);
		// for debug
		qDebug() << "[CON_SECTION] count : " << m_BaseList.count();
		if (m_BaseList.count() <= 0) {
			m_ProgressWidget->Accept();
			QMessageBox::warning(this
				, tr(QCoreApplication::applicationName().toStdString().c_str())
				, tr("Please, Retry to analyze. (Not enough data, CON_SECTION)"));
			QApplication::restoreOverrideCursor();
			return false;
		}
		for (QList<int>::const_iterator iter = m_BaseList.cbegin(); iter != m_BaseList.constEnd(); ++iter) {
			//qDebug() << "[CON_SECTION] " << *iter;
		}
	}
	// 순차적으로 설정
	if (condition.at(CON_SNIFFLING)) {
		m_ProgressWidget->SetValue(CON_PERIOD, CON_COUTINUE, QString("period"));

		StatSniffling sniffling;
		sniffling.Generate(srcData, false, m_StartTurn, m_EndTurn);
		m_BaseList = sniffling.GetList(m_BaseList);
		// for debug
		qDebug() << "[CON_SNIFFLING] count : " << m_BaseList.count();
		if (m_BaseList.count() <= 0) {
			m_ProgressWidget->Accept();
			QMessageBox::warning(this
				, tr(QCoreApplication::applicationName().toStdString().c_str())
				, tr("Please, Retry to analyze. (Not enough data, CON_SNIFFLING)"));
			QApplication::restoreOverrideCursor();
			return false;
		}
		for (QList<int>::const_iterator iter = m_BaseList.cbegin(); iter != m_BaseList.constEnd(); ++iter) {
			//qDebug() << "[CON_SNIFFLING] " << *iter;
		}
	}
	// 랜덤하게 설정
	if (condition.at(CON_PERIOD)) {
		m_ProgressWidget->SetValue(CON_SNIFFLING, CON_COUTINUE, QString("sniffling"));

		StatPeriod period;
		period.Generate(srcData, true, m_LastWeek);
		m_PeriodList = period.GetListRandom();
		// for debug
		qDebug() << "[CON_PERIOD] count " << m_PeriodList.count();
		if (m_PeriodList.count() <= 0) {
			m_ProgressWidget->Accept();
			QMessageBox::warning(this
				, tr(QCoreApplication::applicationName().toStdString().c_str())
				, tr("Please, Retry to analyze. (Not enough data, CON_PERIOD)"));
			QApplication::restoreOverrideCursor();
			return false;
		}
		for (QList<int>::const_iterator iter = m_PeriodList.cbegin(); iter != m_PeriodList.constEnd(); ++iter) {
			//qDebug() << "=== CON_PERIOD " << *iter;
		}
	}
	// todo
	//if (condition.at(CON_COUTINUE)) {

	//	StatContinue conti;
	//	conti.Generate(srcData, false, m_StartTurn, m_EndTurn);
	//	conti.GetList();
	//}
	m_ProgressWidget->Accept();

	QApplication::restoreOverrideCursor();
	return true;
}


QList<int> MgrLotto::ExportData()
{
	//qDebug() << "ExportData()";

	//QList<int> tempList = m_BaseList + m_PeriodList;
	QList<int> tempList;
	for (QList<int>::const_iterator iter = m_BaseList.cbegin(); iter != m_BaseList.constEnd(); ++iter) {
		if (!tempList.contains(*iter)) {
			tempList.append(*iter);
		}
	}
	for (QList<int>::const_iterator iter = m_PeriodList.cbegin(); iter != m_PeriodList.constEnd(); ++iter) {
		if (!tempList.contains(*iter)) {
			tempList.append(*iter);
		}
	}
	// for debug
	qDebug() << "[TEMP_LIST] count : " << tempList.count();
	for (QList<int>::const_iterator iter = tempList.cbegin(); iter != tempList.constEnd(); ++iter) {
		//qDebug() << "[TEMP_LIST] " << *iter;
	}

	m_LottoList.clear();
	SettingData settings;
	while (m_LottoList.count() < 6) {

		// 랜덤하게 설정
		int random = settings.RandInt(0, tempList.count() - 1);
		//qDebug() << "random " << random;
		if (!m_LottoList.contains(tempList[random])) {
			//qDebug() << "lotto number " << tempList[random];
			m_LottoList.append(tempList[random]);
		}
	}
	qSort(m_LottoList);

	return m_LottoList;
}



