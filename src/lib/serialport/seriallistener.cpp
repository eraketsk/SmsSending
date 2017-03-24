#include "seriallistener.h"
//#include "src/logger/logger.h"

#ifdef __WINNT
#include "mem.h"
#include "winbase.h"
#include "memory.h"
#endif

#include <iostream>
#include <string>
#include <sstream>

namespace serial {

  using namespace std;
//==============================================================================
// Private class Port
//==============================================================================

  class SerialListener::Port {
    public:
      wstring _portName;
      int    _baudRate;
      int    _byteSize;
      int    _parity;
      int    _stopBits;

#ifdef __WINNT
      HANDLE _device;
#endif

      Port():_portName(L""), _baudRate(0), _byteSize(0), _parity(0), _stopBits(0) {}
      wstring portName() const { return _portName;}
      int     parity()   const { return _parity; }
      int     byteSize() const { return _byteSize; }
      int     stopBits() const { return _stopBits; }
      int     baudRate() const { return _baudRate; }

#ifdef __WINNT
      HANDLE device() { return _device; }
#endif
    };

  SerialListener::SerialListener()
    {
      _port = new SerialListener::Port;
      _bufferSize = 4096;
      _isOpened = false;
      _busy = false;
    }

//==============================================================================
// SerialListener::getStopBits
//==============================================================================

  int SerialListener::getStopBits(StopBits sb) {
      switch (sb) {
        case Sb_One:    return 0;
        case Sb_OneHalf:return   1;
        case Sb_Two:    return   2;
        };

      return 0;
    }

//==============================================================================
// SerialListener::getParity
//==============================================================================

  int SerialListener::getParity(Parity p) {
      switch (p) {
        case None:  return 0;
        case Odd:   return 1;
        case Even:  return 2;
        case Mark:  return 3;
        case Space: return 4;
        };

      return 0;
    }
//========================================================================================================
//  bool portIsAvailable()
//========================================================================================================

  bool SerialListener::portIsAvailable(const std::wstring &portName) {

      WCHAR pathBuff[1024];

#ifdef __WINNT

      std::wstring fullName = L"\\\\.\\" + portName;

      if(QueryDosDeviceW(fullName.c_str(), pathBuff, 1024)) {
          return true;
        }

#endif

      return false;
    }

//==============================================================================
// list<string> SerialListener::availablePorts()
//      return all existing serail ports
//==============================================================================
  list<wstring> SerialListener::availablePorts() {
      list<wstring> ports;

      WCHAR pathBuff[1024];

#ifdef __WINNT
      for(int i = 0; i < 255; ++i) {

          wstring portName;
          wstring fullName;

          wstringstream st(portName, wstringstream::in | wstringstream::out);
          st << L"COM" << i;
          st >> portName;
          fullName = L"\\\\.\\" + portName;

          if(!QueryDosDeviceW(portName.c_str(), pathBuff, 1024)) continue;

          ports.push_back(portName);
        }
#endif

      return ports;
    }

//==============================================================================
// open()
//      make connection to comm
//==============================================================================

  bool SerialListener::open(const std::wstring &name,
                            const int &baudRate,
                            const int &byteSize,
                            Parity parity,
                            StopBits bits) {

      close();

      _port->_portName  = name;
      _port->_baudRate  = baudRate;
      _port->_byteSize  = byteSize;
      _port->_parity    = getParity(parity);
      _port->_stopBits  = getStopBits(bits);

#ifdef __WINNT
      COMMTIMEOUTS CommTimeOuts = {0};
      DCB          Dcb = {0};

      _port->_portName = wstring(L"\\\\.\\") + name;
      //LOG_INFORMATIONAL(tr("Try connect to port: ") + _port->portName().c_str() +  tendl);
      _port->_device   = CreateFileW(_port->_portName.c_str(),
                                     GENERIC_READ | GENERIC_WRITE,
                                     0,
                                     NULL,
                                     OPEN_EXISTING,
                                     FILE_ATTRIBUTE_NORMAL | FILE_FLAG_OVERLAPPED,
                                     NULL);

      if(_port->_device == INVALID_HANDLE_VALUE) {
          if(GetLastError() == ERROR_FILE_NOT_FOUND) {
              //LOG_WARNING(tr("Port '") + name.c_str() + ("' does not exist") + endl);
            }
          else
            //LOG_ERROR(tr("Failed to open ComPort '") + name.c_str() + "'" + endl);

          return false;
        }

      Dcb.DCBlength = sizeof(DCB);

      if(!GetCommState(_port->device(), &Dcb)) {
          cout << "Error in GetCommState()";
          CloseHandle(_port->_device);
          return false;
        }

      cout << "Connect to port: " << _port->portName().c_str() << endl;
      cout << "BaudRate = " << _port->baudRate()  << endl;
      cout << "byteSize = " << _port->byteSize()  << endl;
      cout << "parity   = " << _port->parity()    << endl;
      cout << "stopBits = " << _port->stopBits()  << endl;

      Dcb.BaudRate     = _port->baudRate();
      Dcb.ByteSize     = _port->byteSize();
      Dcb.Parity       = _port->parity();
      Dcb.StopBits     = _port->stopBits();

      if(!SetCommState(_port->device(), &Dcb)) {
          //LOG_ERROR(tr("Error in SetCommState()"));
          CloseHandle(_port->_device);
          return false;
        }

      /* set up for overlapped I/O */
      CommTimeOuts.ReadIntervalTimeout         = 50;
      CommTimeOuts.ReadTotalTimeoutMultiplier  = 50;
      CommTimeOuts.ReadTotalTimeoutConstant    = 10;
      CommTimeOuts.WriteTotalTimeoutMultiplier = 50;
      CommTimeOuts.WriteTotalTimeoutConstant   = 10;

      if(!SetCommTimeouts(_port->device(), &CommTimeOuts)) {
          //LOG_ERROR(tr("Error in SetCommTimeouts()"));
          CloseHandle(_port->_device);
          return false;
        }
#endif

      return _isOpened = true;
    }


//==============================================================================
// SerialListener::~SerialListener()
//==============================================================================

  SerialListener::~SerialListener() {
      close();
      delete _port;
    }

//==============================================================================
// close()
//==============================================================================

  void SerialListener::close() {
      if(!_isOpened) return;

      _isOpened = false;

      //LOG_INFORMATIONAL(tr("Com port closed"));

      CloseHandle(_port->device());
    }

//==============================================================================
// read()
//      read data from comm
//==============================================================================
  string SerialListener::read() {
      if(!_isOpened) return 0;

      unsigned long Length;
      char*         pBuffer = NULL;

      _busy = true;

#ifdef __WINNT
      COMSTAT         ComStat    = {0};
      DWORD           ErrorFlags = 0;
      OVERLAPPED      osRead     = {0};
      DWORD           LReaded    = 0;


      /* only try to read number of bytes in queue */
      ClearCommError(_port->device(), &ErrorFlags, &ComStat);
      Length = ComStat.cbInQue;

      if(Length > 0) {
          pBuffer = new char[Length + 1];
          memset(pBuffer, 0, Length + 1);

          if(ReadFile(_port->device(), pBuffer, Length, &LReaded, &osRead) == FALSE) {
              Length = 0 ;
              ClearCommError(_port->device(), &ErrorFlags, &ComStat);
              if(ErrorFlags != 0) {

                  _busy = false;
                  cout << "\n Too many errors" << endl;
                  close();

                }
              return "";
            }
          else {
              Length = LReaded;
            }
        }
      else {
          Length = 0;
        }

#endif

      string result;

      if(LReaded && pBuffer) {
          pBuffer[LReaded] = 0;
          result = string(pBuffer);
          //cout << pBuffer << endl;
        }

      _busy = false;
      return result;
    }

//==============================================================================
// portName()
//==============================================================================
  std::wstring SerialListener::portName() const {
      return _port->portName();
    }

//==============================================================================
// write()
//==============================================================================
  bool SerialListener::write(const string &text) {
      if(!_isOpened) return false;

#ifdef __WINNT
      DWORD      BytesWritten = 0;
      OVERLAPPED osWrite      = {0};

      int E =GetLastError();

      BOOL result = WriteFile(_port->device(),
                              text.c_str(),
                              text.length(),
                              &BytesWritten,
                              &osWrite);
      if(result == FALSE)
        {
          E =GetLastError();
          if(E == ERROR_IO_PENDING) {
              GetOverlappedResult(_port->device(),&osWrite,&BytesWritten,true);
              return TRUE;
            }
          else return (false);
        }
#endif
      return (true);
    }

  } // namespace serial

