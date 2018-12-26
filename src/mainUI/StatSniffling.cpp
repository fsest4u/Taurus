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

#include "StatSniffling.h"
#include "MgrLotto.h"
//#include "taurus_constants.h"


StatSniffling::StatSniffling()
{
}

StatSniffling::~StatSniffling()
{
}


void StatSniffling::Generate(QMap<int, QList<int>> srcData)
{
	qDebug() << "StatSniffling::Generate()";
	m_StatSniffling.clear();

	QMapIterator<int, QList<int>> iterator1(srcData);
	while (iterator1.hasNext()) {
		iterator1.next();
		QList<int> numData = iterator1.value();

		QMap<bool, int>  sniffling;
		sniffling.clear();
		for (QList<int>::const_iterator iter = numData.cbegin(); iter != numData.constEnd(); ++iter) {
			if (*iter % 2) {
				sniffling.insertMulti(true, *iter);// odd number
			}
			else {
				sniffling.insertMulti(false, *iter);// even number
			}
		}
		m_StatSniffling.insert(iterator1.key(), sniffling);
	}

	// for debug
	QMapIterator<int, QMap<bool, int>> iterator2(m_StatSniffling);
	while (iterator2.hasNext()) {
		iterator2.next();
		QMapIterator<bool, int> val(iterator2.value());
		while (val.hasNext()) {
			val.next();
			qDebug() << "[sniffling] iterator2.key : " << iterator2.key() << ", key : " << val.key() << ", value : " << val.value();
		}
	}

}
