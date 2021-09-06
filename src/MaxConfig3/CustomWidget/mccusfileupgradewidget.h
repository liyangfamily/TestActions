#pragma once

#include <LAPIControl>

#include <QWidget>
#include <QStateMachine>

namespace Internal
{
	namespace CustomWidget
	{
		class MCCusFileUpgradeWidgetPrivate;
		 
		class MCCusFileUpgradeWidget : public QWidget
		{
			Q_OBJECT

		public:
			MCCusFileUpgradeWidget(LBLFileTransferPackage::EFileType type= LBLFileTransferPackage::EFileType::EFT_SelectFile, QWidget *parent = Q_NULLPTR);
			~MCCusFileUpgradeWidget();
			void setPortIndex(quint8 port);
			quint8 portIndex();
			void setModuleIndex(quint8 module);
			quint16 moduleIndex();
			bool startRefresh();
		private:
			void creatStateMechine(); 
			void creatPrepareUpgradeStates();
			void creatUpgradingStates();
			void creatUpgradingBackStates();

			void creatConnections();
			void creatPreparUpgradeTransitions();
			void creatUpgradingTransitions();
			void creatUpgradingBackTransitions();
		private:
			MCCusFileUpgradeWidgetPrivate *d;
			QList<QWidget*> extraWidgets;
			QStateMachine *m_upgradeStateMechine;
			QState *m_prepareUpgradeState;
			QState *m_UpgradingState;
			QState *m_UpgradingBackState;

		signals:
			void sig_PrepareUpgrade();
			void sig_Upgrading();
			void sig_UpgradingBack();

		private slots:
			void slot_btnUpgrade_clicked();
			void slot_btnUpgradeCancel_clicked();
			void onUpgradeFinished();
			void updateUpgardeProgressBar();
		};
	}
}