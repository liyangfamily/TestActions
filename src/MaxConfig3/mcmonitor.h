#pragma once

#include <QDialog>
#include <LAPIControl>
namespace Ui { class MCMonitor; };

struct STableElement
{
	int startValue = 0;
	int endValue = 0;
	int useValue = 0;

	bool IsLessThan(int value);
	bool IsMoreThan(int value);
	bool IsInRange(int value);
};

class MCMonitorTemperatureTable
{
public:
	MCMonitorTemperatureTable();
	~MCMonitorTemperatureTable();

public:
	//加载温度对照表文件
	bool loadTxtFile(QString filePath);

	//传入AD值，返回实际温度
	int getTemperature(int ADValue);

private:
	bool parsingTxtDataByRow(QByteArray data, STableElement& element);



private:
	QList<STableElement> m_elementList;
};

class MCMonitor : public QDialog
{
	Q_OBJECT

public:
    MCMonitor(QWidget *parent = Q_NULLPTR);
	~MCMonitor();

private:
	Ui::MCMonitor *ui;
	MCMonitorTemperatureTable m_tTable;

protected:
	bool event(QEvent* e) override;

private:
	void initRCMonitorInfoTable();
	void processTabelData(QList<LBL::RC::SRCMonitorInfo> list);

private slots:
	void on_pushButton_clicked();
};
