#include "renderer.h"

#include "../profile/game.h"

#ifndef IMPACTO_DISABLE_OPENGL
#include "opengl/renderer.h"
#endif
#ifndef IMPACTO_DISABLE_VULKAN
#include "vulkan/renderer.h"
#endif
#ifndef IMPACTO_DISABLE_DX9
#include "dx9/renderer.h"
#endif

namespace Impacto {

void InitRenderer() {
  switch (Profile::ActiveRenderer) {
#ifndef IMPACTO_DISABLE_OPENGL
    case RendererType::OpenGL:
      Renderer = new OpenGL::Renderer();
      break;
#endif
#ifndef IMPACTO_DISABLE_VULKAN
    case RendererType::Vulkan:
      Renderer = new Vulkan::Renderer();
      break;
#endif
#ifndef IMPACTO_DISABLE_DX9
    case RendererType::DirectX9:
      Renderer = new DirectX9::Renderer();
      break;
#endif
    default:
      ImpLog(LogLevel::Error, LogChannel::Render,
             "Unknown or unsupported renderer selected!\n");
      exit(1);
  }

  Renderer->Init();
}

void BaseRenderer::DrawSprite(Sprite const& sprite, RectF const& dest,
                              glm::vec4 tint, float angle, bool inverted) {
  std::array<glm::vec4, 4> tints = {tint, tint, tint, tint};
  DrawSprite(sprite, CornersQuad(dest), tints, angle, inverted);
}

void BaseRenderer::DrawSprite(Sprite const& sprite, glm::vec2 topLeft,
                              glm::vec4 tint, glm::vec2 scale, float angle,
                              bool inverted) {
  RectF scaledDest(topLeft.x, topLeft.y,
                   scale.x * sprite.Bounds.Width * sprite.BaseScale.x,
                   scale.y * sprite.Bounds.Height * sprite.BaseScale.y);
  DrawSprite(sprite, scaledDest, tint, angle, inverted);
}

void BaseRenderer::DrawCCMessageBox(Sprite const& sprite, Sprite const& mask,
                                    glm::vec2 topLeft, glm::vec4 tint,
                                    int alpha, int fadeRange, float effectCt,
                                    glm::vec2 scale) {
  RectF scaledDest(topLeft.x, topLeft.y,
                   scale.x * sprite.Bounds.Width * sprite.BaseScale.x,
                   scale.y * sprite.Bounds.Height * sprite.BaseScale.y);
  DrawCCMessageBox(sprite, mask, scaledDest, tint, alpha, fadeRange, effectCt);
}

void BaseRenderer::DrawSprite3DRotated(Sprite const& sprite, glm::vec2 topLeft,
                                       float depth, glm::vec2 vanishingPoint,
                                       bool stayInScreen, glm::quat rot,
                                       glm::vec4 tint, glm::vec2 scale,
                                       bool inverted) {
  RectF scaledDest(topLeft.x, topLeft.y,
                   scale.x * sprite.Bounds.Width * sprite.BaseScale.x,
                   scale.y * sprite.Bounds.Height * sprite.BaseScale.y);
  DrawSprite3DRotated(sprite, scaledDest, depth, vanishingPoint, stayInScreen,
                      rot, tint, inverted);
}

void BaseRenderer::DrawProcessedText(std::span<const ProcessedTextGlyph> text,
                                     Font* font, float opacity,
                                     RendererOutlineMode outlineMode,
                                     bool smoothstepGlyphOpacity,
                                     SpriteSheet* maskedSheet) {
  switch (font->Type) {
    case FontType::Basic:
      DrawProcessedText_BasicFont(text, (BasicFont*)font, opacity, outlineMode,
                                  smoothstepGlyphOpacity, opacity, maskedSheet);
      break;
    case FontType::LB: {
      DrawProcessedText_LBFont(text, (LBFont*)font, opacity, outlineMode,
                               smoothstepGlyphOpacity, opacity, maskedSheet);
    }
  }
}

void BaseRenderer::DrawProcessedText(std::span<const ProcessedTextGlyph> text,
                                     Font* font, float opacity,
                                     float outlineOpacity,
                                     RendererOutlineMode outlineMode,
                                     bool smoothstepGlyphOpacity,
                                     SpriteSheet* maskedSheet) {
  switch (font->Type) {
    case FontType::Basic:
      DrawProcessedText_BasicFont(text, (BasicFont*)font, opacity, outlineMode,
                                  smoothstepGlyphOpacity, outlineOpacity,
                                  maskedSheet);
      break;
    case FontType::LB: {
      DrawProcessedText_LBFont(text, (LBFont*)font, opacity, outlineMode,
                               smoothstepGlyphOpacity, outlineOpacity,
                               maskedSheet);
    }
  }
}

void BaseRenderer::DrawVideoTexture(YUVFrame* tex, glm::vec2 topLeft,
                                    glm::vec4 tint, glm::vec2 scale,
                                    float angle, bool alphaVideo) {
  RectF scaledDest(topLeft.x, topLeft.y, scale.x * tex->Width,
                   scale.y * tex->Height);
  DrawVideoTexture(tex, scaledDest, tint, angle, alphaVideo);
}

void BaseRenderer::DrawProcessedText_BasicFont(
    std::span<const ProcessedTextGlyph> text, BasicFont* font, float opacity,
    RendererOutlineMode outlineMode, bool smoothstepGlyphOpacity,
    float outlineOpacity, SpriteSheet* maskedSheet) {
  // cruddy mages outline
  if (outlineMode != RendererOutlineMode::None) {
    for (int i = 0; i < text.size(); i++) {
      glm::vec4 color = RgbIntToFloat(text[i].Colors.OutlineColor);
      color.a = outlineOpacity;
      if (smoothstepGlyphOpacity) {
        color.a *= glm::smoothstep(0.0f, 1.0f, text[i].Opacity);
      } else {
        color.a *= text[i].Opacity;
      }
      Sprite glyph = font->Glyph(text[i].CharId);
      RectF dest = text[i].DestRect;
      switch (outlineMode) {
        case RendererOutlineMode::Full:
          dest.X--;
          dest.Y--;
          if (maskedSheet) {
            Sprite mask;
            mask.Sheet = *maskedSheet;
            mask.Bounds = dest;
            DrawMaskedSpriteOverlay(glyph, mask, dest, color, color.a * 255,
                                    256, false, 0, i == 0);
          } else {
            DrawSprite(glyph, dest, color);
          }
          dest.X++;
          dest.Y++;
          [[fallthrough]];
        case RendererOutlineMode::BottomRight:
          dest.X++;
          dest.Y++;
          if (maskedSheet) {
            Sprite mask;
            mask.Sheet = *maskedSheet;
            mask.Bounds = dest;
            DrawMaskedSpriteOverlay(glyph, mask, dest, color, color.a * 255,
                                    256, false, 0, i == 0);
          } else {
            DrawSprite(glyph, dest, color);
          }
          break;
        default:
          break;
      }
    }
  }

  for (int i = 0; i < text.size(); i++) {
    glm::vec4 color = RgbIntToFloat(text[i].Colors.TextColor);
    color.a = opacity;
    if (smoothstepGlyphOpacity) {
      color.a *= glm::smoothstep(0.0f, 1.0f, text[i].Opacity);
    } else {
      color.a *= text[i].Opacity;
    }
    if (maskedSheet) {
      Sprite mask;
      mask.Sheet = *maskedSheet;
      mask.Bounds = text[i].DestRect;
      DrawMaskedSpriteOverlay(font->Glyph(text[i].CharId), mask,
                              text[i].DestRect, color, color.a * 255, 256,
                              false, 0, false);
    } else {
      DrawSprite(font->Glyph(text[i].CharId), text[i].DestRect, color);
    }
  }
}

void BaseRenderer::DrawProcessedText_LBFont(
    std::span<const ProcessedTextGlyph> text, LBFont* font, float opacity,
    RendererOutlineMode outlineMode, bool smoothstepGlyphOpacity,
    float outlineOpacity, SpriteSheet* maskedSheet) {
  if (outlineMode != RendererOutlineMode::None) {
    for (int i = 0; i < text.size(); i++) {
      glm::vec4 color = RgbIntToFloat(text[i].Colors.OutlineColor);
      color.a = outlineOpacity;
      if (smoothstepGlyphOpacity) {
        color.a *= glm::smoothstep(0.0f, 1.0f, text[i].Opacity);
      } else {
        color.a *= text[i].Opacity;
      }

      float scaleX = text[i].DestRect.Height / font->BitmapEmWidth;
      float scaleY = text[i].DestRect.Height / font->BitmapEmHeight;
      RectF outlineDest;

      switch (outlineMode) {
        case RendererOutlineMode::Full:
          outlineDest =
              RectF(text[i].DestRect.X + scaleX * font->OutlineOffset.x,
                    text[i].DestRect.Y + scaleY * font->OutlineOffset.y,
                    scaleX * font->OutlineCellWidth,
                    scaleY * font->OutlineCellHeight);
          break;
        case RendererOutlineMode::BottomRight:
          outlineDest = RectF(
              text[i].DestRect.X + scaleX * (font->OutlineOffset.x * 3 / 4),
              text[i].DestRect.Y + scaleY * (font->OutlineOffset.y * 3 / 4),
              scaleX * (font->OutlineCellWidth + font->OutlineOffset.x / 2),
              scaleY * (font->OutlineCellHeight + font->OutlineOffset.y / 2));
          break;
        default:
          break;
      }
      if (maskedSheet) {
        Sprite mask;
        mask.Sheet = *maskedSheet;
        mask.Bounds = outlineDest;
        DrawMaskedSpriteOverlay(font->OutlineGlyph(text[i].CharId), mask,
                                outlineDest, color, color.a * 255, 256, false,
                                0, i == 0);
      } else {
        DrawSprite(font->OutlineGlyph(text[i].CharId), outlineDest, color);
      }
    }
  }

  for (int i = 0; i < text.size(); i++) {
    glm::vec4 color = RgbIntToFloat(text[i].Colors.TextColor);
    color.a = opacity;
    if (smoothstepGlyphOpacity) {
      color.a *= glm::smoothstep(0.0f, 1.0f, text[i].Opacity);
    } else {
      color.a *= text[i].Opacity;
    }

    float scaleX = text[i].DestRect.Height / font->BitmapEmWidth;
    float scaleY = text[i].DestRect.Height / font->BitmapEmHeight;

    RectF foregroundDest =
        RectF(text[i].DestRect.X + scaleX * font->ForegroundOffset.x,
              text[i].DestRect.Y + scaleY * font->ForegroundOffset.y,
              scaleX * font->CellWidth, scaleY * font->CellHeight);
    if (maskedSheet) {
      Sprite mask;
      mask.Sheet = *maskedSheet;
      mask.Bounds = foregroundDest;
      DrawMaskedSpriteOverlay(font->Glyph(text[i].CharId), mask, foregroundDest,
                              color, color.a * 255, 256, false, 0, false);
    } else {
      DrawSprite(font->Glyph(text[i].CharId), foregroundDest, color);
    }
  }
}
}  // namespace Impacto
