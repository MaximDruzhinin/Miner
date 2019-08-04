#ifndef LOGGER_H
#define LOGGER_H

#define LOG_ERROR(message) { \
    qDebug () << "(ERR)" << __FUNCTION__ << ":" << message; \
}

#endif // LOGGER_H
