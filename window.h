#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

#include <QGraphicsScene>
#include <QGraphicsBlurEffect>
#include <QGraphicsPixmapItem>
#include <QPainter>

#include <QDir>
#include <QFileDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class window; }
QT_END_NAMESPACE

class window : public QWidget
{
    Q_OBJECT

public:
    window(QWidget *parent = nullptr);
    ~window();
    QString imageSourcePath = "";
    QImage blurImage(QImage imageSource, int blurValue);
    void processNewImage(QString sourceFile, int blurValue);


public slots:
    void openFile();
    void blurImage();

private:
    Ui::window *ui;
};
#endif // WINDOW_H
