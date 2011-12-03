#pragma once

#include "../geometry/screenbase.hpp"

#include "../base/mutex.hpp"

#include "../std/function.hpp"
#include "../std/list.hpp"
#include "../std/shared_ptr.hpp"

namespace yg
{
  class InfoLayer;

  namespace gl
  {
    class BaseTexture;
    class RenderBuffer;

    class RenderState
    {
    public:

      typedef function<void()> invalidateFn;

      /// Already rendered model params
      /// @{
      /// Bitmap
      shared_ptr<BaseTexture> m_actualTarget;
      /// Information layer
      shared_ptr<yg::InfoLayer> m_actualInfoLayer;
      /// Screen parameters
      ScreenBase m_actualScreen;
      /// Empty-model flag of the actual target
      bool m_isEmptyModelActual;
      /// @}

      /// In-Progress rendering operation params
      /// @{
      /// Screen of the rendering operation in progress.
      ScreenBase m_currentScreen;
      /// information layer
      shared_ptr<yg::InfoLayer> m_currentInfoLayer;
      /// at least one backBuffer layer
      shared_ptr<BaseTexture> m_backBuffer;
      /// depth buffer used for rendering
      shared_ptr<RenderBuffer> m_depthBuffer;
      /// Duration of the rendering operation
      double m_duration;
      /// Empty-model flag of the current rendering operation
      bool m_isEmptyModelCurrent;
      /// @}

      shared_ptr<BaseTexture> m_shadowActualTarget;
      shared_ptr<BaseTexture> m_shadowBackBuffer;

      /// Surface height and width.
      unsigned int m_surfaceWidth;
      unsigned int m_surfaceHeight;

      /// Texture height and width.
      unsigned int m_textureWidth;
      unsigned int m_textureHeight;

      /// Have this state been resized?
      bool m_isResized;
      /// RepaintAll flag
      bool m_doRepaintAll;

      mutable shared_ptr<threads::Mutex> m_mutex;

      list<invalidateFn> m_invalidateFns;

      RenderState();

      bool isPanning() const;

      void copyTo(RenderState & s) const;

      void invalidate();

      void addInvalidateFn(invalidateFn fn);

      void onSize(size_t w, size_t h);

      m2::PointU const coordSystemShift(bool doLock = false) const;
    };
  }
}
