#pragma once

#define LOG_FILE_NAME       "ADNAforAirSim_log"
#define LOG_FILE_EXTENSION  ".csv"

class CLogger
{
public:
    /**
     * @brief Creates a new file which is used for logging.
     * @param fname The name of the file with path and extension.
    */
    void Create();

    /**
     * Writes a new line to the log file, if a log file was created.
     * The format look as follows:
     * [timestamp (in ms)], [resource], [value]
     * 
     * @brief Writes a line to the log file.
     * @param resource The name of the resource which produced the value.
     * @param value The The value with was produced by a resource.
    */
    void LogValue(CString resource, float value);
private:
    CStdioFile m_logFile;
    CString GetCurrentTimestamp();
};
