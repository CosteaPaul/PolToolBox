#ifndef POLCOPY_H
#define POLCOPY_H

#include "QString"

class PolCopy
{
public:
    PolCopy();
    /**
      * @brief Copy specified file to server, as given in settings.
      * @arg localPath -    Complete path of file to copy.
      * @returns True is copy succeeded.
      */
    static bool copyToServer(QString localPath);

    /**
      * @brief Copy specified file from server to a local path.
      * @arg fileName -     Name of file to copy from server.
      * @arg localPath -    Local path to copy to.
      */
    static bool copyFromServer(QString fileName,QString localPath);
};

#endif // POLCOPY_H
