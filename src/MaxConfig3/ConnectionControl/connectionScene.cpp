#include "connectionScene.h"

#include "app.h"
#include "mcconnection.h"
#include <LBL_Core/LBLConnection>
#include "arrowItem.h"
#include "Utils/correctdatahelper.h"
#include "Core/icore.h"

#include <QDebug>
#include <QGraphicsView>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QMessageBox>

ConnectionDiagramScene *ConnectionDiagramScene::s_connectionDiagramScene = nullptr;

ConnectionDiagramScene::ConnectionDiagramScene(QObject *parent /*= nullptr*/) : QGraphicsScene(parent)
{
	m_mode = SceneEdit;
	setSceneRect(0, 0, SHRT_MAX, SHRT_MAX);
}

void ConnectionDiagramScene::creatConnectionDiagramScene(QObject *parent)
{
	s_connectionDiagramScene = new ConnectionDiagramScene(parent);
}

ConnectionDiagramScene *ConnectionDiagramScene::instance()
{
	if (!s_connectionDiagramScene)
	{
		QSharedPointer<ConnectionDiagramScene> p(new ConnectionDiagramScene(Core::ICore::mainWindow()));
		s_connectionDiagramScene = p.get();
	}
	return s_connectionDiagramScene;
}

void ConnectionDiagramScene::setOperatPort(int port)
{
	m_curPort = port;
}

int ConnectionDiagramScene::operatPort() const
{
	return m_curPort;
}

void ConnectionDiagramScene::setColumnCount(int col)
{
	if (m_colCount != col)
	{
		m_colCount = col;
		prepareModuleItem();
		emit sig_connectionSettingChanged();
	}
}

int ConnectionDiagramScene::columnCount() const
{
	return m_colCount;
}

void ConnectionDiagramScene::setRowCount(int row)
{
	if (m_rowCount != row)
	{
		m_rowCount = row;
		prepareModuleItem();
		emit sig_connectionSettingChanged();
	}
}

int ConnectionDiagramScene::rowCount() const
{
	return m_rowCount;
}

void ConnectionDiagramScene::setModuleWidth(int width)
{
	if (m_moduleWidth != width)
	{
		m_moduleWidth = width;
		prepareModuleItem();
		emit sig_connectionSettingChanged();
	}
}

int ConnectionDiagramScene::moduleWidth() const
{
	return m_moduleWidth;
}

void ConnectionDiagramScene::setModuleHeight(int height)
{
	if (m_moduleHeight != height)
	{
		m_moduleHeight = height;
		prepareModuleItem();
		emit sig_connectionSettingChanged();
	}
}

int ConnectionDiagramScene::moduleHeight() const
{
	return m_moduleHeight;
}

bool ConnectionDiagramScene::addItemConnection(ModuleItem *startItem, ModuleItem *endItem /*= nullptr*/)
{
	if (!startItem)
	{
		return false;
	}
	if (endItem)
	{
		if (endItem->isConnected())
		{
			return false;
		}
	}
	QList<ModuleItem *> curItemList = m_allConnectModuleItem.value(operatPort());
	if (startItem->isConnected())
	{
		if (startItem->port() != operatPort())
		{
			return false;
		}
		if (startItem->isOrder(ModuleItem::O_End))
		{
			//尾部->队列中
			if (endItem)
			{
				setModuleItemStatus(startItem, ModuleItem::O_InQueen);
			}
		}
		else if (startItem->isOrder(ModuleItem::O_Start) && curItemList.size() == 1)
		{
			//头部->头部
			setModuleItemStatus(startItem, ModuleItem::O_Start);
		}
		else
		{
			//不允许连接
			return false;
		}
		if (endItem)
		{
			setModuleItemStatus(endItem, ModuleItem::O_End);
			addArrow(startItem, endItem);
			endItem->setPort(m_curPort);
			endItem->setModuleIndex(curItemList.size());
			m_allConnectModuleItem[operatPort()].append(endItem);
		}
	}
	else
	{
		if (curItemList.isEmpty())
		{
			//空->头部
			setModuleItemStatus(startItem, ModuleItem::O_Start);
			startItem->setPort(m_curPort);
			startItem->setModuleIndex(curItemList.size());
			m_allConnectModuleItem[operatPort()].append(startItem);
		}
		else
		{
			//原队列尾部->队列中
			if (!curItemList.back()->isOrder(ModuleItem::O_Start))
			{
				setModuleItemStatus(curItemList.back(), ModuleItem::O_InQueen);
			}
			if (endItem)
			{
				//添加尾部
				setModuleItemStatus(startItem, ModuleItem::O_InQueen);
				setModuleItemStatus(endItem, ModuleItem::O_End);
				addArrow(startItem, endItem);
				endItem->setPort(m_curPort);
			}
			else
			{
				//添加尾部
				setModuleItemStatus(startItem, ModuleItem::O_End);
			}
			addArrow(curItemList.back(), startItem);
			startItem->setPort(m_curPort);
			startItem->setModuleIndex(curItemList.size());
			m_allConnectModuleItem[operatPort()].append(startItem);
			if (endItem)
			{
				endItem->setModuleIndex(curItemList.size());
				m_allConnectModuleItem[operatPort()].append(endItem);
			}
		}
	}
	return true;
}

bool ConnectionDiagramScene::removeItemConnection(ModuleItem *item)
{
	if (!item)
	{
		return false;
	}
	if (!item->isConnected())
	{
		return false;
	}
	int port = item->port();
	QList<ModuleItem *> curItemList = m_allConnectModuleItem.value(port);
	if (!curItemList.contains(item))
	{
		return false;
	}
	int total = curItemList.size();
	int pos = curItemList.indexOf(item);
	for (int i = total; i > pos; --i)
	{
		curItemList.at(i - 1)->clearItem();
		m_allConnectModuleItem[port].removeLast();
	}
	if (!m_allConnectModuleItem[port].isEmpty())
	{
		setModuleItemStatus(m_allConnectModuleItem[port].last(), ModuleItem::O_End);
	}

	return true;
}

bool ConnectionDiagramScene::setModuleItemStatus(ModuleItem *item, ModuleItem::Order order)
{
	if (!item)
	{
		return false;
	}
	switch (order)
	{
	case ModuleItem::O_Null:
	{
		item->clearItem();
	}
	break;
	case ModuleItem::O_Start:
	{
		item->setOrder(ModuleItem::O_Start);
	}
	break;
	case ModuleItem::O_InQueen:
	{
		if (!item->isOrder(ModuleItem::O_Start))
		{
			item->setOrder(ModuleItem::O_InQueen);
		}
	}
	break;
	case ModuleItem::O_End:
	{
		if (!item->isOrder(ModuleItem::O_Start))
		{
			item->setOrder(ModuleItem::O_End);
		}
	}
	break;
	default:
		return false;
	}
	return true;
}

void ConnectionDiagramScene::clearModuleItem()
{
	for (auto item : m_allModuleItem)
	{
		item->removeArrows();
		removeItem(item);
		delete item;
		item = nullptr;
	}
	m_allModuleItem.clear();
	m_allConnectModuleItem.clear();
}

bool ConnectionDiagramScene::drawConnection(LBLConnection *connection)
{
	if (!connection)
	{
		qDebug() << "The Connection is nullptr.";
		return false;
	}
	this->setColumnCount(connection->col());
	this->setRowCount(connection->row());
	this->setModuleWidth(connection->moduleWidth());
	this->setModuleHeight(connection->moduleHeight());
	prepareModuleItem();
	int saveCurrentOptPort = operatPort();
	QList<LBLSPort> portList = connection->portList();
	for (int i = 0; i < portList.size(); ++i)
	{
		int portIndex = portList.at(i).index();
		QRectF portRect = portList.at(i).rect();
		setOperatPort(portIndex);
		QList<LBLSModule> moduleMap = portList.at(i).moduleList();
		for (auto it = moduleMap.begin(); it != moduleMap.end(); ++it)
		{
			QRectF itemRect(it->rect().topLeft() + portRect.topLeft(), it->rect().size());
			QList<QGraphicsItem *> curPtItem = items(itemRect.center());
			bool find = false;
			foreach (QGraphicsItem *item, curPtItem)
			{
				if (item->type() == ModuleItem::Type)
				{
					find = true;
					addItemConnection(qgraphicsitem_cast<ModuleItem *>(item));
					break;
				}
			}
			if (!find)
			{
				ModuleItem *item = new ModuleItem();
				item->setRect(itemRect);
				item->setZValue(1);
				addItem(item);
				m_allModuleItem.append(item);
				addItemConnection(qgraphicsitem_cast<ModuleItem *>(item));
			}
		}
	}
    setOperatPort(saveCurrentOptPort);
	emit sig_operatPortChanged(saveCurrentOptPort);
    sortItemToCorrectData();
    for (auto view : this->views())
	{
		view->fitInView(moduleBoundingRect(), Qt::KeepAspectRatio);
	}
    emit sig_connectionSettingChanged();
	return true;
}

bool ConnectionDiagramScene::creatConnection(LBLConnection *connection)
{
	if (!connection)
	{
		qDebug() << "The Connection is nullptr.";
		return false;
	}
	connection->resetJsonData();
	connection->setRow(rowCount());
	connection->setCol(columnCount());
	connection->setModuleHeight(moduleHeight());
	connection->setModuleWidth(moduleWidth());
	for (auto it = m_allConnectModuleItem.begin(); it != m_allConnectModuleItem.end(); ++it)
	{
		connection->addPort(LBLSPort(it.key(), QRectF()));
		LBLSPort &port = connection->port(it.key());

		QList<ModuleItem *> itemList = it.value();
		QRectF boundingRect;
		for (auto item : itemList)
		{
			boundingRect |= item->rect();
		}
		if (boundingRect.width() * boundingRect.height() > App::maxPortLoadPoint)
		{
			int opt = QMessageBox::question(NULL, tr("Question"),
											tr("Does the network port '%1' beyond the range, is there any?").arg(port.index() + 1),
											QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
			if (opt == QMessageBox::No)
			{
				qDebug() << QString("network port '%1' beyond the range, cancel send.").arg(port.index() + 1);
				return false;
			}
		}
		port.setRect(boundingRect);
		for (auto i = 0; i < itemList.size(); ++i)
		{
			ModuleItem *temp = itemList.at(i);
			port.addModule(LBLSModule(i, QRectF(temp->rect().topLeft() - port.rect().topLeft(), temp->rect().size())));
		}
	}
	return true;
}

bool ConnectionDiagramScene::drawPortConnection(int port)
{
	Q_UNUSED(port)
	return false;
}

void ConnectionDiagramScene::clearModuleConnection()
{
	for (auto it = m_allConnectModuleItem.begin(); it != m_allConnectModuleItem.end(); ++it)
	{
		if (!it->isEmpty())
		{
			removeItemConnection(it->front());
		}
	}
	m_allConnectModuleItem.clear();
}

QRectF ConnectionDiagramScene::moduleBoundingRect()
{
	QRectF boundingRect;
	for (auto item : m_allModuleItem)
	{
		boundingRect |= item->sceneBoundingRect();
	}
	return boundingRect;
}

void ConnectionDiagramScene::setSceneMode(Mode mode)
{
	m_mode = mode;
	switch (m_mode)
	{
	case ConnectionDiagramScene::SceneView:
		setInteractive(false);
		break;
	case ConnectionDiagramScene::SceneEdit:
		setInteractive(true);
		break;
	case ConnectionDiagramScene::Correct:
		setInteractive(true);
		break;
    case ConnectionDiagramScene::ModuleParam:
        setInteractive(true);
        break;
	default:
        setInteractive(true);
		break;
	}
	this->update();
}

bool ConnectionDiagramScene::isInteractive()
{
	return m_bInteractive;
}

void ConnectionDiagramScene::setInteractive(bool allow)
{
	m_bInteractive = allow;
}

bool ConnectionDiagramScene::isSceneMode(Mode mode)
{
	return m_mode == mode;
}

QList<QPair<CorrectDataHelper *, QString>> ConnectionDiagramScene::correctInfoList()
{
	QList<QPair<CorrectDataHelper *, QString>> list;
	for (auto it = m_allConnectModuleItem.begin(); it != m_allConnectModuleItem.end(); ++it)
	{
		QList<ModuleItem *> itemList = it.value();
		for (auto item : itemList)
		{
			QPair<CorrectDataHelper *, QString> pair = item->correctDataHelper()->correctFileInfo();
			if (!pair.second.isEmpty())
			{
				list.append(pair);
			}
		}
	}
	return list;
}

// 自定义 Scene
void ConnectionDiagramScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug() << "Custom scene clicked.";
	if (!m_bInteractive)
	{
		event->ignore();
		return;
	}
	if (event->button() == Qt::LeftButton)
	{
		switch (m_mode)
		{
		case ConnectionDiagramScene::SceneEdit:
		{
			QList<QGraphicsItem *> curPtItem = items(event->scenePos());
			for (auto it = curPtItem.begin(); it != curPtItem.end(); ++it)
			{
				if ((*it)->type() == ModuleItem::Type)
				{
					ModuleItem *p = qgraphicsitem_cast<ModuleItem *>((*it));
					addItemConnection(p);
					m_needDrawArrow = true;
					m_leftBtnDownPoint = event->scenePos();
					emit sig_operatPortChanged(p->port());
					break;
				}
			}
		}
		break;
		case ConnectionDiagramScene::Correct:
			break;
		default:
			break;
		}
	}
	else if (event->button() == Qt::RightButton)
	{
		switch (m_mode)
		{
		case ConnectionDiagramScene::SceneEdit:
		{
			// 检测光标下是否有 item
			foreach (QGraphicsItem *item, items(event->scenePos()))
			{
				if (item->type() == ModuleItem::Type)
				{
					ModuleItem *p = qgraphicsitem_cast<ModuleItem *>(item);
					int port = p->port();
					emit sig_operatPortChanged(port);
					removeItemConnection(p);
					if (m_allConnectModuleItem.contains(port) && m_allConnectModuleItem[port].isEmpty())
					{
						m_allConnectModuleItem.remove(port);
					}
					break;
				}
			}
		}
		break;
		case ConnectionDiagramScene::Correct:
			break;
		default:
			break;
		}
	}
	QGraphicsScene::mousePressEvent(event);
}

void ConnectionDiagramScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	// qDebug() << "Custom scene moved.";
	if (!m_bInteractive)
	{
		event->ignore();
		return;
	}
	if (m_needDrawArrow && !line)
	{
		QPointF point = event->scenePos();
		line = new QGraphicsLineItem(QLineF(m_leftBtnDownPoint,
											event->scenePos()));
		line->setPen(QPen(QColor("#0000ff"), 5));
		addItem(line);
	}
	if (line != 0)
	{
		QLineF newLine(line->line().p1(), event->scenePos());
		line->setLine(newLine);

		if (line != 0)
		{
			QList<QGraphicsItem *> startItems = items(line->line().p1());
			for (auto it = startItems.begin(); it != startItems.end();)
			{
				if ((*it)->type() != ModuleItem::Type)
				{
					it = startItems.erase(it);
					continue;
				}
				++it;
			}
			QList<QGraphicsItem *> endItems = items(line->line().p2());
			for (auto it = endItems.begin(); it != endItems.end();)
			{
				if ((*it)->type() != ModuleItem::Type)
				{
					it = endItems.erase(it);
					continue;
				}
				++it;
			}
			if (startItems.count() > 0 && endItems.count() > 0 &&
				startItems.first()->type() == ModuleItem::Type &&
				endItems.first()->type() == ModuleItem::Type &&
				startItems.first() != endItems.first())
			{
				ModuleItem *startItem = qgraphicsitem_cast<ModuleItem *>(startItems.first());
				ModuleItem *endItem = qgraphicsitem_cast<ModuleItem *>(endItems.first());

				if (!endItem->isConnected())
				{
					addItemConnection(startItem, endItem);
					QPointF test(0, 0);
					line->setLine(QLineF(endItem->scenePos() + test,
										 endItem->scenePos() + test));
				}
				// startItem->update(startItem->rect());
				// endItem->update(endItem->rect());
			}
		}
	}
	else
	{
		if (event->buttons() & Qt::LeftButton)
		{
			// qDebug() << "scene move line is nullptr with LeftButton.";
		}
		// qDebug() << "scene move line is nullptr.";
		QGraphicsScene::mouseMoveEvent(event);
	}
}

void ConnectionDiagramScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	if (!m_bInteractive)
	{
		event->ignore();
		return;
	}
	if (event->button() == Qt::LeftButton)
	{
		m_needDrawArrow = false;
	}
	if (line != 0)
	{
		removeItem(line);
		delete line;
		line = 0;
	}
	QGraphicsScene::mouseReleaseEvent(event);
}

void ConnectionDiagramScene::keyPressEvent(QKeyEvent *event)
{
	if (!m_bInteractive)
	{
		event->ignore();
		return;
	}
	if (event->key() == Qt::Key_Backspace || event->key() == Qt::Key_Delete)
	{
		// 移除所有选中的 items
        //qDebug() << "selected items " << selectedItems().size();
		if (!selectedItems().isEmpty())
		{
			QGraphicsItem *item = selectedItems().front();
			if (item->type() == Arrow::Type)
			{
				removeItemConnection(qgraphicsitem_cast<Arrow *>(item)->endItem());
			}
			else if (item->type() == ModuleItem::Type)
			{
				removeItemConnection(qgraphicsitem_cast<ModuleItem *>(item));
			}
		}
	}
	else
	{
		QGraphicsScene::keyPressEvent(event);
	}
}

void ConnectionDiagramScene::prepareModuleItem()
{
	clearModuleItem();
	for (int i = 0; i < m_colCount; i += 1)
	{
		for (int j = 0; j < m_rowCount; j += 1)
		{
			qreal x = (i * m_moduleWidth);
			qreal y = (j * m_moduleHeight);

			ModuleItem *item = new ModuleItem();
			item->setRect(QRectF(x, y, m_moduleWidth, m_moduleHeight));
			item->setZValue(1);
			/*QList<QGraphicsItem *> curPtItem = items(item->rect().center());
			bool find = false;
			foreach(QGraphicsItem *item, curPtItem) {
				if (item->type() == CustomItem::Type) {
					find = true;
					break;
				}
			}
			if (find) {
				continue;
			}*/
			addItem(item);
			m_allModuleItem.append(item);
		}
	}
	for (auto view : this->views())
	{
		view->fitInView(moduleBoundingRect(), Qt::KeepAspectRatio);
	}
}

bool ConnectionDiagramScene::addArrow(ModuleItem *startItem, ModuleItem *endItem)
{
	if (!startItem || !endItem)
	{
		return false;
	}
	if (startItem == endItem)
	{
		return false;
	}
	Arrow *arrow = new Arrow(startItem, endItem);
	startItem->addArrow(arrow);
	endItem->addArrow(arrow);
	arrow->setZValue(1.0);
	addItem(arrow);
	arrow->updatePosition();
	return true;
}

void ConnectionDiagramScene::sortItemToCorrectData()
{
	QList<ModuleItem *> allItem;
	for (auto &&port : m_allConnectModuleItem)
	{
		allItem.append(port);
	}
	qSort(allItem.begin(), allItem.end(), [](const ModuleItem *infoA, const ModuleItem *infoB)
		  { 
			  QRectF a = infoA->rect();
			  QRectF b = infoB->rect();

              if (a.x() < b.x()){
                  return true;
              }
          else if(a.x()==b.x()){
              return (a.y()<b.y());
		  } 
		  else{
			  return false;
          } });
    for(int index=0;index<allItem.count();++index){
        allItem.at(index)->setCorrectIndex(index+1);
    }
}

void ConnectionDiagramScene::setItemCorrectDataFilePath(const QMap<int, QString> &path)
{
    QList<ModuleItem *> allItem;
    for (auto &&port : m_allConnectModuleItem)
    {
        allItem.append(port);
    }
    for(auto &&item:allItem){
        if(path.contains(item->correctIndex())){
            item->correctDataHelper()->setCorrectFilePath(path[item->correctIndex()]);
        }
    }
}
