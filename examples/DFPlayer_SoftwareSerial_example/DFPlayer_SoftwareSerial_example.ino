#include <DFPlayer.h>

static const int RX_PIN = 10;
static const int TX_PIN = 11;


DFPlayer dfplayer(SM_Software, RX_PIN, TX_PIN);

void setup () {
  dfplayer.play();
}


void loop () { 
}