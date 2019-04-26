#ifndef LABELWIDGET_H
#define LABELWIDGET_H

#include "effects/nodeio.h"

class LabelWidget : public NodeIO
{
public:
  LabelWidget(Node* parent, const QString& name, const QString& text);
};

#endif // LABELWIDGET_H
