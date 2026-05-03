// SPDX-FileCopyrightText: 2026 Ernie Pasveer <epasveer@att.net>
//
// SPDX-License-Identifier: GPL-3.0-or-later

#include "SeerMonitorVisualizerWidget.h"
#include "SeerHelpPageDialog.h"
#include "SeerUtl.h"
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QtGui/QFont>
#include <QtCore/QSettings>
#include <QtCore/QDebug>

SeerMonitorVisualizerWidget::SeerMonitorVisualizerWidget (QWidget* parent) : QWidget(parent) {

    // Init variables.
    _monitorId = Seer::createID(); // Create id for gdb monitor messages.

    // Set up UI.
    setupUi(this);

    // Setup the widgets
    setWindowIcon(QIcon(":/seer/resources/icons/hicolor/64x64/seergdb.png"));
    setWindowTitle("Seer - GDB Monitor Visualizer");
    setAttribute(Qt::WA_DeleteOnClose);

    m1ToolButton->setMacroName("M1", "gdbmonitor");
    m2ToolButton->setMacroName("M2", "gdbmonitor");
    m3ToolButton->setMacroName("M3", "gdbmonitor");
    m4ToolButton->setMacroName("M4", "gdbmonitor");
    m5ToolButton->setMacroName("M5", "gdbmonitor");
    m6ToolButton->setMacroName("M6", "gdbmonitor");
    m7ToolButton->setMacroName("M7", "gdbmonitor");
    m8ToolButton->setMacroName("M8", "gdbmonitor");
    m9ToolButton->setMacroName("M9", "gdbmonitor");
    m0ToolButton->setMacroName("M0", "gdbmonitor");

    // Default font.
    QFont font;
    font.setFamily("monospace");
    font.setStyleHint(QFont::Monospace);
    font.setFixedPitch(true);

    // Set the widget's font.
    QTextCharFormat format = textEdit->currentCharFormat();
    format.setFont(font);
    textEdit->setCurrentCharFormat(format);
    textEdit->setFont(font);

    // Connect things.
    QObject::connect(monitorCommandLineEdit,        &QLineEdit::returnPressed,                                 this,            &SeerMonitorVisualizerWidget::handleCommandLineEdit);
    QObject::connect(clearToolButton,               &QToolButton::clicked,                                     this,            &SeerMonitorVisualizerWidget::handleClearButton);
    QObject::connect(printToolButton,               &QToolButton::clicked,                                     this,            &SeerMonitorVisualizerWidget::handlePrintButton);
    QObject::connect(helpToolButton,                &QToolButton::clicked,                                     this,            &SeerMonitorVisualizerWidget::handleHelpButton);
    QObject::connect(macroButtonGroup,              &QButtonGroup::buttonClicked,                              this,            &SeerMonitorVisualizerWidget::handleMacroToolButtonClicked);

    // Restore window settings.
    readSettings();
}

SeerMonitorVisualizerWidget::~SeerMonitorVisualizerWidget () {
}

void SeerMonitorVisualizerWidget::handleText (const QString& text) {
    qDebug() << text;
}

void SeerMonitorVisualizerWidget::handleCommandLineEdit () {

    QString command = monitorCommandLineEdit->text();

    monitorCommandLineEdit->clear();

    emit executeGdbMonitorCommand(_monitorId, command);
}

void SeerMonitorVisualizerWidget::handleClearButton () {
}

void SeerMonitorVisualizerWidget::handlePrintButton () {
}

void SeerMonitorVisualizerWidget::handleHelpButton () {

    SeerHelpPageDialog* help = new SeerHelpPageDialog;
    help->loadFile(":/seer/resources/help/ArrayVisualizer.md");
    help->show();
    help->raise();
}

void SeerMonitorVisualizerWidget::handleMacroToolButtonClicked (QAbstractButton* button) {

    if (button == nullptr) {
        return;
    }

    SeerMacroToolButton* tb = qobject_cast<SeerMacroToolButton*>(button);

    for (auto& command : tb->commands()) {
        if (command == "") {
            continue;
        }

        emit executeGdbMonitorCommand(_monitorId, command);
    }
}

void SeerMonitorVisualizerWidget::writeSettings() {

    QSettings settings;

    settings.beginGroup("gdbmonitorvisualizerwindow"); {
        settings.setValue("size", size());
    } settings.endGroup();
}

void SeerMonitorVisualizerWidget::readSettings() {

    QSettings settings;

    settings.beginGroup("gdbmonitorvisualizerwindow"); {
        resize(settings.value("size", QSize(800, 400)).toSize());
    } settings.endGroup();
}

void SeerMonitorVisualizerWidget::resizeEvent (QResizeEvent* event) {

    writeSettings();

    QWidget::resizeEvent(event);
}

