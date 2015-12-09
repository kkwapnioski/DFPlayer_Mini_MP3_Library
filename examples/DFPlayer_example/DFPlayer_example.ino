#include <DFPlayer.h>

static const int TX_PIN = 10;
static const int RX_PIN = 11;

DFPlayer dfplayer(SOFTWARE, TX_PIN, RX_PIN);

void setup () {
  dfplayer.play();
}


void loop () { 
}