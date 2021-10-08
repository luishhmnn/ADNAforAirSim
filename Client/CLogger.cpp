#include "pch.h"
#include "CLogger.h"
#include <chrono>


void CLogger::Create()
{
    CString logFileName, timestamp, fileHeader;
    
    // Open a new .csv file in write mode.
    timestamp = GetCurrentTimestamp();
    logFileName = _T(LOG_FILE_NAME) + timestamp + _T(LOG_FILE_EXTENSION);
    m_logFile.Open(logFileName, CFile::modeWrite | CFile::modeCreate);

    // Add the .csv header.
    fileHeader = _T("timestamp,resource,value\n");
    m_logFile.WriteString((LPCTSTR)fileHeader);
}


void CLogger::LogValue(CString resource, float value)
{
    CString line, timestamp;

    // Return, if no log file exists.
    if (m_logFile.m_hFile == CFile::hFileNull) return;

    // Create output string and write it.
    timestamp = GetCurrentTimestamp();
    line.Format(_T("%s,%s,%f\n"), (LPCTSTR)timestamp, (LPCTSTR)resource, value);
    m_logFile.WriteString((LPCTSTR)line);
}


CString CLogger::GetCurrentTimestamp()
{
    CString output;

    // Get milliseconds since epoch.
    auto start = std::chrono::system_clock::now();
    auto duration = start.time_since_epoch();
    __int64 millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
  
    // Convert to string.
    output.Format(_T("%I64d"), millis);

    return output;
}
