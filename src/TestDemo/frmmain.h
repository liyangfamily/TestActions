#ifndef FRMMAIN_H
#define FRMMAIN_H

#include <QWidget>
#include "progressmanager/progressmanager.h"
#include "progressmanager/futureprogress.h"
#include "progressmanager/progressmanager_p.h"
#include "progressmanager/progressview.h"
#include <QFutureInterface.h>

namespace Ui {
class frmMain;
}
namespace Core {
	namespace Internal {
		class ProgressManagerPrivate;
	}
}
class frmMain : public QWidget
{
    Q_OBJECT

public:
    explicit frmMain(QWidget *parent = 0);
    ~frmMain();

private slots:
    void on_tabWidget_currentChanged(int index);
    void on_btnTest_clicked();

private:
	Ui::frmMain *ui;
	Core::Internal::ProgressManagerPrivate *m_progressManager = nullptr;
};

#endif // FRMMAIN_H
