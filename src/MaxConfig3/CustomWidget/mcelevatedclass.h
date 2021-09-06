#ifndef MCELEVATEDCLASS_H
#define MCELEVATEDCLASS_H
#include <QPushButton>
#include <QRadioButton>
#include <QFrame>
#include <QProgressBar>
#include <QStyle>

class QSSPropertyBtn : public QPushButton
{
    Q_OBJECT
    Q_PROPERTY(QSizePolicy::Policy vertSizePolicy READ verticalPolicy WRITE setVerticalPolicy)
    Q_PROPERTY(QSizePolicy::Policy horizSizePolicy READ horizontalPolicy WRITE setHorizontalPolicy)

    public:

    QSSPropertyBtn(QWidget* parent = 0)
     :QPushButton(parent){};
    QSSPropertyBtn(const QString& text, QWidget* parent = 0 )
        :QPushButton(text,parent){};
    QSSPropertyBtn(const QIcon& icon, const QString& text, QWidget* parent = 0 )
        :QPushButton(icon,text,parent){};

    protected: // Overloaded operations

    void setVerticalPolicy(QSizePolicy::Policy policy)
    {
        QSizePolicy mPolicy = sizePolicy();
        setSizePolicy(mPolicy.horizontalPolicy(), policy);
    };
    void setHorizontalPolicy(QSizePolicy::Policy policy)
    {
        QSizePolicy mPolicy = sizePolicy();
        setSizePolicy(policy, mPolicy.verticalPolicy());
    };
    QSizePolicy::Policy verticalPolicy() { return sizePolicy().verticalPolicy(); };
    QSizePolicy::Policy horizontalPolicy() { return sizePolicy().horizontalPolicy(); };

};

class NavigateBarFirstBtn : public QSSPropertyBtn
{
    Q_OBJECT
public:
    explicit NavigateBarFirstBtn(QWidget *parent = nullptr)
        :QSSPropertyBtn(parent){};
    explicit NavigateBarFirstBtn(const QString &text, QWidget *parent = nullptr)
        :QSSPropertyBtn(text,parent){};
    NavigateBarFirstBtn(const QIcon& icon, const QString &text, QWidget *parent = nullptr)
        :QSSPropertyBtn(icon,text,parent){};
};

class NavigateBarSecondBtn : public QSSPropertyBtn
{
    Q_OBJECT
public:
    explicit NavigateBarSecondBtn(QWidget *parent = nullptr)
        :QSSPropertyBtn(parent){};
    explicit NavigateBarSecondBtn(const QString &text, QWidget *parent = nullptr)
        :QSSPropertyBtn(text,parent){};
    NavigateBarSecondBtn(const QIcon& icon, const QString &text, QWidget *parent = nullptr)
        :QSSPropertyBtn(icon,text,parent){};
};

class BluePushButton : public QSSPropertyBtn
{
    Q_OBJECT
public:
    explicit BluePushButton(QWidget *parent = nullptr)
        :QSSPropertyBtn(parent){};
    explicit BluePushButton(const QString &text, QWidget *parent = nullptr)
        :QSSPropertyBtn(text,parent){};
    BluePushButton(const QIcon& icon, const QString &text, QWidget *parent = nullptr)
        :QSSPropertyBtn(icon,text,parent){};
};

class SwitchRadioButton : public QRadioButton
{
    Q_OBJECT
public:
    explicit SwitchRadioButton(QWidget *parent = nullptr)
        :QRadioButton(parent){};
    explicit SwitchRadioButton(const QString &text, QWidget *parent = nullptr)
        :QRadioButton(text,parent){};

    ~SwitchRadioButton(){};
};

class SCListItemFrame : public QFrame
{
    Q_OBJECT
public:
    explicit SCListItemFrame(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags())
        :QFrame(parent,f){}
    ~SCListItemFrame(){};
};

class HasErrorProgressBar : public QProgressBar
{
    Q_OBJECT
    Q_PROPERTY(bool hasError READ hasError WRITE setHasError)
public:
    explicit HasErrorProgressBar(QWidget *parent = nullptr)
        :QProgressBar(parent){};
    ~HasErrorProgressBar(){};

    void setHasError(bool b){
        m_hasErroe=b;
        this->style()->unpolish(this);
        this->style()->polish(this);
        this->update();
    }

    bool hasError(){
        return m_hasErroe;
    }
private:
    bool m_hasErroe=false;
};
#endif // MCELEVATEDCLASS_H
