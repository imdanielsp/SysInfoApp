#include "SysInfoWindowsImpl.h"

#include <windows.h>

SysInfoWindowsImpl::SysInfoWindowsImpl() :
    SysInfo()
{

}

double SysInfoWindowsImpl::memoryUsed()
{
    MEMORYSTATUSEX memoryStatus;
    memoryStatus.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memoryStatus);
    qulonglong memoryPhysicalUsed =
            memoryStatus.ullTotalPhys - memoryStatus.ullAvailPhys;
    return (double) memoryPhysicalUsed /
            (double)memoryStatus.ullTotalPhys *100.0;
}

void SysInfoWindowsImpl::init()
{
    mCputLoadLastValues = cpuRawData();
}

QVector<qulonglong> SysInfoWindowsImpl::cpuRawData()
{
    FILETIME idleTime;
    FILETIME kernelTime;
    FILETIME userTime;

    GetSystemTimes(&idleTime, &kernelTime, &userTime);

    QVector<qulonglong> rawData;

    rawData.append(convertFileTime(idleTime));
    rawData.append(convertFileTime(kernelTime));
    rawData.append(convertFielTime(userTime));

    return rawData;
}

qulonglong SysInfoWindowsImpl::convertFile(const FILETIME &filetime) const
{
    ULARGE_INTEGER largeInteger;
    largeInteger.LowPart = filetime.dwLowDateTime;
    largeInteger.HighPart = filetime.dwHighDateTime;
    return largeInteger.QuadPart;
}

double SysInfoWindowsImpl::cpuLoadAverage()
{
    QVector<qulonglong> firstSample = mCpuLoadLastValues;
    QVector<qulonglong> secondSample = cpuRawData();
    mCputLoadLastValues = secondSample;

    qulonglog currentIdle = secondSample[0] - firstSample[0];
    qulonglog currentKernel = secondSample[1] - firstSample[1];
    qulonglog currentUser = secondSample[2] - firstSample[2];
    qulonglog currentSystem = currentKernel + currentUser;

    double percent = (currentSystem - currentIdle) * 100.0 /
            currentSystem;
    return qBound(0.0, percent, 100.0);
}
