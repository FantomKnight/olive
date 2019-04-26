/***

  Olive - Non-Linear Video Editor
  Copyright (C) 2019  Olive Team

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.

***/

#ifndef TRANSFORMEFFECT_H
#define TRANSFORMEFFECT_H

#include "nodes/node.h"

class TransformEffect : public SubClipNode {
  Q_OBJECT
public:
  TransformEffect(Clip* c);

  virtual QString name() override;
  virtual QString id() override;
  virtual QString category() override;
  virtual QString description() override;
  virtual EffectType subclip_type() override;
  virtual olive::TrackType type() override;
  virtual NodePtr Create(Node *c) override;

  virtual void refresh() override;
  virtual void Process(double timecode) override;

  virtual void gizmo_draw(double timecode, GLTextureCoords& coords) override;

  NodeIO* matrix_output();

public slots:
  void toggle_uniform_scale(bool enabled);

private:
  Vec2Input* position;
  Vec2Input* scale;
  BoolInput* uniform_scale_field;
  DoubleInput* rotation;
  Vec2Input* anchor_point;
  DoubleInput* opacity;

  NodeIO* matrix_output_;

  EffectGizmo* top_left_gizmo;
  EffectGizmo* top_center_gizmo;
  EffectGizmo* top_right_gizmo;
  EffectGizmo* bottom_left_gizmo;
  EffectGizmo* bottom_center_gizmo;
  EffectGizmo* bottom_right_gizmo;
  EffectGizmo* left_center_gizmo;
  EffectGizmo* right_center_gizmo;
  EffectGizmo* anchor_gizmo;
  EffectGizmo* rotate_gizmo;
  EffectGizmo* rect_gizmo;
};

#endif // TRANSFORMEFFECT_H
