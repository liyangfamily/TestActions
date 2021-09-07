#pragma once

#include <QMainWindow>

namespace Utils
{
	class AppMainWindow : public QMainWindow
	{
		Q_OBJECT

	public:
		AppMainWindow();

	public slots:
		void raiseWindow();

	signals:
		void deviceChange();

#ifdef Q_OS_WIN
	protected:
#if QT_VERSION < 0x050000
		virtual bool winEvent(MSG *message, long *result)override;
#else  
		virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result)override;
#endif //QT_VERSION < 0x050000
        bool event(QEvent *event) override;
#endif //Q_OS_WIN

    private:
		const int m_deviceEventId;
	};
} // Utils
