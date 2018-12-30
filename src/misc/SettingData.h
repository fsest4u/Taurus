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
#ifndef SETTINGDATA_H
#define SETTINGDATA_H

#include <QtCore/QSettings>

class SettingData : public QSettings
{
public:
	SettingData();
	virtual ~SettingData();

	int RandInt(int low, int high);

private:


};

#endif // SETTINGDATA_H
