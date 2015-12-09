#include <DFPlayer.h>

static const int TX_PIN = 10;
static const int RX_PIN = 11;
DFPlayer* dfplayer;

void setup () {
  dfplayer = new DFPlayer(TX_PIN, RX_PIN);
  dfplayer->play();
}


//
void loop () { 
}
