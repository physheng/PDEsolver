#ifndef UI_Plot2DWindow_H
#define UI_Plot2DWindow_H
#include <QtGui>
//#include "./QCustomPlot/qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_Plot2DWindow
{
public:
    void setupUi(QMainWindow *Plot2DWindow)
    {
        //Plot2DWindow->setWindowTitle(("PDE simulation 2D Plot"));
        //Plot2DWindow->setMinimumSize(480, 320);
        //Plot2DWindow->setGeometry(200, 200,720, 480);
    } // setupUi
};

namespace Ui {
    class Plot2DWindow: public Ui_Plot2DWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
