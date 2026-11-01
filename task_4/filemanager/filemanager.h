#ifndef FILEMANAGER_H
#define FILEMANAGER_H

/**
 * @brief Process a single filemanager request and print its result to stdout.
 *
 * @param[in] option  Request code:
 *                    - 'c' - create the file @p filepath (existing file is not overwritten);
 *                    - 'd' - delete the file @p filepath;
 *                    - 'h' - print help message.
 *
 * @param[in] filepath  Absolute or relative path to the file. Required for 'c' and 'd'.
 *
 * @return Exit status code from <sysexits.h>.
 * @retval EX_OK        Request has been processed successfully.
 * @retval EX_USAGE     Unknown request or missing file path.
 * @retval EX_CANTCREAT File already exists or could not be created.
 * @retval EX_NOPERM    No permission to create or delete the file.
 * @retval EX_NOINPUT   File does not exist or could not be deleted.
 * @retval EX_IOERR     File has been created but could not be closed.
 */
[[nodiscard]] int fm_process_request(const int option, const char *const filepath);

#endif /* FILEMANAGER_H */
