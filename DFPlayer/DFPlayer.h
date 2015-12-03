#ifndef DFPlayer_h
#define DFPlayer_h

#include <Arduino.h>
#include <SoftwareSerial.h>

enum DFPlayerSerialMode {
  HARDWARE = 0,
  SOFTWARE = 1
};


class DFPlayer {
  public:
    DFPlayer();
    
    void initialize(DFPlayerSerialMode mode, int tx, int rx);
    
    void pause();
    
    void play();
    //void play(byte track);
    void play(byte track, byte folder);
    
    byte query_folders();
    
    byte query_tracks(byte folder);
    
    void repeat(bool enable);
    
    void reset();
    
    void set_volume(byte volume);
    
    void stop();
    
    void unpause();
    
  private:
    // Static Members
    static const byte DFPLAYER_START_BYTE   = 0x7E;
    static const byte DFPLAYER_VERSION_BYTE = 0xFF;
    static const byte DFPLAYER_CMD_LEN_BYTE = 0x06;
    static const byte DFPLAYER_NO_ACK_BYTE  = 0x00;
    static const byte DFPLAYER_ACK_BYTE     = 0x01;
    static const byte DFPLAYER_END_BYTE     = 0xEF;
    static const int  DFPLAYER_CMD_DELAY    = 250;
    
    // Members
    DFPlayerSerialMode serial_mode_;
    SoftwareSerial* software_serial_;
    
    // Methods
    void execute_cmd(byte command, byte param1, byte param2);
    byte read_cmd();
    void serial_write(byte b);
};


#endif
