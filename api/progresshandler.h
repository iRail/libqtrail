//
// Configuration
//

// Include guard
#ifndef PROGRESSHANDLER_H
#define PROGRESSHANDLER_H

// Includes
#include <memory>
#include <QDebug>

namespace iRail
{
    class ProgressHandler
    {
    public:
        ProgressHandler()
        {
            mLevel = 0;
        }

        ~ProgressHandler()
        {
            if (mLevel)
                delete[] mProgress;
            mLevel = 0;
        }

        void enter()
        {
            unsigned int* tProgress = new unsigned int[mLevel+1];
            if (mLevel == 0)
                mTotalProgress = 0;
            else
            {
                memcpy(tProgress, mProgress, mLevel * sizeof(unsigned int));
                delete[] mProgress;
            }
            mProgress = tProgress;
            mLevel++;
        }

        void exit()
        {
            mTotalProgress += 100 - mProgress[mLevel-1];

            Q_ASSERT(mLevel > 0);
            mLevel--;
            if (mLevel == 0)
                delete[] mProgress;
            else
            {
                unsigned int* tProgress = new unsigned int[mLevel];
                memcpy(mProgress, tProgress, mLevel * sizeof(unsigned int));
                delete mProgress;
                mProgress = tProgress;
            }
        }

        unsigned int level()
        {
            return mLevel;
        }

        void setProgress(unsigned int iProgress)
        {
            mTotalProgress += iProgress - mProgress[mLevel-1];
        }

        unsigned int progress()
        {
            return mTotalProgress / mLevel;
        }

    private:
        unsigned int mLevel;
        unsigned int mTotalProgress;
        unsigned int* mProgress;
    };
}

#endif // PROGRESSHANDLER_H
