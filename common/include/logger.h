//
// Created by Alex M on 7/7/25.
//

#ifndef ACC_LOGGER_H
#define ACC_LOGGER_H

#include <source_location>
#include <string>

namespace acc::logger {

class Logger {
public:
  enum class Level { Info, Warning, Error, Fatal };

  static void report(
      const std::string& message,
      Level level = Level::Error,
      const std::source_location& location = std::source_location::current());

};

// Helper functions for convenience
inline void
info(const std::string& message, const std::source_location& location = std::source_location::current()) {
  Logger::report(message, Logger::Level::Info, location);
}

inline void
warning(const std::string& message, const std::source_location& location = std::source_location::current()) {
  Logger::report(message, Logger::Level::Warning, location);
}

inline void error(const std::string& message, const std::source_location& location = std::source_location::current()) {
  Logger::report(message, Logger::Level::Error, location);
}

inline void fatal(const std::string& message, const std::source_location& location = std::source_location::current()) {
  Logger::report(message, Logger::Level::Fatal, location);
}
} // namespace acc::logger
#endif // ACC_LOGGER_H
