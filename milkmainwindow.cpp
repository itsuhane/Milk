#include <QtGui>

#include "milkmainwindow.h"

#include "glwidget.h"

MilkMainWindow::MilkMainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setObjectName("MilkMainWindow");
    setWindowTitle("Milk");
    setWindowIcon(QIcon(":/ui/app.ico"));

    setDockOptions(QMainWindow::AllowNestedDocks|QMainWindow::AllowTabbedDocks);

    setMinimumSize(320, 240);

    createCentralView();

    createAction();
    createMenu();
    createToolBar();
    createStatusBar();
    createDockPanel();
}

void MilkMainWindow::createCentralView()
{
    viewMain = new GLWidget;
    setCentralWidget(viewMain);
}

void MilkMainWindow::createAction()
{
    actionNewProject    = new QAction(QIcon(":/ui/action/new.png"), tr("&New Project"), this);
    actionOpenProject   = new QAction(QIcon(":/ui/action/open.png"), tr("&Open Project..."), this);
    actionSaveProject   = new QAction(QIcon(":/ui/action/save.png"), tr("&Save Project"), this);
    actionSaveProjectAs = new QAction(QIcon(":/ui/action/saveas.png"), tr("Save Project &As..."), this);
    actionExit          = new QAction(QIcon(":/ui/action/exit.png"), tr("E&xit"), this);

    actionUndo          = new QAction(QIcon(":/ui/action/undo.png"), tr("&Undo"), this);
    actionRedo          = new QAction(QIcon(":/ui/action/redo.png"), tr("&Redo"), this);
    actionCut           = new QAction(QIcon(":/ui/action/cut.png"), tr("Cu&t"), this);
    actionCopy          = new QAction(QIcon(":/ui/action/copy.png"), tr("&Copy"), this);
    actionPaste         = new QAction(QIcon(":/ui/action/paste.png"), tr("&Paste"), this);
    actionDelete        = new QAction(QIcon(":/ui/action/delete.png"), tr("&Delete"), this);
    actionSettings      = new QAction(QIcon(":/ui/action/settings.png"), tr("&Settings..."), this);
}

void MilkMainWindow::createMenu()
{
    menuFile = menuBar()->addMenu(tr("&File"));
    menuEdit = menuBar()->addMenu(tr("&Edit"));
    menuView = menuBar()->addMenu(tr("&View"));
    menuHelp = menuBar()->addMenu(tr("&Help"));

    menuFile->addAction(actionNewProject);
    menuFile->addAction(actionOpenProject);
    menuFile->addSeparator();
    menuFile->addAction(actionSaveProject);
    menuFile->addAction(actionSaveProjectAs);
    menuFile->addSeparator();
    menuFile->addAction(actionExit);

    menuEdit->addAction(actionUndo);
    menuEdit->addAction(actionRedo);
    menuEdit->addSeparator();
    menuEdit->addAction(actionCut);
    menuEdit->addAction(actionCopy);
    menuEdit->addAction(actionPaste);
    menuEdit->addAction(actionDelete);
    menuEdit->addSeparator();
    menuEdit->addAction(actionSettings);
}

void MilkMainWindow::createToolBar()
{
    createCommonToolBar();
    createPanelToolBar();
}

void MilkMainWindow::createStatusBar()
{
    statusBar()->setSizeGripEnabled(false);
}

void MilkMainWindow::createDockPanel()
{
    menuView->addSeparator();

    createModelPanel();
    createMaterialPanel();
    createCameraPanel();
    createLightPanel();
    createScenePanel();
    createNodePanel();
    createTimelinePanel();
    createTargetPanel();
    createConsolePanel();
}

void MilkMainWindow::createCommonToolBar()
{
    toolbarCommon = addToolBar(tr("Common"));
    toolbarCommon->addAction(actionNewProject);
    toolbarCommon->addAction(actionOpenProject);
    toolbarCommon->addSeparator();
    toolbarCommon->addAction(actionUndo);
    toolbarCommon->addAction(actionRedo);
    toolbarCommon->addSeparator();
    toolbarCommon->addAction(actionCut);
    toolbarCommon->addAction(actionCopy);
    toolbarCommon->addAction(actionPaste);
    toolbarCommon->addSeparator();
    toolbarCommon->addAction(actionDelete);
    QAction* actionTest = new QAction(tr("Test"),this);
    toolbarCommon->addAction(actionTest);
    QAction* action = toolbarCommon->toggleViewAction();
    action->setStatusTip(tr("Show/Hide Common Toolbar"));
    menuView->addAction(action);

    connect(actionTest, SIGNAL(triggered()), this, SLOT(test()));
}

void MilkMainWindow::createPanelToolBar()
{
    toolbarPanel = addToolBar(tr("Panels"));
    QAction* action = toolbarPanel->toggleViewAction();
    action->setStatusTip(tr("Show/Hide Panels Toolbar"));
    menuView->addAction(action);
}

void MilkMainWindow::createModelPanel()
{
    panelModel = new QDockWidget(tr("Model"), this);
    addDockWidget(Qt::LeftDockWidgetArea, panelModel);
    panelModel->setVisible(false);
    QAction* action = panelModel->toggleViewAction();
    menuView->addAction(action);
    action->setIcon(QIcon(":/ui/action/model.png"));
    action->setIconVisibleInMenu(false);
    action->setStatusTip(tr("Show/Hide Model Panel."));
    toolbarPanel->addAction(action);
}

void MilkMainWindow::createMaterialPanel()
{
    panelMaterial = new QDockWidget(tr("Material"), this);
    addDockWidget(Qt::LeftDockWidgetArea, panelMaterial);
    panelMaterial->setVisible(false);
    QAction* action = panelMaterial->toggleViewAction();
    menuView->addAction(action);
    action->setIcon(QIcon(":/ui/action/material.png"));
    action->setIconVisibleInMenu(false);
    action->setStatusTip(tr("Show/Hide Material Panel."));
    toolbarPanel->addAction(action);
}

void MilkMainWindow::createCameraPanel()
{
    panelCamera = new QDockWidget(tr("Camera"), this);
    addDockWidget(Qt::RightDockWidgetArea, panelCamera);
    panelCamera->setVisible(false);
    QAction* action = panelCamera->toggleViewAction();
    menuView->addAction(action);
    action->setIcon(QIcon(":/ui/action/camera.png"));
    action->setIconVisibleInMenu(false);
    action->setStatusTip(tr("Show/Hide Camera Panel."));
    toolbarPanel->addAction(action);
}

void MilkMainWindow::createLightPanel()
{
    panelLight = new QDockWidget(tr("Light"), this);
    addDockWidget(Qt::RightDockWidgetArea, panelLight);
    panelLight->setVisible(false);
    QAction* action = panelLight->toggleViewAction();
    menuView->addAction(action);
    action->setIcon(QIcon(":/ui/action/light.png"));
    action->setIconVisibleInMenu(false);
    action->setStatusTip(tr("Show/Hide Light Panel."));
    toolbarPanel->addAction(action);
}

void MilkMainWindow::createScenePanel()
{
    panelScene = new QDockWidget(tr("Scene"), this);
    addDockWidget(Qt::TopDockWidgetArea, panelScene);
    panelScene->setVisible(false);
    QAction* action = panelScene->toggleViewAction();
    menuView->addAction(action);
    action->setIcon(QIcon(":/ui/action/scene.png"));
    action->setIconVisibleInMenu(false);
    action->setStatusTip(tr("Show/Hide Scene Panel."));
    toolbarPanel->addAction(action);
}

void MilkMainWindow::createNodePanel()
{
    panelNode = new QDockWidget(tr("Node"), this);
    addDockWidget(Qt::BottomDockWidgetArea, panelNode);
    panelNode->setVisible(false);
    QAction* action = panelNode->toggleViewAction();
    menuView->addAction(action);
    action->setIcon(QIcon(":/ui/action/node.png"));
    action->setIconVisibleInMenu(false);
    action->setStatusTip(tr("Show/Hide Node Panel."));
    toolbarPanel->addAction(action);
}

void MilkMainWindow::createTimelinePanel()
{
    panelTimeline = new QDockWidget(tr("Timeline"), this);
    addDockWidget(Qt::BottomDockWidgetArea, panelTimeline);
    //panelTimeline->setVisible(false);
    QAction* action = panelTimeline->toggleViewAction();
    menuView->addAction(action);
    action->setIcon(QIcon(":/ui/action/timeline.png"));
    action->setIconVisibleInMenu(false);
    action->setStatusTip(tr("Show/Hide Timeline Panel."));
    toolbarPanel->addAction(action);
    timelineWidget = new TimelineWidget();
    panelTimeline->setWidget(timelineWidget);
}

void MilkMainWindow::createTargetPanel()
{
    panelTarget = new QDockWidget(tr("Target"), this);
    addDockWidget(Qt::TopDockWidgetArea, panelTarget);
    panelTarget->setVisible(false);
    QAction* action = panelTarget->toggleViewAction();
    menuView->addAction(action);
    action->setIcon(QIcon(":/ui/action/target.png"));
    action->setIconVisibleInMenu(false);
    action->setStatusTip(tr("Show/Hide Target Panel."));
    toolbarPanel->addAction(action);
}

void MilkMainWindow::createConsolePanel()
{
    panelConsole = new QDockWidget(tr("Console"), this);
    addDockWidget(Qt::BottomDockWidgetArea, panelConsole);
    panelConsole->setVisible(false);
    QAction* action = panelConsole->toggleViewAction();
    menuView->addAction(action);
    action->setIcon(QIcon(":/ui/action/console.png"));
    action->setIconVisibleInMenu(false);
    action->setStatusTip(tr("Show/Hide Console Panel."));
    toolbarPanel->addAction(action);
}

void MilkMainWindow::test()
{
//    timelineWidget->view()->scrollToPosition(50);
}
