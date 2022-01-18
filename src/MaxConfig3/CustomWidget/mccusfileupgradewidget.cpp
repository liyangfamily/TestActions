#include "mccusfileupgradewidget.h"
#include <QHBoxLayout>
#include <QProgressBar>
#include <QPushButton>
#include <QComboBox>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QSignalTransition>
#include <QFileDialog>
#include "app.h"

#ifdef Q_CC_MSVC
#pragma execution_character_set("utf-8")
#endif

namespace Internal
{
	namespace CustomWidget
	{

		class MCCusFileUpgradeWidgetPrivate :public QObject
		{
			Q_OBJECT
		public: 
			explicit MCCusFileUpgradeWidgetPrivate(MCCusFileUpgradeWidget *q);

			QHBoxLayout *m_mainHLayout;
			QComboBox *m_comboBox;
			QProgressBar *m_progressBar;
			QPushButton *m_btnUpgrade;
			QPushButton *m_btnCancel;
			QPushButton *m_btnBack;
			LBLFileTransferPackage::EFileType m_fileType;
			quint8 m_portIndex = 0xFF;
			quint16 m_moduleIndex = 0xFFFF; 
			QFutureWatcher<quint16> m_upgradeWatcher;
			MCCusFileUpgradeWidget *m_q;
		};

		MCCusFileUpgradeWidgetPrivate::MCCusFileUpgradeWidgetPrivate(MCCusFileUpgradeWidget *q) :
			m_mainHLayout(new QHBoxLayout), m_comboBox(new QComboBox), m_progressBar(new QProgressBar), 
			m_btnUpgrade(new QPushButton("Upgrade")), m_btnCancel(new QPushButton("Cancel")),m_btnBack(new QPushButton("Back")),
			m_q(q)
		{
			m_progressBar->setValue(0);
			m_progressBar->setFormat(tr("0%"));
			m_progressBar->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);  // 对齐方式
		}



		MCCusFileUpgradeWidget::MCCusFileUpgradeWidget(LBLFileTransferPackage::EFileType type, QWidget *parent)
			: QWidget(parent), d(new MCCusFileUpgradeWidgetPrivate(this))
		{
			d->m_fileType = type;
			setLayout(d->m_mainHLayout);
			d->m_mainHLayout->addWidget(d->m_comboBox, 1); 
			d->m_mainHLayout->addWidget(d->m_btnUpgrade);
			d->m_mainHLayout->addWidget(d->m_progressBar, 1);
			d->m_mainHLayout->addWidget(d->m_btnCancel);
			d->m_mainHLayout->addWidget(d->m_btnBack);
			d->m_mainHLayout->setContentsMargins(5, 2, 5, 2);
			d->m_mainHLayout->setSpacing(5);
			extraWidgets << d->m_comboBox << d->m_btnUpgrade
				<< d->m_progressBar << d->m_btnCancel << d->m_btnBack;
			foreach(QWidget *widget, extraWidgets) {
				QGraphicsOpacityEffect *effect = new QGraphicsOpacityEffect;
				effect->setOpacity(1.0);
				widget->setGraphicsEffect(effect);
			}
			creatStateMechine(); 
			creatConnections();
		}

		MCCusFileUpgradeWidget::~MCCusFileUpgradeWidget()
		{
			delete d;
		}

		void CustomWidget::MCCusFileUpgradeWidget::setPortIndex(quint8 port)
		{
			d->m_portIndex = port;
		}

		quint8 CustomWidget::MCCusFileUpgradeWidget::portIndex()
		{
			return d->m_portIndex;
		}

		void CustomWidget::MCCusFileUpgradeWidget::setModuleIndex(quint8 module)
		{
			d->m_moduleIndex = module;
		}

		quint16 CustomWidget::MCCusFileUpgradeWidget::moduleIndex()
		{
			return d->m_moduleIndex;
		}

		bool CustomWidget::MCCusFileUpgradeWidget::startRefresh()
		{
			if (LAPI::IsUpgrading() && LAPI::IsUpgradeSend()) {
				if (d->m_fileType == LBLFileTransferPackage::EFT_SelectFile) {
					QTimer::singleShot(500, [this]() {
						emit sig_Upgrading();
					});
					d->m_upgradeWatcher.blockSignals(false);
					d->m_upgradeWatcher.setFuture(LAPI::UpgradeFuture());
					return true;
				}
				else if (d->m_fileType == LBLFileTransferPackage::EFT_ReciverFPGA) {
					if (LAPI::UpgradingPortIndex() == d->m_portIndex&&LAPI::UpgradingModuleIndex() == d->m_moduleIndex) {
						QTimer::singleShot(50, [this]() {
							emit sig_Upgrading();
						});
						d->m_upgradeWatcher.blockSignals(false);
						d->m_upgradeWatcher.setFuture(LAPI::UpgradeFuture());
						return true;
					}
				}
			}
			return false;
		}

		void MCCusFileUpgradeWidget::creatStateMechine()
		{
			m_upgradeStateMechine = new QStateMachine(this);
			creatPrepareUpgradeStates();
			creatUpgradingStates();
			creatUpgradingBackStates();
			creatPreparUpgradeTransitions();
			creatUpgradingTransitions();
			creatUpgradingBackTransitions();
			m_upgradeStateMechine->setInitialState(m_prepareUpgradeState);
			m_upgradeStateMechine->start();
		}
		void MCCusFileUpgradeWidget::creatPrepareUpgradeStates()
		{
			m_prepareUpgradeState = new QState(m_upgradeStateMechine);

			if (d->m_fileType == LBLFileTransferPackage::EFT_SelectFile) {
				m_prepareUpgradeState->assignProperty(d->m_comboBox->graphicsEffect(), "opacity", 1.0);
				m_prepareUpgradeState->assignProperty(d->m_comboBox, "visible", true);
			}
			else {
				m_prepareUpgradeState->assignProperty(d->m_comboBox->graphicsEffect(), "opacity", 0.0);
				m_prepareUpgradeState->assignProperty(d->m_comboBox, "visible", false);
			}
			m_prepareUpgradeState->assignProperty(d->m_btnUpgrade->graphicsEffect(), "opacity", 1.0);
			m_prepareUpgradeState->assignProperty(d->m_btnUpgrade, "visible", true);

			m_prepareUpgradeState->assignProperty(d->m_progressBar->graphicsEffect(), "opacity", 0.0);
			m_prepareUpgradeState->assignProperty(d->m_progressBar, "visible", false);
			m_prepareUpgradeState->assignProperty(d->m_btnCancel->graphicsEffect(), "opacity", 0.0);
			m_prepareUpgradeState->assignProperty(d->m_btnCancel, "visible", false);

			m_prepareUpgradeState->assignProperty(d->m_btnBack->graphicsEffect(), "opacity", 0.0);
			m_prepareUpgradeState->assignProperty(d->m_btnBack, "visible", false);
		}


		void MCCusFileUpgradeWidget::creatUpgradingStates()
		{
			m_UpgradingState = new QState(m_upgradeStateMechine);
			
			m_UpgradingState->assignProperty(d->m_comboBox->graphicsEffect(), "opacity", 0.0);
			m_UpgradingState->assignProperty(d->m_comboBox, "visible", false);
			m_UpgradingState->assignProperty(d->m_btnUpgrade->graphicsEffect(), "opacity", 0.0);
			m_UpgradingState->assignProperty(d->m_btnUpgrade, "visible", false);

			m_UpgradingState->assignProperty(d->m_progressBar->graphicsEffect(), "opacity", 1.0);
			m_UpgradingState->assignProperty(d->m_progressBar, "visible", true);
			m_UpgradingState->assignProperty(d->m_btnCancel->graphicsEffect(), "opacity", 1.0);
			m_UpgradingState->assignProperty(d->m_btnCancel, "visible", true);

			m_UpgradingState->assignProperty(d->m_btnBack->graphicsEffect(), "opacity", 0.0);
			m_UpgradingState->assignProperty(d->m_btnBack, "visible", false);
		}

		void MCCusFileUpgradeWidget::creatUpgradingBackStates()
		{
			m_UpgradingBackState = new QState(m_upgradeStateMechine);

			
			m_UpgradingBackState->assignProperty(d->m_comboBox->graphicsEffect(), "opacity", 0.0);
			m_UpgradingBackState->assignProperty(d->m_comboBox, "visible", false);
			m_UpgradingBackState->assignProperty(d->m_btnUpgrade->graphicsEffect(), "opacity", 0.0);
			m_UpgradingBackState->assignProperty(d->m_btnUpgrade, "visible", false);

			m_UpgradingBackState->assignProperty(d->m_progressBar->graphicsEffect(), "opacity", 1.0);
			m_UpgradingBackState->assignProperty(d->m_progressBar, "visible", true);
			m_UpgradingBackState->assignProperty(d->m_btnCancel->graphicsEffect(), "opacity", 0.0);
			m_UpgradingBackState->assignProperty(d->m_btnCancel, "visible", false);

			m_UpgradingBackState->assignProperty(d->m_btnBack->graphicsEffect(), "opacity", 1.0);
			m_UpgradingBackState->assignProperty(d->m_btnBack, "visible", true);
		}

		void MCCusFileUpgradeWidget::creatConnections()
		{
			connect(d->m_btnUpgrade, &QPushButton::clicked, this, &MCCusFileUpgradeWidget::slot_btnUpgrade_clicked);
			connect(d->m_btnCancel, &QPushButton::clicked, this, &MCCusFileUpgradeWidget::slot_btnUpgradeCancel_clicked);
			connect(d->m_btnBack, &QPushButton::clicked, this, &MCCusFileUpgradeWidget::sig_PrepareUpgrade);
			
			connect(&d->m_upgradeWatcher, &QFutureWatcher<quint16>::finished,
				this, &MCCusFileUpgradeWidget::onUpgradeFinished);
			connect(&d->m_upgradeWatcher, &QFutureWatcherBase::progressValueChanged,
				this, &MCCusFileUpgradeWidget::updateUpgardeProgressBar);
			connect(&d->m_upgradeWatcher, &QFutureWatcherBase::progressTextChanged,
				this, &MCCusFileUpgradeWidget::updateUpgardeProgressBar);
		}

		void MCCusFileUpgradeWidget::creatPreparUpgradeTransitions()
		{
			QSignalTransition* transition = m_UpgradingBackState->addTransition(this, &MCCusFileUpgradeWidget::sig_PrepareUpgrade, m_prepareUpgradeState);
            QPropertyAnimation *animation =nullptr;
			foreach(QWidget *widget, extraWidgets) {
				if (QGraphicsOpacityEffect *effect =
					static_cast<QGraphicsOpacityEffect*>(
						widget->graphicsEffect())) {
					animation = new QPropertyAnimation(effect, "opacity", widget);
					animation->setDuration(500);
					animation->setEasingCurve(QEasingCurve::InOutQuart);
					transition->addAnimation(animation);
				}
			}
			transition = m_UpgradingState->addTransition(this, &MCCusFileUpgradeWidget::sig_PrepareUpgrade, m_prepareUpgradeState); 
			transition->addAnimation(animation);
		}

		void MCCusFileUpgradeWidget::creatUpgradingTransitions()
		{
			QSignalTransition* transition = m_prepareUpgradeState->addTransition(this, &MCCusFileUpgradeWidget::sig_Upgrading, m_UpgradingState);
			QPropertyAnimation *animation;
			foreach(QWidget *widget, extraWidgets) {
				if (QGraphicsOpacityEffect *effect =
					static_cast<QGraphicsOpacityEffect*>(
						widget->graphicsEffect())) {
					animation = new QPropertyAnimation(effect, "opacity", widget);
					animation->setDuration(500);
					animation->setEasingCurve(QEasingCurve::InOutQuart);
					transition->addAnimation(animation);
				}
			}
		}

		void MCCusFileUpgradeWidget::creatUpgradingBackTransitions()
		{
			QSignalTransition* transition = m_UpgradingState->addTransition(this, &MCCusFileUpgradeWidget::sig_UpgradingBack, m_UpgradingBackState);
			QPropertyAnimation *animation;
			foreach(QWidget *widget, extraWidgets) {
				if (QGraphicsOpacityEffect *effect =
					static_cast<QGraphicsOpacityEffect*>(
						widget->graphicsEffect())) {
					animation = new QPropertyAnimation(effect, "opacity", widget);
					animation->setDuration(500);
					animation->setEasingCurve(QEasingCurve::InOutQuart);
					transition->addAnimation(animation);
				}
			}
		}

		void MCCusFileUpgradeWidget::slot_btnUpgrade_clicked()
		{
			if (d->m_fileType == LBLFileTransferPackage::EFT_SelectFile) {
			}
			else {
				LBLUIHelper::appRunTimeDataLocation();
				QString fileName = QFileDialog::getOpenFileName(this,
					tr("Select File"),
					App::lastOpenPath,
                    Utils::FileFilter::UPGRADE_FILTER);
				App::lastOpenPath = fileName;
				App::writeConfig();

				if (!fileName.isEmpty()) {
					if (LAPI::EResult::ER_Success == LAPI::UpgradeFile(d->m_fileType, fileName, portIndex(), moduleIndex())) {
						emit sig_Upgrading();
						d->m_upgradeWatcher.blockSignals(false);
						d->m_upgradeWatcher.setFuture(LAPI::UpgradeFuture());
					}
				}
			}
		}

		void MCCusFileUpgradeWidget::slot_btnUpgradeCancel_clicked()
		{
			LAPI::CancelUpgrade();
			d->m_btnCancel->setText(tr("Canceling"));
			d->m_btnCancel->setEnabled(false);
		}

		void MCCusFileUpgradeWidget::onUpgradeFinished()
		{
			if (m_upgradeStateMechine->configuration().contains(m_UpgradingState)) {
				emit sig_UpgradingBack();
				d->m_upgradeWatcher.blockSignals(true);

				d->m_btnCancel->setText(tr("Cancel"));
				d->m_btnCancel->setEnabled(true);
			}
		}

		void MCCusFileUpgradeWidget::updateUpgardeProgressBar()
		{
			d->m_progressBar->setValue(d->m_upgradeWatcher.progressValue());
			if (d->m_upgradeWatcher.isRunning()) {
				d->m_progressBar->setFormat(tr("%1 ,Progress：%2%")\
					.arg(d->m_upgradeWatcher.progressText())\
					.arg(d->m_upgradeWatcher.progressValue()));
			}
			else {
				d->m_progressBar->setFormat(d->m_upgradeWatcher.progressText());
			}
		}

	}
#include "mccusfileupgradewidget.moc"
}
