#ifndef NODEEDITOR_H
#define NODEEDITOR_H

#include <QGraphicsScene>

#include "effectspanel.h"
#include "ui/nodeview.h"
#include "ui/nodeui.h"
#include "ui/nodeedgeui.h"

class NodeEditor : public EffectsPanel {
  Q_OBJECT
public:
  NodeEditor(QWidget* parent = nullptr);
  virtual ~NodeEditor() override;

  virtual void Retranslate() override;

protected:
  virtual void LoadEvent() override;
  virtual void AboutToClearEvent() override;

private:
  QGraphicsScene scene_;
  NodeView view_;
  QWidget props_;
  QVector<NodeUI*> nodes_;
  QVector<NodeEdgeUI*> edges_;
  QVector<NodeIO*> connected_rows_;
  QVBoxLayout* prop_layout_;
  QVector<EffectUI*> nodes_open_in_props_;

  void ClearEdges();
  void LoadEdges();

  void ConnectRow(NodeIO* row);
  void DisconnectAllRows();

private slots:
  void ItemsChanged();
  void ReloadEdges();
  void ContextMenu();
  void UpdateNodeProperties();
};

#endif // NODEEDITOR_H
