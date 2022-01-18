#ifndef CURRENTGAIN_H
#define CURRENTGAIN_H

#include <QDialog>

namespace Ui {
class CurrentGain;
}

class CurrentGain : public QDialog
{
    Q_OBJECT

public:
    explicit CurrentGain(QWidget *parent = nullptr);
    ~CurrentGain();

private slots:
    void on_CurrentGainRSlider_valueChanged(int value);

    void on_CurrentGainGSlider_valueChanged(int value);

    void on_CurrentGainBSlider_valueChanged(int value);

    void on_SettingBtn_clicked();

private:
    void Showic();
    void LoadForm();
    void WriteCurrent(int Regnum,int ByteCount, int StartByte);
    QString getpercent(int value);
    int MaxValue = 0;
    void ShowScrool(bool type);
    void initMetroTrackBar(int Regnum, int ByteCount, int StartByte);
    void init5043MetroTrackBar(int ByteCount, int StartByte);
    void init5353MetroTrackBar(int ByteCount, int StartByte);
    void Write5353Current(int ByteCount, int StartByte);
    void Write5043Current(int ByteCount, int StartByte);




private:
    Ui::CurrentGain *ui;
};

#endif // CURRENTGAIN_H
