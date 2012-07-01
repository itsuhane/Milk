#ifndef MILKMAINWINDOW_H
#define MILKMAINWINDOW_H

#include <QtGui>
#include <QtScript>

#include "timelinewidget.h"

class MilkMainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MilkMainWindow(QWidget *parent = 0);
protected:
    void createCentralView();
    void createAction();
    void createMenu();
    void createToolBar();
    void createStatusBar();
    void createDockPanel();

private:
    void createCommonToolBar();
    void createPanelToolBar();

    void createModelPanel();
    void createMaterialPanel();
    void createCameraPanel();
    void createLightPanel();
    void createScenePanel();
    void createNodePanel();
    void createTimelinePanel();
    void createTargetPanel();
    void createConsolePanel();

    QAction* actionNewProject;
    QAction* actionOpenProject;
    QAction* actionSaveProject;
    QAction* actionSaveProjectAs;
    QAction* actionExit;

    QAction* actionUndo;
    QAction* actionRedo;
    QAction* actionCut;
    QAction* actionCopy;
    QAction* actionPaste;
    QAction* actionDelete;
    QAction* actionSettings;

    QMenu* menuFile;
    QMenu* menuEdit;
    QMenu* menuView;
    QMenu* menuHelp;

    QToolBar* toolbarCommon;
    QToolBar* toolbarPanel;

    QDockWidget* panelModel;
    QDockWidget* panelMaterial;
    QDockWidget* panelCamera;
    QDockWidget* panelLight;
    QDockWidget* panelScene;
    QDockWidget* panelNode;
    QDockWidget* panelTimeline;
    QDockWidget* panelTarget;
    QDockWidget* panelConsole;

    QWidget* viewMain;

    TimelineWidget* timelineWidget;
private slots:
    void test();
};

#endif // MILKMAINWINDOW_H
