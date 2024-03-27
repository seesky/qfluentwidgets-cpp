#include <QtCore/Qt>
#include <QtCore/QSize>
#include <QtCore/QPoint>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>

#include "../components/widgets/button.h"
#include "../common/icon.h"
#include "../common/style_sheet.h"
#include "../components/widgets/spin_box.h"

class Demo : public QWidget{
public:

    QGridLayout *gridLayout;
    SpinBox *spinBox;
    CompactSpinBox *compactSpinBox;
    TimeEdit *timeEdit;
    CompactTimeEdit *compactTimeEdit;
    DateEdit *dateEdit;
    CompactDateEdit *compactDateEdit;
    DateTimeEdit *dateTimeEdit;
    CompactDateTimeEdit *compactDateTimeEdit;
    DoubleSpinBox *doubleSpinBox;
    CompactDoubleSpinBox *compactDoubleSpinBox;

    Demo(){
       this->setStyleSheet(QString("Demo{background: rgb(255, 255, 255)}"));

       this->gridLayout = new QGridLayout(this);

       this->spinBox = new SpinBox(this);
       this->compactSpinBox = new CompactSpinBox(this);
       this->spinBox->setAccelerated(true);
       this->compactSpinBox->setAccelerated(true);

       this->timeEdit = new TimeEdit(this);
       this->compactTimeEdit = new CompactTimeEdit(this);

        this->dateEdit = new DateEdit(this);
        this->compactDateEdit = new CompactDateEdit(this);

       this->dateTimeEdit = new DateTimeEdit(this);
       this->compactDateTimeEdit = new CompactDateTimeEdit(this);

       this->doubleSpinBox = new DoubleSpinBox(this);
       this->compactDoubleSpinBox = new CompactDoubleSpinBox(this);

       this->resize(500, 500);
       this->gridLayout->setHorizontalSpacing(30);

       this->gridLayout->setContentsMargins(100, 50, 100, 50);
       this->gridLayout->addWidget(this->spinBox, 0, 0);
       this->gridLayout->addWidget(this->compactSpinBox, 0, 1, Qt::AlignLeft);

       this->gridLayout->addWidget(this->doubleSpinBox, 1, 0);
       this->gridLayout->addWidget(this->compactDoubleSpinBox, 1, 1, Qt::AlignLeft);

       this->gridLayout->addWidget(this->timeEdit, 2, 0);
       this->gridLayout->addWidget(this->compactTimeEdit, 2, 1, Qt::AlignLeft);

       this->gridLayout->addWidget(this->dateEdit, 3, 0);
       this->gridLayout->addWidget(this->compactDateEdit, 3, 1, Qt::AlignLeft);

       this->gridLayout->addWidget(this->dateTimeEdit, 4, 0);
       this->gridLayout->addWidget(this->compactDateTimeEdit, 4, 1, Qt::AlignLeft);
    };

};



int main(int argc, char *argv[])
{
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    
    QApplication *app = new QApplication(argc, argv);
    Demo *w = new Demo();
    w->show();
    return app->exec();
}