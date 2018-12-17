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

#include "misc/ProgressWidget.h"
#include "MgrCSV.h"
#include "MgrLotto.h"
//#include "taurus_constants.h"


MgrLotto::MgrLotto() :
	 m_ProgressWidget(NULL)
{
	m_CompactData.clear();

	m_ProgressWidget = new ProgressWidget();
}

MgrLotto::~MgrLotto()
{

	if (m_ProgressWidget) {
		delete m_ProgressWidget;
		m_ProgressWidget = NULL;
	}
}

void MgrLotto::SetSourceData(QList<QStringList> srcData)
{
	m_CompactData.clear();
	QByteArray byteArray;
	byteArray.clear();

	for (int i = m_StartRow; i < srcData.size(); i++) {
		byteArray.clear();
		//byteArray.append(srcData.at(i).value(MgrCSV::COL_1ST_NUM));
		//byteArray.append(srcData.at(i).value(MgrCSV::COL_2ND_NUM));
		//byteArray.append(srcData.at(i).value(MgrCSV::COL_3RD_NUM));
		//byteArray.append(srcData.at(i).value(MgrCSV::COL_4TH_NUM));
		//byteArray.append(srcData.at(i).value(MgrCSV::COL_5TH_NUM));
		//byteArray.append(srcData.at(i).value(MgrCSV::COL_6TH_NUM));
		//byteArray.append(srcData.at(i).value(MgrCSV::COL_BONUS_NUM));
		byteArray.setNum(srcData.at(i).value(MgrCSV::COL_1ST_NUM).toInt());
		byteArray.setNum(srcData.at(i).value(MgrCSV::COL_2ND_NUM).toInt());

		m_CompactData.insert(srcData.at(i).value(MgrCSV::COL_TURN), byteArray);
	}

}

void MgrLotto::SetStatNumber(bool bNumber)
{
	qDebug() << "m_bBonus : " << m_bBonus;
	if (!bNumber) return;
	qDebug() << "SetStatNumber()";

	QMapIterator<QString, QByteArray> i(m_CompactData);
	while (i.hasNext()) {
		i.next();
		// for debug
		QByteArray byteArray;
		byteArray.clear();
		byteArray = i.value();
		QString key = QString("%1").arg(i.key());
		qDebug() << "key : " << key;

		QByteArray::iterator i;
		for (i = byteArray.begin(); i != byteArray.end(); ++i)
			qDebug() << *i;


		//for (QByteArray::const_iterator iter = byteArray.cbegin();
		//	iter != byteArray.constEnd(); ++iter) {

		//}
	}


}
void MgrLotto::SetStatColor(bool bColor)
{
	if (!bColor) return;
	qDebug() << "SetStatColor()";

}
void MgrLotto::SetStatSection(bool bSection)
{
	if (!bSection) return;
	qDebug() << "SetStatSection()";

}
void MgrLotto::SetStatPeriod(bool bPeriod)
{
	if (!bPeriod) return;
	qDebug() << "SetStatPeriod()";

}
void MgrLotto::SetStatSniffling(bool bSniffling)
{
	if (!bSniffling) return;
	qDebug() << "SetStatSniffling()";

}
void MgrLotto::SetStatContinue(bool bContinue)
{
	if (!bContinue) return;
	qDebug() << "SetStatContinue()";

}


void MgrLotto::ExportData()
{
	qDebug() << "ExportData()";

}


