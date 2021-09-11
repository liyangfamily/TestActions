#pragma once
#include "moduleItem.h"

#include <QGraphicsScene>
#include <QSharedPointer>
#include <QPair>
#include <QList>

QT_BEGIN_NAMESPACE
class QGraphicsSceneMouseEvent;
class QKeyEvent;
class QMenu;
QT_END_NAMESPACE

class LBLConnection;
class CorrectDataHelper;
// 自定义 Scene
class ConnectionDiagramScene : public QGraphicsScene
{
    Q_OBJECT
public:
	enum Mode { SceneView, SceneEdit, Correct };
	ConnectionDiagramScene(QObject * parent = nullptr);

	static void creatConnectionDiagramScene(QObject * parent);
	static ConnectionDiagramScene* instance();

    //void setOperatPort(int port);
	int operatPort() const;
    //void setColumnCount(int col);
	int columnCount() const;
    //void setRowCount(int row);
	int rowCount() const;
    //void setModuleWidth(int width);
	int moduleWidth() const;
    //void setModuleHeight(int height);
	int moduleHeight() const;

	bool drawConnection(LBLConnection* connection);
	bool creatConnection(LBLConnection* connection);
	bool drawPortConnection(int port);
	void clearModuleConnection();

	QRectF moduleBoundingRect();

	bool isInteractive();
	void setInteractive(bool allow);
	bool isSceneMode(Mode mode);
	Mode sceneMode() {
		return m_mode;
	}

	QList<QPair<CorrectDataHelper*, QString>> correctInfoList();
signals:
    void sig_operatPortChanged(int port);
    void sig_connectionSettingChanged();
public slots:
    void setOperatPort(int port);
    void setColumnCount(int col);
    void setRowCount(int row);
    void setModuleWidth(int width);
    void setModuleHeight(int height);
	void setSceneMode(Mode mode); 

protected:
	void mousePressEvent(QGraphicsSceneMouseEvent *event);
	void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	void keyPressEvent(QKeyEvent *event);

private:
	bool addItemConnection(ModuleItem* startItem, ModuleItem* endItem = nullptr);
	bool removeItemConnection(ModuleItem* item);
	bool setModuleItemStatus(ModuleItem* item, ModuleItem::Order order);
	void clearModuleItem();
	void prepareModuleItem();
	bool addArrow(ModuleItem* startItem, ModuleItem* endItem);
	bool deleteArrow(ModuleItem* startItem, ModuleItem* endItem);
private:
	QMenu *m_ItemMenu;
	Mode m_mode;
	bool m_bInteractive = true;

	bool m_needDrawArrow = false;
	QPointF m_leftBtnDownPoint;
	QGraphicsLineItem *line = nullptr;

	int m_curPort = 0;
	int m_colCount = 0;
	int m_rowCount = 0;
	int m_moduleWidth = 0;
	int m_moduleHeight = 0;
	QMap<int, QList<ModuleItem*>> m_allConnectModuleItem;
	QList<ModuleItem*> m_allModuleItem;
	static ConnectionDiagramScene* s_connectionDiagramScene;
};
