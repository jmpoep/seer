#include "SeerCatchpointCreateDialog.h"
#include <QtCore/QDebug>

SeerCatchpointCreateDialog::SeerCatchpointCreateDialog (QWidget* parent) : QDialog(parent) {

    // Set up the UI.
    setupUi(this);

    // Setup the widgets
    setType("");
    setArguments("");

    setTemporaryEnabled(false);
    setDisabledEnabled(false);

    throwRadioButton->setFocus();

    // Connect things.
}

SeerCatchpointCreateDialog::~SeerCatchpointCreateDialog () {
}

void SeerCatchpointCreateDialog::setType (const QString& text) {

    if (text == "throw") {
        throwRadioButton->setChecked(true);

    }else if (text == "rethrow") {
        rethrowRadioButton->setChecked(true);

    }else if (text == "catch") {
        catchRadioButton->setChecked(true);

    }else if (text == "load") {
        loadRadioButton->setChecked(true);

    }else if (text == "unload") {
        unloadRadioButton->setChecked(true);

    }else if (text == "assert") {
        adaAssertRadioButton->setChecked(true);

    }else if (text == "exception") {
        adaExceptionRadioButton->setChecked(true);

    }else if (text == "handlers") {
        adaHandlersRadioButton->setChecked(true);

    }else if (text == "signal") {
        signalRadioButton->setChecked(true);

    }else if (text == "fork") {
        forkRadioButton->setChecked(true);

    }else if (text == "vfork") {
        vforkRadioButton->setChecked(true);

    }else if (text == "exec") {
        execRadioButton->setChecked(true);

    }else if (text == "syscall") {
        syscallRadioButton->setChecked(true);

    }else{
        throwRadioButton->setChecked(true);
    }
}

QString SeerCatchpointCreateDialog::typeText () const {

    if (throwRadioButton->isChecked()) {
        return "throw";

    }else if (rethrowRadioButton->isChecked()) {
        return "rethrow";

    }else if (catchRadioButton->isChecked()) {
        return "catch";

    }else if (loadRadioButton->isChecked()) {
        return "load";

    }else if (unloadRadioButton->isChecked()) {
        return "unload";

    }else if (adaAssertRadioButton->isChecked()) {
        return "assert";

    }else if (adaExceptionRadioButton->isChecked()) {
        return "exception";

    }else if (adaHandlersRadioButton->isChecked()) {
        return "handlers";

    }else if (signalRadioButton->isChecked()) {
        return "signal";

    }else if (forkRadioButton->isChecked()) {
        return "fork";

    }else if (vforkRadioButton->isChecked()) {
        return "vfork";

    }else if (execRadioButton->isChecked()) {
        return "exec";

    }else if (syscallRadioButton->isChecked()) {
        return "syscall";

    }else{
        return "throw";
    }
}

void SeerCatchpointCreateDialog::setTemporaryEnabled (bool flag) {
    temporaryCheckBox->setChecked(flag);
}

void SeerCatchpointCreateDialog::setDisabledEnabled (bool flag) {
    disabledCheckBox->setChecked(flag);
}

void SeerCatchpointCreateDialog::setArguments (const QString& text) {
    argumentsLineEdit->setText(text);
}

QString SeerCatchpointCreateDialog::arguments () const {
    return argumentsLineEdit->text();
}

bool SeerCatchpointCreateDialog::temporaryEnabled () const {
    return temporaryCheckBox->isChecked();
}

bool SeerCatchpointCreateDialog::disabledEnabled () const {
    return disabledCheckBox->isChecked();
}

QString SeerCatchpointCreateDialog::catchpointText () const {

    // Build a catchpoint specification.
    QString catchpointParameters = typeText();

    if (temporaryEnabled()) {
        catchpointParameters += " -t";
    }

    if (disabledEnabled()) {
        catchpointParameters += " -d";
    }

    if (typeText() == "assert") { // Handle Ada 'assert'. Nothing to add here.

    }else if (typeText() == "exception") { // Handle Ada 'exception'.

        if (arguments() != "") {
            catchpointParameters += " -e " + arguments();
        }

    }else if (typeText() == "handlers") { // Handle Ada 'handlers'.

        if (arguments() != "") {
            catchpointParameters += " -e " + arguments();
        }

    }else if (typeText() == "load") { // Handle library 'load'. Must have a name.

        catchpointParameters += " " + arguments();

    }else if (typeText() == "unload") { // Handle library 'unload'. Must have a name.

        catchpointParameters += " " + arguments();

    }else if (typeText() == "signal") { // Handle library 'unload'. Must have a name.

        catchpointParameters += " " + arguments();

    }else if (typeText() == "syscall") { // Handle library 'unload'. Must have a name.

        catchpointParameters += " " + arguments();

    }else{  // C++ throw, rethrow, catch. These require '-r', but only if there is a name.

        if (arguments() != "") {
            catchpointParameters += " -r " + arguments();
        }
    }

    // qDebug() << catchpointParameters;

    return catchpointParameters;
}

