#include <time.h>
#include <cstdarg>

#include <fmt/chrono.h>
#include <SDL_log.h>
#include "log.h"
#include "util.h"

namespace Impacto {

// TODO Color output in console?

// TODO configurable stream/file logging
static bool LoggingToConsole = false;
static bool LoggingToFile = false;

bool CheckLogConfig(LogLevel level, LogChannel channel) {
  bool any = false;
  if (LoggingToConsole && (level <= g_LogLevelConsole) &&
      (g_LogChannelsConsole & channel) != LogChannel::None) {
    any = true;
  }
  if (LoggingToFile && (level <= g_LogLevelFile) &&
      (g_LogChannelsFile & channel) != LogChannel::None) {
    any = true;
  }
  return any;
}

void ConsoleWrite(LogLevel level, std::string_view str) {
  assert(level > LogLevel::Off && level < LogLevel::Max);
  switch (level) {
    case LogLevel::Fatal:
      SDL_LogCritical(SDL_LOG_CATEGORY_APPLICATION, "%s", str.data());
      break;
    case LogLevel::Error:
      SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "%s", str.data());
      break;
    case LogLevel::Warning:
      SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "%s", str.data());
      break;
    case LogLevel::Info:
      SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "%s", str.data());
      break;
    case LogLevel::Debug:
      SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "%s", str.data());
      break;
    case LogLevel::Trace:
      SDL_LogVerbose(SDL_LOG_CATEGORY_APPLICATION, "%s", str.data());
      break;
    default:
      assert(false);
  }
}

void ImpLogImpl(LogLevel level, LogChannel channel, fmt::string_view format,
                fmt::format_args args, size_t tailSize) {
  constexpr size_t maxChannelSize = 16;
  constexpr size_t maxTimestampSize = 21;
  assert(level > LogLevel::Off && channel > LogChannel::None);
  const size_t lineBufferSize =
      maxChannelSize + maxTimestampSize + tailSize + 1;
  auto* line = static_cast<char*>(ImpStackAlloc(lineBufferSize));

  std::string_view channelStr = ChannelToString(channel);
  time_t timestamp = time(nullptr);
  auto tsFormat = fmt::format_to_n(
      line, maxTimestampSize, "[{:%Y-%m-%d %H:%M:%S}]", fmt::gmtime(timestamp));
  auto channelFormat =
      fmt::format_to_n(tsFormat.out, maxChannelSize, "[{}] ", channelStr);
  auto tailFormat =
      fmt::vformat_to_n(channelFormat.out, tailSize + 1, format, args);
  *tailFormat.out = '\0';

  ConsoleWrite(level, line);

  // TODO file
}

void LogSetFile(char* path) {
  assert(false);  // TODO
}

void LogSetConsole(bool enabled) {
  LoggingToConsole = enabled;
  SDL_LogSetPriority(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_VERBOSE);
}

#ifndef IMPACTO_DISABLE_OPENGL
void GLAPIENTRY LogGLMessageCallback(GLenum source, GLenum type, GLuint id,
                                     GLenum severity, GLsizei length,
                                     const GLchar* message,
                                     const void* userParam) {
  LogLevel level;
  switch (severity) {
    case GL_DEBUG_SEVERITY_HIGH_ARB:
      level = LogLevel::Error;
      break;
    case GL_DEBUG_SEVERITY_MEDIUM_ARB:
      level = LogLevel::Warning;
      break;
    case GL_DEBUG_SEVERITY_LOW_ARB:
    default:
      level = LogLevel::Info;
      break;
  }

  const char typeError[] = "Error";
  const char typeDeprecated[] = "DeprecatedBehaviour";
  const char typeUB[] = "UndefinedBehaviour";
  const char typePerf[] = "Performance";
  const char typePortability[] = "Portability";
  const char typeOther[] = "Other";

  const char* typeStr;
  switch (type) {
    case GL_DEBUG_TYPE_ERROR_ARB:
      typeStr = typeError;
      break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR_ARB:
      typeStr = typeDeprecated;
      break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR_ARB:
      typeStr = typeUB;
      break;
    case GL_DEBUG_TYPE_PERFORMANCE_ARB:
      typeStr = typePerf;
      break;
    case GL_DEBUG_TYPE_PORTABILITY_ARB:
      typeStr = typePortability;
      break;
    case GL_DEBUG_TYPE_OTHER_ARB:
    default:
      typeStr = typeOther;
      break;
  }

  const char sourceApi[] = "API";
  const char sourceSc[] = "ShaderCompiler";
  const char sourceWin[] = "WindowSystem";
  const char source3rdParty[] = "ThirdParty";
  const char sourceApplication[] = "Application";
  const char sourceOther[] = "Other";

  const char* sourceStr;
  switch (source) {
    case GL_DEBUG_SOURCE_API_ARB:
      sourceStr = sourceApi;
      break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER_ARB:
      sourceStr = sourceSc;
      break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM_ARB:
      sourceStr = sourceWin;
      break;
    case GL_DEBUG_SOURCE_THIRD_PARTY_ARB:
      sourceStr = source3rdParty;
      break;
    case GL_DEBUG_SOURCE_APPLICATION_ARB:
      sourceStr = sourceApplication;
      break;
    case GL_DEBUG_SOURCE_OTHER_ARB:
    default:
      sourceStr = sourceOther;
      break;
  }

  ImpLog(level, LogChannel::GL,
         "type={:s}, source={:s}, id={:d}, message: {:s}\n", typeStr, sourceStr,
         id, message);
}
#endif

}  // namespace Impacto