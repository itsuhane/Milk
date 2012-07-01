#include <QtGui>
#include "timelinewidget.h"
#include "timelinetree/timelinetreeconfig.h"

class ItemDelegate : public QStyledItemDelegate
{
public:
    QSize sizeHint (const QStyleOptionViewItem & option, const QModelIndex & index) const
    {
        Q_UNUSED(option);
        Q_UNUSED(index);
        return QSize(0,FRAME_HEIGHT);
    }
};

TimelineWidget::TimelineWidget(QWidget *parent) :
    QMainWindow(parent)
{
    setMinimumSize(480,160);

    createToolBar();
    createTimelineView();
}

void TimelineWidget::createToolBar()
{
    toolbar = addToolBar(tr("Timeline"));
    toolbar->setMovable(false);

    QWidget* spacer = new QWidget;
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    toolbar->addAction(QIcon(":/ui/action/rewind.png"), tr("Rewind"));
    toolbar->addAction(QIcon(":/ui/action/record.png"), tr("Record"));
    toolbar->addAction(QIcon(":/ui/action/play.png"), tr("Play"));
    toolbar->addAction(QIcon(":/ui/action/forward.png"), tr("Forward"));
    toolbar->addSeparator();
    toolbar->addAction(QIcon(":/ui/action/repeat.png"), tr("Repeat"));
    toolbar->addWidget(spacer);
    frameSpin = new QSpinBox;
    toolbar->addWidget(frameSpin);

    QWidget* rspacer = new QWidget;
    rspacer->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    rspacer->setMinimumWidth(8);
    rspacer->setMaximumWidth(8);
    toolbar->addWidget(rspacer);

}

void TimelineWidget::createTimelineView()
{
    TimelineTreeModel* model = new TimelineTreeModel();

    timelineTree = new QTreeView;
    timelineTree->setItemDelegate(new ItemDelegate);
    timelineTree->setFocusPolicy(Qt::NoFocus);
    timelineTree->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    timelineTree->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    timelineTree->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    timelineTree->header()->setMovable(false);
    timelineTree->setRootIsDecorated(false);
    timelineTree->setModel(model);
    for(int i=1;i<model->columnCount();++i)
        timelineTree->setColumnHidden(i, true);

    timelineTree->setMinimumWidth(160);
    timelineTree->setMaximumWidth(300);

    timelineView = new TimelineTreeView();
    timelineView->setModel(model);
    timelineView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    QSplitter* splitter = new QSplitter;

    splitter->addWidget(timelineTree);
    splitter->addWidget(timelineView);
    splitter->setCollapsible(1,false);
    splitter->setHandleWidth(2);
    setCentralWidget(splitter);

    connect(timelineTree->verticalScrollBar(), SIGNAL(valueChanged(int)), timelineView->verticalScrollBar(), SLOT(setValue(int)));
    connect(timelineView->verticalScrollBar(), SIGNAL(valueChanged(int)), timelineTree->verticalScrollBar(), SLOT(setValue(int)));
    connect(timelineTree, SIGNAL(expanded(QModelIndex)), timelineView, SLOT(expand(QModelIndex)));
    connect(timelineTree, SIGNAL(collapsed(QModelIndex)), timelineView, SLOT(collapse(QModelIndex)));
    connect(timelineView->ruler()->timeline(), SIGNAL(positionChanged(int)), frameSpin, SLOT(setValue(int)));
    connect(frameSpin, SIGNAL(valueChanged(int)), timelineView->ruler()->timeline(), SLOT(setPosition(int)));
}
