#include "SemCtl.h"
#include <sys/types.h>;
#include <sys/ipc.h>;
#include <sys/sem.h>;
#include <errno.h>
#include <string.h>
#include <stdint.h>

SemCtl::SemCtl(void)
{
}


SemCtl::~SemCtl(void)
{
}

int SemCtl::Init(key_t key, int iSemLen)
{
    union semun unSem;
    struct semid_ds seminfo;
    if((m_iSemID = semget(key, iSemLen, IPC_CREAT | IPC_EXCL | 0666)) > -1)
    {
        //If not EXISTS
        unsigned short *pSemZero = NULL;
        pSemZero = new unsigned short[iSemLen];
        memset(pSemZero, 0, sizeof(pSemZero));
        unSem.array = pSemZero;
        if(semctl(m_iSemID, 0, SETALL, unSem) == -1)
        {
            delete[] pSemZero;
            return -1;
        }
        delete[] pSemZero;
    }
    else if(errno == EEXIST)
    {
        if((m_iSemID = semget(key, 0, 0666)) < 0 )
        {
            return -1;
        }
        unSem.buf = &seminfo;
        //Test if the seminfo is right.
        if(semctl(m_iSemID, 0, IPC_STAT, unSem) == -1)
        {
            return -2;
        }
        if(unSem.buf->sem_nsems != iSemLen)
        {
            return -3;
        }
    }
    m_iSemLen = iSemLen;
    return 0;
}

int SemCtl::SetSem(int iSem, int iVal)
{
    union semun unSem;
    unSem.val = iVal;
    //Test if the seminfo is right.
    return semctl(m_iSemID, iSem, SETVAL, unSem);
}


int SemCtl::GetSem(int iSem)
{
    //We do not check iSem, it must => 0 <= iSem < iSemLen.
    return semctl(m_iSemID, iSem, GETVAL);

}


int SemCtl::ModSem(int iSem, int iMod)
{
    struct sembuf arSemOP[1];
    arSemOP->sem_num = iSem;
    arSemOP->sem_op = iMod;
    arSemOP->sem_flg = SEM_UNDO;
    return semop(m_iSemID, arSemOP, 1);
}


