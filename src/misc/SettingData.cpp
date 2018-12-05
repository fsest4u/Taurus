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

#include "SettingData.h"



SettingData::SettingData()
	: QSettings(QStandardPaths::writableLocation(QStandardPaths::TempLocation) + "/aquarius/aquarius.ini", QSettings::IniFormat)
{
}


SettingData::~SettingData()
{
}
