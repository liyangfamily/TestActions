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
var targetDirectoryPage = null;

function Component() {
    component.loaded.connect(this, this.installerLoaded);
    if (!installer.isOfflineOnly()) {
        this.installerLoaded();
    }

}

// 实用函数，类似于 QString QDir::toNativeSeparators()
var Dir = new function() {
    this.toNativeSparator = function(path) {
        if (installer.value("os") == "win")
            return path.replace(/\//g, '\\');
        return path;
    }
};

Component.prototype.createOperations = function() {
    // call default implementation to actually install README.txt!
    component.createOperations();

    component.addOperation("CreateShortcut",
        "@TargetDir@/MaxConfig.exe",
        "@DesktopDir@/MaxConfig3.lnk",
        "workingDirectory=@TargetDir@");
	component.addOperation("CreateShortcut",
        "@TargetDir@/MaxConfig.exe",
        "@StartMenuDir@/MaxConfig3.lnk",
        "workingDirectory=@TargetDir@");
}

// 加载组件后立即调用
Component.prototype.installerLoaded = function() {

    installer.gainAdminRights();

    installer.setDefaultPageVisible(QInstaller.TargetDirectory, false);
    installer.addWizardPage(component, "TargetWidget", QInstaller.TargetDirectory);

    targetDirectoryPage = gui.pageWidgetByObjectName("DynamicTargetWidget");
    targetDirectoryPage.windowTitle = "选择安装目录";
    targetDirectoryPage.description.setText("请选择程序的安装位置：");
    targetDirectoryPage.targetDirectory.textChanged.connect(this, this.targetDirectoryChanged);
    targetDirectoryPage.targetDirectory.setText(Dir.toNativeSparator(installer.value("TargetDir")));
    targetDirectoryPage.targetChooser.released.connect(this, this.targetChooserClicked);

    gui.pageById(QInstaller.ComponentSelection).entered.connect(this, this.componentSelectionPageEntered);
}

// 当点击选择安装位置按钮时调用
Component.prototype.targetChooserClicked = function() {
    var dir = QFileDialog.getExistingDirectory("", targetDirectoryPage.targetDirectory.text);
    if (dir != "") {
        targetDirectoryPage.targetDirectory.setText(Dir.toNativeSparator(dir + "/" + installer.value("ProductName")));
    }
}

// 当安装位置发生改变时调用
Component.prototype.targetDirectoryChanged = function() {
    var dir = targetDirectoryPage.targetDirectory.text;
    if (installer.fileExists(dir) && installer.fileExists(dir + "/MaxConfig.exe")) {
        targetDirectoryPage.warning.setText("<p style=\"color: red\">检测到程序已安装，继续将会被卸载。</p>");
    } else {
        targetDirectoryPage.warning.setText("");
    }
    installer.setValue("TargetDir", dir);
}

// 当进入【选择组件】页面时调用
Component.prototype.componentSelectionPageEntered = function() {
    var dir = installer.value("TargetDir");
    if (installer.isInstaller()) {
        if (installer.fileExists(dir) && installer.fileExists(dir + "/maintenancetool.exe")) {
            installer.execute(dir + "/maintenancetool.exe", "--script=" + dir + "/script/uninstallscript.qs");
        }
    }
}
