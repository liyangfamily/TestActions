#include "versiondialog.h"

#include "Core/icore.h"
#include "Core/app_version.h"

#include <QLabel>
#include <QGridLayout>
#include <QDialogButtonBox>
#include <QDateTime>

using namespace Core;
VersionDialog::VersionDialog(QWidget *parent)
    : QDialog(parent)
{
    // We need to set the window icon explicitly here since for some reason the
    // application icon isn't used when the size of the dialog is fixed (at least not on X11/GNOME)

    setWindowTitle(tr("About %1").arg("MaxConfig"));
    auto layout = new QGridLayout(this);
    layout->setSizeConstraint(QLayout::SetFixedSize);

    QString buildGitSHA;
//#ifdef IDE_REVISION
    buildGitSHA = tr("<br/>From reversion %1-%2<br/>")
            .arg(QString(GIT_BUILD_SHA))
			.arg(QString(GIT_BUILD_TIME));
//#endif
     QString buildGitDateInfo;
#ifndef QTC_SHOW_BUILD_DATE
     buildGitDateInfo = tr("<br/>Built on %1<br/>").arg(QDateTime::currentDateTime().toString("yyyy.MM.dd hh:mm:ss"));
     //buildGitDateInfo = tr("<br/>Built on %1<br/>")
             //.arg(QString(GIT_BUILD_TIME));
#endif

    const QString br = QLatin1String("<br/>");
    const QStringList additionalInfoLines;
    const QString additionalInfo;

    const QString description = tr(
        "<h3>%1</h3>"
        "%2<br/>"
        "%3"
        "%4"
        "%5"
        "<br/>"
        "Copyright 2019-%6 %7. All rights reserved.<br/>"
        "<br/>")
        .arg(ICore::versionString(),
             ICore::buildCompatibilityString(),
             buildGitSHA,
             buildGitDateInfo,
             additionalInfo.isEmpty() ? QString() : br + additionalInfo + br,
             QLatin1String(Core::Constants::IDE_YEAR),
             QLatin1String(Core::Constants::IDE_AUTHOR));

    QLabel *copyRightLabel = new QLabel(description);
    //copyRightLabel->setWordWrap(true);
    copyRightLabel->setOpenExternalLinks(true);
    copyRightLabel->setTextInteractionFlags(Qt::TextBrowserInteraction);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Close);
    QPushButton *closeButton = buttonBox->button(QDialogButtonBox::Close);
    buttonBox->addButton((QAbstractButton *)closeButton, QDialogButtonBox::ButtonRole(QDialogButtonBox::RejectRole | QDialogButtonBox::AcceptRole));
    connect(buttonBox , &QDialogButtonBox::rejected, this, &QDialog::reject);

    QLabel *logoLabel = new QLabel;
    logoLabel->setPixmap(QPixmap(":/Normal/Resources/Normal/MaxConfig.ico").scaled(128,128,Qt::KeepAspectRatio));
    layout->addWidget(logoLabel , 0, 0, 1, 1);
    layout->addWidget(copyRightLabel, 0, 1, 1, 1);
    layout->addWidget(buttonBox, 1, 1, 1, 1);
    layout->setColumnStretch(0,0);
    layout->setColumnStretch(1,1);
    layout->setHorizontalSpacing(20);
}
