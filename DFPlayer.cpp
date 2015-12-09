
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <DFPlayer.h>

////////////////////////////
// Public Methods
////////////////////////////


DFPlayer::DFPlayer() {
}


DFPlayer::DFPlayer(SerialMode mode, int tx, int rx) {
  initialize(mode, tx, rx);
}


void DFPlayer::initialize(SerialMode mode, int tx, int rx) {
  serial_mode_ = mode;
  if(serial_mode_ == SOFTWARE) {
    // Software Serial
    software_serial_ = new SoftwareSerial(tx, rx);
    software_serial_->begin(9600);
  } else {
    // Use the Hardware Serial
    Serial.begin(9600);
  }
  
  delay(DFPLAYER_CMD_DELAY);
}













/*
void DFPlayer::play() {
  execute_cmd(0x01, 0, 0);
  delay(DFPLAYER_CMD_DELAY);
}


void DFPlayer::play(byte track, byte folder) {
  execute_cmd(0x0F, folder, track);
  delay(DFPLAYER_CMD_DELAY);
}


void DFPlayer::pause() {
  execute_cmd(0x0E, 0, 0);
  delay(DFPLAYER_CMD_DELAY);
}


byte DFPlayer::query_folders() {
  software_serial_->listen();
  execute_cmd(0x4F, 0 ,0);
  return read_cmd();
}


byte DFPlayer::query_tracks(byte folder) {
  software_serial_->listen();
  execute_cmd(0x4E, 0, folder);
  return read_cmd();
}


void DFPlayer::repeat(bool enable) {
  execute_cmd(0x19, 0, !enable);
  delay(DFPLAYER_CMD_DELAY);
}


void DFPlayer::reset() {
  execute_cmd(0x0C, 0, 0);
  delay(DFPLAYER_CMD_DELAY);
}


void DFPlayer::set_volume(byte volume) {
  execute_cmd(0x06, 0, volume);
  delay(DFPLAYER_CMD_DELAY);
}


void DFPlayer::stop() {
  execute_cmd(0x16, 0, 0);
  delay(DFPLAYER_CMD_DELAY);
}


void DFPlayer::unpause() {
  execute_cmd(0x0D, 0, 0);
  delay(DFPLAYER_CMD_DELAY);
}
*/


////////////////////////////
// Private Methods
////////////////////////////

void DFPlayer::execute_cmd(byte command, byte param1, byte param2) {
  // Calculate the command checksum
  word checksum = -(
    DFPLAYER_VERSION_BYTE +
    DFPLAYER_CMD_LEN_BYTE +
    command +
    DFPLAYER_NO_ACK_BYTE +
    param1 +
    param2
  );
  
  // Build the command
  byte cmd[10] = {
    DFPLAYER_START_BYTE,
    DFPLAYER_VERSION_BYTE,
    DFPLAYER_CMD_LEN_BYTE,
    command,
    DFPLAYER_NO_ACK_BYTE,
    param1,
    param2,
    highByte(checksum),
    lowByte(checksum),
    DFPLAYER_END_BYTE
  };
  
  // Send the Command
  for(int i=0; i < 10; i++) {
    serial_write(cmd[i]);
  }
}


int DFPlayer::read_cmd() {
  int result = 0;
  int timeout = DFPLAYER_READ_TIMEOUT;
  int i = 0;
  
  while(timeout-- > 0 && i < 10) {
    if(serial_available() > 0) {
      byte b = serial_read();
      i++;
      
      if (i == 7) {
        result = b;
      }
    } else {
      delay(1);
    }
  }
  
  return result;
}


int DFPlayer::serial_available() {
  if(serial_mode_ == SOFTWARE) {
    return software_serial_->available();
  } else {
    return Serial.available();
  }
}


byte DFPlayer::serial_read() {
  if(serial_mode_ == SOFTWARE) {
    return software_serial_->read();
  } else {
    return Serial.read();
  }
}


void DFPlayer::serial_write(byte b) {
  if(serial_mode_ == SOFTWARE) {
    software_serial_->write(b);
  } else {
    Serial.write(b);
  }
}
