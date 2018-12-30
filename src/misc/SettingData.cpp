/************************************************************************
**
**  Copyright (C) 2018  Daniel Lee <fsest4u@gmail.com>
**
**  This file is part of Taurus.
**
**  Taurus is analysis tool for lotto.
**
*************************************************************************/

#include <QtCore/QStandardPaths>
#include <QtCore/QTime>
#include <QtCore/QtGlobal>

#include "SettingData.h"



SettingData::SettingData()
	: QSettings(QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/taurus/taurus.ini", QSettings::IniFormat)
{
	// Create seed for the random
	// That is needed only once on application startup
	QTime time = QTime::currentTime();
	qsrand((uint)time.msec());

	//qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

}


SettingData::~SettingData()
{
}

int SettingData::RandInt(int low, int high)
{
	// Random number between low and high
	return qrand() % ((high + 1) - low) + low;
}

