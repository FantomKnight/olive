#ifndef TRACK_H
#define TRACK_H

#include <QVector>
#include <memory>

#include "nodes/node.h"
#include "tracktypes.h"
#include "undo/comboaction.h"
#include "timeline/selection.h"
#include "clip.h"

class Sequence;
class Transition;

namespace olive {
  namespace timeline {
    const int kGhostThickness = 2;
    const int kClipTextPadding = 3;

    /**
     * @brief Set default track sizes
     *
     * Olive has a few default constants used for adjusting track heights in the Timeline. For HiDPI, it makes
     * sense to multiply these by the current DPI scale. It uses a variable from QApplication to do this multiplication,
     * which means the QApplication instance needs to be instantiated before these are calculated. Therefore, call this
     * function ONCE after QApplication is created to multiply the track heights correctly.
     */
    void MultiplyTrackSizesByDPI();

    extern int kTrackDefaultHeight;
    extern int kTrackMinHeight;
    extern int kTrackHeightIncrement;

    extern int kTimelineLabelFixedWidth;
  }
}

class Track : public Node
{
  Q_OBJECT
public:
  Track(Sequence* p, olive::TrackType subclip_type);

  virtual NodePtr Create(Node *c) override;
  virtual NodePtr copy(Node* parent) override;

  Sequence* sequence();

  virtual olive::TrackType type() override;

  int height();
  void set_height(int h);

  virtual QString name() override;
  void SetName(const QString& s);

  virtual void AddChild(NodePtr child) override;
  virtual Node* AddChild(NodeType type) override;
  int ClipCount();
  ClipPtr GetClip(int i);
  void RemoveClip(int i);
  void RemoveClip(Clip* c);
  QVector<Clip*> GetAllClips();
  QVector<Clip*> GetSelectedClips(bool containing);
  ClipPtr GetClipObjectFromRawPtr(Clip* c);
  Clip* GetClipFromPoint(long point);
  bool ContainsClip(Clip* c);

  Track* Previous();
  Track* Next();
  Track* Sibling(int diff);

  int Index();

  bool IsClipSelected(int clip_index, bool containing = true);
  bool IsClipSelected(Clip* clip, bool containing = true);
  bool IsTransitionSelected(Transition* t);

  void DeleteArea(ComboAction *ca, const Selection& s);
  void DeleteArea(ComboAction *ca, long in, long out);

  void SelectArea(long in, long out);
  void SelectClip(Clip *c);
  void SelectAll();
  void SelectAtPoint(long point);
  void TidySelections();
  void ClearSelections();
  void DeselectArea(long in, long out);
  QVector<Selection> Selections();

  long GetEndFrame();

  bool IsEffectivelyMuted();
  bool IsMuted();
  bool IsSoloed();
  bool IsLocked();

public slots:
  void SetMuted(bool muted);
  void SetSoloed(bool soloed);
  void SetLocked(bool locked);

signals:
  void HeightChanged(int height);

private:
  olive::TrackType type_;
  int height_;
  QVector<Selection> selections_;

  bool muted_;
  bool soloed_;
  bool locked_;

  QString name_;
};

#endif // TRACK_H
