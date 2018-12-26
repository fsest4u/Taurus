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

#include "StatContinue.h"
#include "MgrLotto.h"
//#include "taurus_constants.h"


StatContinue::StatContinue()
{
}

StatContinue::~StatContinue()
{
}


void StatContinue::Generate(QMap<int, QList<int>> srcData)
{
	qDebug() << "StatContinue::Generate()";
	m_Stat1.clear();

	QMapIterator<int, QList<int>> iterator1(srcData);
	while (iterator1.hasNext()) {
		iterator1.next();
		QList<int> numData = iterator1.value();
		QList<int> tempData;
		tempData.clear();

		int previous = -1;

		for (QList<int>::const_iterator iter = numData.cbegin(); iter != numData.constEnd(); ++iter) {
			if (*iter == previous + 1) {
				tempData.insert(0, previous);
				tempData.insert(1, *iter);
				m_Stat1.insert(iterator1.key(), tempData);
			}
			previous = *iter;
		}
	}

	// for debug
	QMapIterator<int, QList<int>> iterator2(m_Stat1);
	while (iterator2.hasNext()) {
		iterator2.next();
		QList<int> val(iterator2.value());
		qDebug() << "[continue] iterator2.key : " << iterator2.key() << ", key : " << val.at(0) << ", value : " << val.at(1);
	}

}
