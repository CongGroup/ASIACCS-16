#ifndef __SEMCTL_H__
#define __SEMCTL_H__

#include <sys/sem.h>

class SemCtl
{
public:
    SemCtl(void);
    ~SemCtl(void);
    
    int Init(key_t key, int iSemLen);

    int SetSem(int iSem, int iVal);

    int GetSem(int iSem);

    int ModSem(int iSem, int iMod);

private:

    union semun {
       int val;                    /* value for SETVAL */
       struct semid_ds *buf;       /* buffer for IPC_STAT, IPC_SET */
       unsigned short int *array;  /* array for GETALL, SETALL */
       struct seminfo *__buf;      /* buffer for IPC_INFO */
    };

    int m_iSemID;
    int m_iSemLen;

};

#endif
