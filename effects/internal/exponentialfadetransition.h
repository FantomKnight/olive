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

#ifndef EXPONENTIALFADETRANSITION_H
#define EXPONENTIALFADETRANSITION_H

#include "effects/transition.h"

class ExponentialFadeTransition : public Transition {
public:
  ExponentialFadeTransition(Clip* c);

  virtual QString name() override;
  virtual QString id() override;
  virtual QString description() override;
  virtual EffectType subclip_type() override;
  virtual olive::TrackType type() override;
  virtual NodePtr Create(Clip *c) override;

  virtual void process_audio(double timecode_start,
                             double timecode_end,
                             float **samples,
                             int nb_samples,
                             int channel_count,
                             int subclip_type) override;
};

#endif // LINEARFADETRANSITION_H
