#ifndef FILEMANAGER_H
#define FILEMANAGER_H

/**
 * @brief Process a single filemanager request and print its result to stdout.
 *
 * @param[in] req  Request code:
 *                 - 'c' - create (or truncate) the file @p arg;
 *                 - 'd' - delete the file @p arg;
 *                 - 'h' - print help message.
 *
 * @param[in] arg  Absolute or relative path to the file. Required for 'c' and 'd'.
 *
 * @return Exit status code from <sysexits.h>.
 * @retval EX_OK        Request has been processed successfully.
 * @retval EX_USAGE     Unknown request or missing file path.
 * @retval EX_CANTCREAT File could not be created.
 * @retval EX_NOINPUT   File could not be deleted.
 * @retval EX_IOERR     File has been created but could not be closed.
 */
int fm_process_request(const int req, const char *const arg);

#endif /* FILEMANAGER_H */
