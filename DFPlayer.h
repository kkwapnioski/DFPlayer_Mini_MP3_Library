#ifndef DFPlayer_h
#define DFPlayer_h

#include <Arduino.h>
#include <SoftwareSerial.h>

// DFPlayer Module Commands
#define DFPLAYER_PLAY_NEXT          0x01
#define DFPLAYER_PLAY_PREVIOUS      0x02
#define DFPLAYER_PLAY_ROOT_TRACK    0x03
#define DFPLAYER_INCREASE_VOLUME    0x04
#define DFPLAYER_DECREASE_VOLUME    0x05
#define DFPLAYER_SPECIFY_VOLUME     0x06
#define DFPLAYER_SPECIFY_EQ         0x07  // 0:Normal / 1:Pop / 2:Rock / 3:Jazz / 4:Classic / 5:Bass
#define DFPLAYER_SINGLE_REPEAT      0x08  // 1-2999
#define DFPLAYER_PLAYBACK_DEVICE    0x09  // 0:USB / 1:SD
#define DFPLAYER_STANDBY            0x0A
#define DFPLAYER_RESET              0x0C
#define DFPLAYER_UNPAUSE            0x0D
#define DFPLAYER_PAUSE              0x0E
#define DFPLAYER_PLAY_FOLDER        0x0F  // 01-99 
#define DFPLAYER_ALL_REPEAT         0x11  // 0:Stop Repeat / 1:All Repeat
#define DFPLAYER_PLAY_MP3           0x12  // Play "/mp3" folder files
#define DFPLAYER_PLAY_AD            0x13  // Play "/advert" folder adds while saving current playback position
#define DFPLAYER_STOP_AD            0x15  // Stop playing ad and resume playback
#define DFPLAYER_STOP               0x16  // Stop Playback
#define DFPLAYER_FOLDER_REPEAT      0x17
#define DFPLAYER_PLAY_RANDOM        0x18
#define DFPLAYER_REPEAT_CURRENT     0x19
#define DFPLAYER_QUERY_STATUS       0x42
#define DFPLAYER_QUERY_VOLUME       0x43
#define DFPLAYER_QUERY_EQ           0x44
#define DFPLAYER_QUERY_USB_FILES    0x47
#define DFPLAYER_QUERY_SD_FILES     0x48
#define DFPLAYER_QUERY_USB_TRACK    0x4B
#define DFPLAYER_QUERY_SD_TRACK     0x4C
#define DFPLAYER_QUERY_FOLDER_FILES 0x4E
#define DFPLAYER_QUERY_FOLDERS      0x4F



enum SerialMode {
  HARDWARE = 0,
  SOFTWARE = 1
};


class DFPlayer {
  
  public:
    // Initialize
    DFPlayer();
    DFPlayer(SerialMode mode, int tx, int rx);
    void initialize(SerialMode mode, int tx, int rx);
    void reset();
    void standby();
    
    // Repeat
    void repeat(bool enable);
    
    
    // Volume
    void increase_volume();
    void descrease_volume();
    void set_volume(byte volume);
    int get_volume();
    
    // Playback
    void stop();
    void pause();
    void unpause();
    void play();
    void play(byte track);
    void play(byte track, byte folder);
    
    
    // Folders/Tracks
    byte query_folders();
    byte query_tracks(byte folder);
    
    
  private:
    // Static Members
    static const byte DFPLAYER_START_BYTE   = 0x7E;
    static const byte DFPLAYER_VERSION_BYTE = 0xFF;
    static const byte DFPLAYER_CMD_LEN_BYTE = 0x06;
    static const byte DFPLAYER_NO_ACK_BYTE  = 0x00;
    static const byte DFPLAYER_ACK_BYTE     = 0x01;
    static const byte DFPLAYER_END_BYTE     = 0xEF;
    static const int  DFPLAYER_CMD_DELAY    = 250;
    static const int  DFPLAYER_READ_TIMEOUT = 250;
    
    // Members
    SerialMode serial_mode_;
    SoftwareSerial* software_serial_;
    
    // Methods
    void execute_cmd(byte command, byte param1, byte param2);
    int read_cmd();
    int serial_available();
    byte serial_read();
    void serial_write(byte b);
    
};


#endif
