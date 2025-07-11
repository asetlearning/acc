//
// Created by Alex M on 7/7/25.
//

#include "logger.h"

#include <iostream>

namespace acc::logger {

void Logger::report(const std::string& message, Level level, const std::source_location& location) {
  switch (level) {
    case Level::Info:
      std::cerr << "INFO: ";
      break;
    case Level::Warning:
      std::cerr << "WARNING: ";
      break;
    case Level::Error:
      std::cerr << "ERROR: ";
      break;
    case Level::Fatal:
      std::cerr << "FATAL ERROR: ";
      break;
  }

  std::cerr << message << "\n"
            << "  at " << location.file_name() << ":" << location.line() << " in " << location.function_name()
            << std::endl;

  if (level == Level::Fatal) {
    exit(1);
  }
}
} // namespace acc::logger