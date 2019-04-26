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

#ifndef DOUBLEFIELD_H
#define DOUBLEFIELD_H

#include "../effectfield.h"
#include "ui/labelslider.h"

class KeyframeDataChange;

/**
 * @brief The DoubleField class
 *
 * An EffectField derivative the produces number values (integer or floating-point) and uses a LabelSlider as its
 * visual representation.
 */
class DoubleField : public EffectField
{
  Q_OBJECT
public:
  /**
   * @brief Reimplementation of EffectField::EffectField().
   */
  DoubleField(NodeIO* parent);

  /**
   * @brief Get double value at timecode
   *
   * Convenience function. Equivalent to GetValueAt().toDouble()
   *
   * @param timecode
   *
   * Timecode to retrieve value at
   *
   * @return
   *
   * Double value at the set timecode
   */
  double GetDoubleAt(double timecode);

  /**
   * @brief Sets the minimum allowed number for the user to set to `minimum`.
   */
  void SetMinimum(double minimum);

  /**
   * @brief Sets the maximum allowed number for the user to set to `maximum`.
   */
  void SetMaximum(double maximum);

  /**
   * @brief Sets the default number for this field to `d`.
   */
  void SetDefault(double d);

  /**
   * @brief Sets the UI display type to a member of LabelSlider::DisplayType.
   */
  void SetDisplayType(LabelSlider::DisplayType type);

  /**
   * @brief For a timecode-based display type, sets the frame rate to be used for the displayed timecode
   *
   * \see SetDisplayType() and LabelSlider::SetFrameRate().
   */
  void SetFrameRate(const double& rate);

  /**
   * @brief Reimplementation of EffectField::ConvertStringToValue()
   */
  virtual QVariant ConvertStringToValue(const QString& s) override;

  /**
   * @brief Reimplementation of EffectField::ConvertValueToString()
   */
  virtual QString ConvertValueToString(const QVariant& v) override;

  /**
   * @brief Reimplementation of EffectField::CreateWidget()
   *
   * Creates and connects to a LabelSlider.
   */
  virtual QWidget* CreateWidget(QWidget *existing = nullptr) override;

  /**
   * @brief Reimplementation of EffectField::UpdateWidgetValue()
   */
  virtual void UpdateWidgetValue(QWidget* widget, double timecode) override;
signals:
  /**
   * @brief Signal emitted when the field's maximum value has changed
   *
   * This signal gets connected to any LabelSlider created from CreateWidget() so the maximum value is
   * always synchronized between them.
   *
   * Note: A connection is not made both ways as you should never manipulate a UI object created from
   * an EffectField directly. Always access data through the EffectField itself.
   *
   * \see SetMaximum()
   *
   * @param maximum
   *
   * The new maximum value.
   */
  void MaximumChanged(double maximum);

  /**
   * @brief Signal emitted when the field's minimum value has changed
   *
   * This signal gets connected to any LabelSlider created from CreateWidget() so the minimum value is
   * always synchronized between them.
   *
   * Note: A connection is not made both ways as you should never manipulate a UI object created from
   * an EffectField directly. Always access data through the EffectField itself.
   *
   * \see SetMinimum()
   *
   * @param minimum
   *
   * The new minimum value.
   */
  void MinimumChanged(double minimum);
private:
  /**
   * @brief Internal minimum value
   *
   * \see SetMinimum().
   */
  double min_;

  /**
   * @brief Internal maximum value
   *
   * \see SetMaximum().
   */
  double max_;

  /**
   * @brief Internal default value
   *
   * \see SetDefault().
   */
  double default_;

  /**
   * @brief Internal display type value
   *
   * \see SetDisplayType().
   */
  LabelSlider::DisplayType display_type_;

  /**
   * @brief Internal frame rate value
   *
   * \see SetFrameRate().
   */
  double frame_rate_;

  /**
   * @brief Internal value used to allow SetDefault() to set the value as well if none has been set
   *
   * Initialized to FALSE, then set to TRUE indefinitely whenever the value gets set on this field.
   */
  bool value_set_;

  /**
   * @brief An internal KeyframeDataChange undoable command
   *
   * This is stored to allow for the value to be changed by dragging without every single "step" being pushed to
   * the undo stack. Instead an undo command can be created at the start of a drag, and then pushed at the end
   * to make it one single undoable action.
   */
  KeyframeDataChange* kdc_;
private slots:
  /**
   * @brief Connected to EffectField::Changed() to ensure value_set_ gets set to TRUE whenever a value is set on this
   * field.
   */
  void ValueHasBeenSet();

  /**
   * @brief Internal function connected to any QWidget made from CreateWidget() to update the value based on user input
   *
   * @param b
   *
   * The current number value of the QWidget (LabelSlider in this case). Automatically set when this slot is connected
   * to the LabelSlider::valueChanged() signal.
   */
  void UpdateFromWidget(double d);
};

#endif // DOUBLEFIELD_H
