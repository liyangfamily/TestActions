#include "mcmonitor.h"
#include "ui_mcmonitor.h"
#include <QFile>
#include <Core/icore.h>
#include <LBL_Core/LBLUIHelper>
#include <QStatusBar>
MCMonitorTemperatureTable::MCMonitorTemperatureTable()
{
}


MCMonitorTemperatureTable::~MCMonitorTemperatureTable()
{
}

bool MCMonitorTemperatureTable::loadTxtFile(QString filePath)
{
	//打开文件
	QFile paramFile(filePath);
	if (!paramFile.open(QIODevice::ReadOnly))
	{
        Core::ICore::statusBar()->showMessage(QApplication::tr("Unable to open the ADC temperature acquisition curve value table."), 1500);
		return false;
	}
	//读取文件
	if (0 == paramFile.size())
	{
        Core::ICore::statusBar()->showMessage(QApplication::tr("Unable to open the ADC temperature acquisition curve value table."), 1500);
		return false;
	}
	m_elementList.clear();

	while(!paramFile.atEnd())
	{
		QByteArray strRow = paramFile.readLine();
		if ('[' == strRow.at(0))
		{
			STableElement element;
			if (parsingTxtDataByRow(strRow, element))
			{
				m_elementList.push_back(element);
			}
		}
	}
	paramFile.close();

	//排序
	qSort(m_elementList.begin(),m_elementList.end(),
		[](STableElement p1, STableElement p2)
	{
		return p1.startValue < p2.startValue;
	}
	);
	return true;
}

int MCMonitorTemperatureTable::getTemperature(int ADValue)
{
	if (m_elementList.empty())
	{
		return -1;
	}
	ADValue = ADValue << 4;
	for (auto i : m_elementList)
	{
		if (i.IsInRange(ADValue))
		{
			return i.useValue;
		}
	}
	return -1;
}

bool MCMonitorTemperatureTable::parsingTxtDataByRow(QByteArray data, STableElement& element)
{
	//[0000..0120]:122;
	int iPosLeft = 0;
	int iPosRight = 0;
	if (!data.startsWith('[') && !data.endsWith(';'))
	{
		return false;
	}
	//..左边的数字
	iPosLeft = data.indexOf("[", 0) + 1;
	iPosRight = data.indexOf("..", 0) - 1;
	QByteArray temp = data.mid(iPosLeft, iPosRight - iPosLeft + 1);
	element.startValue = temp.toInt();
	//..右边的数字
	iPosLeft = data.indexOf("..", 0) + 2;
	iPosRight = data.indexOf("]", 0) - 1;
	temp = data.mid(iPosLeft, iPosRight - iPosLeft + 1);
	element.endValue = temp.toInt();
	//:后面的数字
	iPosLeft = data.indexOf(":", 0) + 1;
	iPosRight = data.indexOf(";", 0) - 1;
	temp = data.mid(iPosLeft, iPosRight - iPosLeft + 1);
	element.useValue = temp.toInt();

	return true;
}

bool STableElement::IsLessThan(int value)
{
	return this->startValue > value;
}

bool STableElement::IsMoreThan(int value)
{
	return this->endValue < value;
}

bool STableElement::IsInRange(int value)
{
	if (!IsLessThan(value) && !IsMoreThan(value))
	{
		return true;
	}
	return false;
}

MCMonitor::MCMonitor(QWidget *parent)
    : QDialog(parent)
{
	ui = new Ui::MCMonitor();
	ui->setupUi(this);
	this->setMouseTracking(true);
	initRCMonitorInfoTable();
	m_tTable.loadTxtFile(LBLUIHelper::appParamDataLocation() + "/" + LBLUIHelper::appMonitorTemperatureTableFileName());
}

MCMonitor::~MCMonitor()
{
	delete ui;
}

bool MCMonitor::event(QEvent * e)
{
	return QWidget::event(e);
}
void MCMonitor::initRCMonitorInfoTable()
{
	ui->tableWidget->setMouseTracking(true);
	ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

	QStringList header;
	header << tr("PortIndex") << tr("ModuleIndex") << tr("Voltage") << tr("Tempature");
	ui->tableWidget->setColumnCount(header.size()); //设置列数
	ui->tableWidget->setHorizontalHeaderLabels(header);
	ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	ui->tableWidget->horizontalHeader()->setFixedHeight(23); //设置表头的高度
	ui->tableWidget->horizontalHeader()->setDefaultSectionSize(150);
	ui->tableWidget->verticalHeader()->setVisible(false);
}
void MCMonitor::processTabelData(QList<LBL::RC::SRCMonitorInfo> rcMonitorInfoList)
{
	ui->tableWidget->clearContents();
	ui->tableWidget->setRowCount(rcMonitorInfoList.size());//总行数
	for (int i = 0; i < rcMonitorInfoList.size(); ++i) {

		ui->tableWidget->setRowHeight(i, 40);

		const LBL::RC::SRCMonitorInfo& tempInfo = rcMonitorInfoList.at(i);

		ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(tempInfo.port + 1)));
		ui->tableWidget->item(i, 0)->setTextAlignment(Qt::AlignCenter);

		ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(tempInfo.moduleCardIndex + 1)));
		ui->tableWidget->item(i, 1)->setTextAlignment(Qt::AlignCenter);

		ui->tableWidget->setItem(i, 2, new QTableWidgetItem(QString("%1%2")\
			.arg(QString::number(tempInfo.monitorStuct.GetVoltage(), 'f', 2))\
			.arg("V")));
		ui->tableWidget->item(i, 2)->setTextAlignment(Qt::AlignCenter);

		int tempature = m_tTable.getTemperature(tempInfo.monitorStuct.GetTempature());
		ui->tableWidget->setItem(i, 3, new QTableWidgetItem(QString("%1%2")\
			.arg(tempature)\
            .arg(tr("℃"))));
		ui->tableWidget->item(i, 3)->setTextAlignment(Qt::AlignCenter);
	}
}

void MCMonitor::on_pushButton_clicked()
{
	ui->pushButton->setEnabled(false);
	QList<LBL::RC::SRCMonitorInfo> tempMonitorList = LAPI::ReadRCMonitorInfo(0xFF, true);
	processTabelData(tempMonitorList);
	ui->pushButton->setEnabled(true);
}
