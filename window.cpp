#include "window.h"
#include "ui_window.h"

window::window(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::window)
{
    ui->setupUi(this);
}

window::~window()
{
   delete ui;
}

QImage window::blurImage(QImage imageSource, int blurValue)
{
    if(imageSource.isNull()) return QImage();
    QGraphicsScene scene;
    QGraphicsPixmapItem item;
    item.setPixmap(QPixmap::fromImage(imageSource));

    auto* blur = new QGraphicsBlurEffect;
    blur->setBlurRadius(blurValue);
    item.setGraphicsEffect(blur);
    scene.addItem(&item);
    QImage result (imageSource.size(), QImage::Format_ARGB32);
    result.fill(Qt::transparent);
    QPainter painter(&result);
    scene.render(&painter, QRectF(),
                 QRectF(0, 0, imageSource.width(), imageSource.height()));
    return result;
}


void window::processNewImage(QString sourceFile, int blurValue)
{
    ui->label->setPixmap(QPixmap::fromImage(blurImage(QImage(sourceFile), blurValue).scaled(
                                                    ui->label->width(),
                                                    ui->label->height(),
                                                    Qt::KeepAspectRatio)));
}

void window::openFile()
{
    imageSourcePath = QFileDialog::getOpenFileName(nullptr,
                                 "Open image to blur",
                                                   "",
                                 "image files (*.jpg)"
                                 );
    if(QFileInfo::exists(imageSourcePath))
    {
        processNewImage(imageSourcePath, ui->horizontalSlider->value());
    }
}

void window::blurImage()
{
    if(QFileInfo::exists(imageSourcePath))
    {
        processNewImage(imageSourcePath, ui->horizontalSlider->value());
    }
    else
    {
       ui->label->setText("Image path is not set. Please press \"Open image\" button.");
    }
}
