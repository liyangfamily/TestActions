/****************************************************************************
**
** Copyright (C) 2017 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the FOO module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:GPL-EXCEPT$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3-EXCEPT
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/gpl-3.0.html.
**
** $QT_END_LICENSE$
**
****************************************************************************/

// 更新脚本
 
function Controller()
{
    // 连接信号槽
    installer.installationFinished.connect(this, this.installationFinished);
}

Controller.prototype.IntroductionPageCallback = function()
{
    var widget = gui.currentPageWidget(); // get the current wizard page
    if (widget != null) {
		var installerRadioBtn = widget.findChild("UpdaterRadioButton");
		installerRadioBtn.checked = true;

		gui.clickButton(buttons.NextButton);
    }
}

Controller.prototype.DynamicTargetWidgetCallback = function()
{
	gui.clickButton(buttons.NextButton);
}

Controller.prototype.ComponentSelectionPageCallback = function()
{
	gui.clickButton(buttons.NextButton);
}

Controller.prototype.ReadyForInstallationPageCallback = function()
{
	gui.clickButton(buttons.NextButton);
}

// 当卸载完成时，触发
Controller.prototype.installationFinished = function()
{
    gui.clickButton(buttons.NextButton);
}
 
// 与完成页面上的部件交互
Controller.prototype.FinishedPageCallback = function()
{
    gui.clickButton(buttons.FinishButton);
	installer.autoAcceptMessageBoxes();
}
