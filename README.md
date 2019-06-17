# qt-creator
Qt Creator快速入门 第三版 霍亚飞编著

#### 解决中文乱码
```
#pragma execution_character_set("utf-8")
```

#### 数据模型 
重写函数
```
// 显示
int rowCount(const QModelIndex &parent = QModelIndex()) const;
QVariant data(const QModelIndex &index, int role) const;
QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

// 编辑
bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
Qt::ItemFlags flags(const QModelIndex &index) const;

// 插入删除
bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
```

#### 设置拖拽
```
listWidget->setSelectionMode(QAbstractItemView::SingleSelection);  // 单选
listWidget->setDragEnabled(true);                                  // 启用拖动
listWidget->viewport()->setAcceptDrops(true);                      // 接收拖放
listWidget->setDragDropMode(QAbstractItemView::InternalMove);      // 移动
```

#### 数据模型过滤
```
QStringListModel *listModel = new QStringListModel(list, this);
filterModel = new QSortFilterProxyModel(this);
filterModel->setSourceModel(listModel);
listView->setModel(filterModel);

QRegExp rx(ui->lineEdit->text()); // 过滤规则
filterModel->setFilterRegExp(rx);
```

#### 模型映射
```
mapper = new QDataWidgetMapper(this);
mapper->setModel(model);
mapper->addMapping(lineEdit, 0);
mapper->toFirst();
mapper->toPrevious();
mapper->toNext();
```
