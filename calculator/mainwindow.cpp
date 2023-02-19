#include "mainwindow.h"
#include "ui_mainwindow.h"
// #include <QDebug>

double firstNum;
bool secondNumberTyping = false;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Associates digit_pressed function with button press
    connect(ui->pushButton_0,SIGNAL(released()),
            this, SLOT(digit_pressed()));
    connect(ui->pushButton_1,SIGNAL(released()),
            this, SLOT(digit_pressed()));
    connect(ui->pushButton_2,SIGNAL(released()),
            this, SLOT(digit_pressed()));
    connect(ui->pushButton_3,SIGNAL(released()),
            this, SLOT(digit_pressed()));
    connect(ui->pushButton_4,SIGNAL(released()),
            this, SLOT(digit_pressed()));
    connect(ui->pushButton_5,SIGNAL(released()),
            this, SLOT(digit_pressed()));
    connect(ui->pushButton_6,SIGNAL(released()),
            this, SLOT(digit_pressed()));
    connect(ui->pushButton_7,SIGNAL(released()),
            this, SLOT(digit_pressed()));
    connect(ui->pushButton_8,SIGNAL(released()),
            this, SLOT(digit_pressed()));
    connect(ui->pushButton_9,SIGNAL(released()),
            this, SLOT(digit_pressed()));

    // Associates the plusminus function with a button press
    connect(ui->pushButton_plusMinus,SIGNAL(released()),
            this, SLOT(unary_operation_pressed()));
    // Associating the percent function with a button press
    connect(ui->pushButton_percent,SIGNAL(released()),
            this, SLOT(unary_operation_pressed()));

    // Next comes the associations between binary operations buttons
    connect(ui->pushButton_add,SIGNAL(released()),
            this, SLOT(binary_operation_pressed()));
    connect(ui->pushButton_subtract,SIGNAL(released()),
            this, SLOT(binary_operation_pressed()));
    connect(ui->pushButton_multiply,SIGNAL(released()),
            this, SLOT(binary_operation_pressed()));
    connect(ui->pushButton_divide,SIGNAL(released()),
            this, SLOT(binary_operation_pressed()));

    // Checking if binary buttons have been pressed
    ui->pushButton_add->setCheckable(true);
    ui->pushButton_subtract->setCheckable(true);
    ui->pushButton_multiply->setCheckable(true);
    ui->pushButton_divide->setCheckable(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::digit_pressed() {
    /* Including QDebug to test if the buttons work or not */
    // qDebug() << "Test";

    /* Sender returns a pointer to QObject (QPushButton).
     * Then also caches the sender to QPushButton pointer*/
    QPushButton * button = (QPushButton*)sender();
    double labelNumber;
    QString newLabel;

    /* This if-else statement checks if binary operations
     * have been executed. If true, the label will clear and it
     * will allow us to add the second number. If false,
     * label will keep appending the pressed numbers until
     * an operation is executed */
    if ((ui->pushButton_add->isChecked() ||
            ui->pushButton_subtract->isChecked() ||
            ui->pushButton_multiply->isChecked() ||
            ui->pushButton_divide->isChecked()) && (!secondNumberTyping)) {
        labelNumber = button->text().toDouble();
        secondNumberTyping = true;
        /* Double datatype can not be assigned to setText
         * so it has to be converted to QString */
        newLabel = QString::number(labelNumber,'g', 13);
    }
    else {
        if (ui->label->text().contains('.') && button->text()=="0") {
            newLabel = ui->label->text() + button->text();
        }
        else {
            labelNumber = (ui->label->text()+button->text()).toDouble();
            newLabel = QString::number(labelNumber,'g', 13);
        }
    }
    // This will output text in the label box depending which button was pressed
    ui->label->setText(newLabel);
}

void MainWindow::on_pushButton_decimal_released() {
    /* Appends a decimal to the label for decimal calculation.
     * Also has if-else loop to check if you have
     * already inputted a decimal and won't let you add
     * another decimal if one exists. */

    if (ui->label->text().contains(".")) {
            return;
}
    else {
        ui->label->setText(ui->label->text() + ".");
    }
}

void MainWindow::unary_operation_pressed() {
    QPushButton * button = (QPushButton*)sender();
    double labelNumber;
    QString newLabel;

    if (button->text() == "+/-") {
        labelNumber = ui->label->text().toDouble();
        labelNumber = labelNumber * -1;
        newLabel = QString::number(labelNumber, 'g', 13);
        ui->label->setText(newLabel);
    }
    if (button->text() == "%") {
        labelNumber = ui->label->text().toDouble();
        labelNumber = labelNumber * 0.01;
        newLabel = QString::number(labelNumber, 'g', 13);
        ui->label->setText(newLabel);
    }


}

// This function clears the output after button press
void MainWindow::on_pushButton_clear_released() {
    ui->pushButton_add->setChecked(false);
    ui->pushButton_subtract->setChecked(false);
    ui->pushButton_multiply->setChecked(false);
    ui->pushButton_divide->setChecked(false);
    secondNumberTyping = false;
    ui->label->setText("0");
}


void MainWindow::on_pushButton_equals_released() {
    double labelNumber, secondNum;
    QString newLabel;
    secondNum = ui->label->text().toDouble();

    if (ui->pushButton_add->isChecked()) {
        labelNumber = firstNum + secondNum;
        newLabel = QString::number(labelNumber, 'g', 13);
        ui->label->setText(newLabel);
        ui->pushButton_add->setChecked(false);
    }
    else if (ui->pushButton_subtract->isChecked()) {
        labelNumber = firstNum - secondNum;
        newLabel = QString::number(labelNumber, 'g', 13);
        ui->label->setText(newLabel);
        ui->pushButton_subtract->setChecked(false);
    }
    else if (ui->pushButton_multiply->isChecked()) {
        labelNumber = firstNum * secondNum;
        newLabel = QString::number(labelNumber, 'g', 13);
        ui->label->setText(newLabel);
        ui->pushButton_multiply->setChecked(false);
    }
    else if (ui->pushButton_divide->isChecked()) {
        labelNumber = firstNum / secondNum;
        newLabel = QString::number(labelNumber, 'g', 13);
        ui->label->setText(newLabel);
        ui->pushButton_divide->setChecked(false);
    }
    secondNumberTyping = false;
}

// This function checks if a binary operator has been pressed
void MainWindow::binary_operation_pressed() {
    QPushButton * button = (QPushButton*)sender();
    firstNum = ui->label->text().toDouble();
    button->setChecked(true);
}


