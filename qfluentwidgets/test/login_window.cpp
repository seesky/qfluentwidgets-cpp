#include "login_window.h"

LoginWindow::LoginWindow(QWidget *parent) : AcrylicWindow(parent)
{
    this->setupUi();
    
    
    //this->setTitleBar(new SplitTitleBar(this));
    this->setWindowTitle(QString("Acrylic Window"));
    this->titleBar->raise();

    /*
    this->label->setScaledContents(false);
    this->setWindowTitle("UPR");
    this->setWindowIcon(QIcon("resource/images/logo.png"));
    this->resize(1000, 650);

    
    this->windowEffect->setMicaEffect(reinterpret_cast<HWND>(this->winId()), false, false);
    this->setStyleSheet("LoginWindow{background: rgba(242, 242, 242, 0.8)}");
    
    QRect desktop = QApplication::desktop()->availableGeometry();
    int w = desktop.width();
    int h = desktop.height();
    this->move(w / 2 - this->width() / 2, h / 2 - this->height() / 2);
    */
}

void LoginWindow::setupUi()
{
    this->setObjectName("Form");
    this->resize(1250, 809);
    this->setMinimumSize(QSize(700, 500));
    this->horizontalLayout = new QHBoxLayout(this);
    this->horizontalLayout->setContentsMargins(0, 0, 0, 0);
    this->horizontalLayout->setSpacing(0);
    this->horizontalLayout->setObjectName("horizontalLayout");
    this->label = new QLabel(this);
    this->label->setText("");
    this->label->setPixmap(QPixmap("qfluentwidgets/images/background.jpg"));
    this->label->setScaledContents(true);
    this->label->setObjectName("label");
    this->horizontalLayout->addWidget(this->label);

    this->widget = new QWidget(this);
    this->sizePolicy = new QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    sizePolicy->setHorizontalStretch(0);
    sizePolicy->setVerticalStretch(0);
    sizePolicy->setHeightForWidth(this->widget->sizePolicy().hasHeightForWidth());
    this->widget->setSizePolicy(*(this->sizePolicy));
    this->widget->setMinimumSize(QSize(360, 0));
    this->widget->setMaximumSize(QSize(360, 16777215));
    this->widget->setStyleSheet("QLabel{font: 13px 'Microsoft YaHei'}");

    this->widget->setObjectName("widget");
    this->verticalLayout_2 = new QVBoxLayout(this->widget);
    this->verticalLayout_2->setContentsMargins(20, 20, 20, 20);
    this->verticalLayout_2->setSpacing(9);
    this->verticalLayout_2->setObjectName("verticalLayout_2");
    this->spacerItem = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    this->verticalLayout_2->addItem(this->spacerItem);
    this->label_2 = new QLabel(this->widget);
    this->label_2->setEnabled(true);
    this->sizePolicy2 = new QSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    this->sizePolicy2->setHorizontalStretch(0);
    this->sizePolicy2->setVerticalStretch(0);
    this->sizePolicy2->setHeightForWidth(this->label_2->sizePolicy().hasHeightForWidth());
    this->label_2->setSizePolicy(*(this->sizePolicy2));
    this->label_2->setMinimumSize(QSize(100, 100));
    this->label_2->setMaximumSize(QSize(100, 100));
    this->label_2->setText("");
    this->label_2->setPixmap(QPixmap("qfluentwidgets/images/logo.png"));
    this->label_2->setScaledContents(true);
    this->label_2->setObjectName("label_2");
    this->verticalLayout_2->addWidget(this->label_2, 0, Qt::AlignHCenter);
    this->spacerItem1 = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);
    this->verticalLayout_2->addItem(this->spacerItem1);
    this->gridLayout = new QGridLayout();
    this->gridLayout->setHorizontalSpacing(4);
    this->gridLayout->setVerticalSpacing(9);
    this->gridLayout->setObjectName("gridLayout");


    this->lineEdit = new LineEdit(this->widget);
    this->lineEdit->setClearButtonEnabled(true);
    this->lineEdit->setObjectName("lineEdit");
    this->gridLayout->addWidget(this->lineEdit, 1, 0, 1, 1);
    this->label_3 = new BodyLabel(this->widget);
    this->label_3->setObjectName("label_3");
    this->gridLayout->addWidget(this->label_3, 0, 0, 1, 1);

    this->lineEdit_2 = new LineEdit(this->widget);
    this->lineEdit_2->setPlaceholderText("");
    this->lineEdit_2->setClearButtonEnabled(true);
    this->lineEdit_2->setObjectName("lineEdit_2");
    this->gridLayout->addWidget(this->lineEdit_2, 1, 1, 1, 1);
    this->label_4 = new BodyLabel(this->widget);
    this->label_4->setObjectName("label_4");
    this->gridLayout->addWidget(this->label_4, 0, 1, 1, 1);
    this->gridLayout->setColumnStretch(0, 2);
    this->gridLayout->setColumnStretch(1, 1);
    this->verticalLayout_2->addLayout(this->gridLayout);
    this->label_5 = new BodyLabel(this->widget);
    this->label_5->setObjectName("label_5");
    this->verticalLayout_2->addWidget(this->label_5);
    this->lineEdit_3 = new LineEdit(this->widget);
    this->lineEdit_3->setClearButtonEnabled(true);
    this->lineEdit_3->setObjectName("lineEdit_3");
    this->verticalLayout_2->addWidget(this->lineEdit_3);

    this->label_6 = new BodyLabel(this->widget);
    this->label_6->setObjectName("label_6");
    this->verticalLayout_2->addWidget(this->label_6);
    this->lineEdit_4 = new LineEdit(this->widget);
    this->lineEdit_4->setEchoMode(QLineEdit::Password);
    this->lineEdit_4->setClearButtonEnabled(true);
    this->lineEdit_4->setObjectName("lineEdit_4");
    this->verticalLayout_2->addWidget(this->lineEdit_4);

    this->spacerItem2 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);
    this->verticalLayout_2->addItem(this->spacerItem2);
    this->checkBox = new CheckBox(this->widget);
    this->checkBox->setChecked(true);
    this->checkBox->setObjectName("checkBox");
    this->checkBox->setTristate(false);
    this->verticalLayout_2->addWidget(this->checkBox);

    this->spacerItem3 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Fixed);
    this->verticalLayout_2->addItem(this->spacerItem3);
    this->pushButton = new PrimaryPushButton("", this->widget, nullptr);
    this->pushButton->setObjectName("pushButton");
    this->verticalLayout_2->addWidget(this->pushButton);


    this->spacerItem4 = new QSpacerItem(20, 6, QSizePolicy::Minimum, QSizePolicy::Fixed);
    this->verticalLayout_2->addItem(this->spacerItem4);
    QVariant url = QVariant::fromValue<QString>(QString("http://www.usable-programming.com"));
    this->pushButton_2 = new HyperlinkButton(&url, QString(""), this->widget, nullptr);
    this->pushButton_2->setObjectName("pushButton_2");
    this->verticalLayout_2->addWidget(this->pushButton_2);


    this->spacerItem5 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    this->verticalLayout_2->addItem(spacerItem5);
    this->horizontalLayout->addWidget(this->widget);

    this->retranslateUi();
    QMetaObject::connectSlotsByName(this);
}

void LoginWindow::retranslateUi()
{
    this->setWindowTitle(this->tr("UPR"));
    this->lineEdit->setPlaceholderText(this->tr("ftp.example.com"));
    this->label_3->setText(this->tr("主机"));
    this->lineEdit_2->setText(this->tr("21"));
    this->label_4->setText(this->tr("端口"));
    this->label_5->setText(this->tr("用户名"));
    this->lineEdit_3->setPlaceholderText(this->tr("example@example.com"));
    this->label_6->setText(this->tr("密码"));
    this->lineEdit_4->setPlaceholderText(this->tr("记住密码"));
    this->pushButton->setText(this->tr("登陆"));
    this->pushButton_2->setText(this->tr("找回密码"));
}


void LoginWindow::resizeEvent(QResizeEvent *event)
{
    AcrylicWindow::resizeEvent(event);
    QPixmap pixmap("qfluentwidgets/images/background.jpg");
    this->label->setPixmap(pixmap.scaled(this->label->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation));
}