#ifndef SERIALLISTENER_H
#define SERIALLISTENER_H

#ifndef __LINUX__
#include <windows.h>
#endif
#include <list>
#include <string>

namespace serial {

class SerialListener
{
public:
    enum Parity { None, Odd, Even, Mark, Space };
    enum StopBits { Sb_One, Sb_OneHalf, Sb_Two };
    SerialListener();
    ~SerialListener();

    void setBufferSize(const int& size);

    bool open(const std::wstring& name,
              const int& baudRate = 9600,
              const int& byteSize = 8,
              Parity parity = None,
              StopBits bits = Sb_One);

    void close();
    bool isOpened() const { return _isOpened;}

    std::string             read();
    static std::list<std::wstring>  availablePorts();

    static bool portIsAvailable(const std::wstring& portName);

    bool write(const std::string& text);

    std::wstring portName() const;
protected:
    int getParity(Parity p);
    int getStopBits(StopBits sb);
private:
    class Port;
    Port* _port;
    bool  _isOpened;
    int   _bufferSize;
    bool  _busy;
};
}//namespace serial
#endif // SERIALLISTENER_H
