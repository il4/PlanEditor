#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileSystemModel>
#include <QMainWindow>
#include <QMouseEvent>
#include <qpainter.h>
#include <qlabel.h>
#include <iostream>
#include <qimage.h>

namespace Ui
{
    class MainWindow;
}

class VoronoiParticle
{
public:
    VoronoiParticle(int X, int Y, const VoronoiParticle& parent) : _x(X), _y(Y), _cx(parent._cx), _cy(parent._cy), _name(parent._name), _id(parent._id), _NumOfSup(parent._NumOfSup), _isChild(true), _isMoved(false) { }
    VoronoiParticle(int X, int Y, std::string Name="", int num=0) : _x(X), _y(Y), _cx(X), _cy(Y), _name(Name), _id(_aiID), _NumOfSup(num), _isChild(false), _isMoved(false) { _aiID++; }
    VoronoiParticle(int X, int Y, int cX, int cY, int num=0, std::string Name="") : _x(X), _y(Y), _cx(cX), _cy(cY), _name(Name), _NumOfSup(num), _id(_aiID), _isChild(false), _isMoved(true) { _aiID++; }

    int x()  const { return _x  + 100/2 + 450/2; }
    int y()  const { return 100/2 + 300/2 - _y; }
    int cx() const { return _cx + 100/2 + 450/2; }
    int cy() const { return 100/2 + 300/2 - _cy; }
    unsigned int id() const { return _id; }
    bool isChild() const { return _isChild; }
    bool isMoved() const { return _isChild || _isMoved; }

    int xraw()  const { return _x; }
    int yraw()  const { return _y; }
    int cxraw() const {
        std::cout<<_cx<<std::endl;
        return _cx;
                      }
    int cyraw() const { return _cy; }
    int num()   const {
        std::cout<<_NumOfSup<<std::endl;
        return _NumOfSup;
                      }

    int _x, _y, _cx, _cy;
    std::string _name;
    unsigned int _id, _NumOfSup;
    static unsigned int _aiID;

private:
    bool _isChild;
    bool _isMoved;
};

class Monitor : public QLabel
{
    Q_OBJECT
public:

    explicit Monitor(QWidget *parent = 0) : QLabel(parent) { setMouseTracking(true); }
    ~Monitor() {}

signals:
    void addParticle(int x, int y, int cx, int cy);
    void mMove(int, int, int, int);
    void drawLine(int, int);
    void cordinatePointer(int x, int y);

private:
    void mousePressEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);

    int sX, sY;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QFileSystemModel *dirModel;
    QPainter* painter;
    QImage* image;
    Monitor* monitor;
    std::vector<VoronoiParticle> particles;
    const int SNAP_MAX;
    std::string adr;
    bool hasSaved;

    void drawField();
    void refreshUI();
    void drawParticles();

    unsigned int nearestID(int x, int y);
    unsigned int nearBy(int x, int y, float &d);

    void addParticle(const VoronoiParticle& p);
    void saveConfig(const std::string& add);
    void loadConfig(const std::string& add);
    void simpleSaveFile();

private slots:
    void getParticle(int x, int y, int cx, int cy);
    void getMouseMove(int, int, int, int);
    void setLabel(int x, int y);
    void drawLineInMiddelField(int x, int y);
    void on_b_id_editingFinished();
    void on_update_clicked();
    void on_save_clicked();
    void on_clear_clicked();
    void on_mirrorX_clicked();
    void on_mirrorY_clicked();
    void on_load_clicked();
    void on_treeView_doubleClicked(const QModelIndex &index);
    void on_simpleSave_clicked();
    void on_comboBox_currentIndexChanged(int index);
    void on_comboBox_activated(int index);
};

#endif // MAINWINDOW_H
