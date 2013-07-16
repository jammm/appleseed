
//
// This source file is part of appleseed.
// Visit http://appleseedhq.net/ for additional information and resources.
//
// This software is released under the MIT license.
//
// Copyright (c) 2010-2013 Francois Beaune, Jupiter Jazz Limited
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//

#ifndef APPLESEED_STUDIO_MAINWINDOW_RENDERING_RENDERSELECTIONHANDLER_H
#define APPLESEED_STUDIO_MAINWINDOW_RENDERING_RENDERSELECTIONHANDLER_H

// Qt headers.
#include <QObject>
#include <QPoint>

// Forward declarations.
namespace appleseed { namespace studio { class MouseCoordinatesTracker; } }
namespace appleseed { namespace studio { class RenderWidget; } }
class QEvent;
class QRect;
class QRubberBand;

namespace appleseed {
namespace studio {

class RenderSelectionHandler
  : public QObject
{
    Q_OBJECT

  public:
    RenderSelectionHandler(
        RenderWidget*                       render_widget,
        const MouseCoordinatesTracker&      mouse_tracker);

    ~RenderSelectionHandler();

    void set_enabled(const bool enabled);

  signals:
    void signal_render_selection(const QRect& rect);

  private:
    RenderWidget*                           m_render_widget;
    const MouseCoordinatesTracker&          m_mouse_tracker;
    bool                                    m_enabled;
    QRubberBand*                            m_rubber_band;
    QPoint                                  m_origin;

    virtual bool eventFilter(QObject* object, QEvent* event);
};

}       // namespace studio
}       // namespace appleseed

#endif  // !APPLESEED_STUDIO_MAINWINDOW_RENDERING_RENDERSELECTIONHANDLER_H
