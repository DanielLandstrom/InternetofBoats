//void actOnIR(String IRstring);   

void actOnIR(String IRstring) { 

  // Roxcore remote control
  if      ( IRstring == String("3:0xF9C23D") ) { //3:0x4B9841BE" )){ 
    if (IRdebug) { Serial.println("Up"); }
    fan.on();
  }
  else if ( IRstring == String("3:0xF950AF") ) { //3:0x4B98C13E" )) { 
    if (IRdebug) { Serial.println("Down"); }
    fan.off();
  }
  else if ( IRstring == String("3:0xF9708F") ) {
    if (IRdebug) { Serial.println("Right"); }
    outlet.on();
  }
  else if ( IRstring == String("3:0xF9609F") ) {
    if (IRdebug) { Serial.println("Left"); }
    outlet.off();
  }    
  else if ( IRstring == String("3:0xF9EA15") ) {
    if (IRdebug) { Serial.println("Power"); }
  }
  else if ( IRstring == String("3:0xF9DA25") ) {
    if (IRdebug) { Serial.println("Mute"); }
  }
  else if ( IRstring == String("3:0xF958A7") ) {
    if (IRdebug) { Serial.println("Setup"); }
  }  
  else if ( IRstring == String("3:0xF9807F") ) {
    if (IRdebug) { Serial.println("TV System"); }
  }
  else if ( IRstring == String("3:0xF96897") ) {
    if (IRdebug) { Serial.println("Menu"); }
  }
  else if ( IRstring == String("3:0xF912ED") ) {
    if (IRdebug) { Serial.println("Subtitle"); }
  }
  else if ( IRstring == String("3:0xF9629D") ) {
    if (IRdebug) { Serial.println("Ins replay"); }
  }
  else if ( IRstring == String("3:0xF922DD") ) {
    if (IRdebug) { Serial.println("Zoom in"); }
  }
  else if ( IRstring == String("3:0xF9AA55") ) {
    if (IRdebug) { Serial.println("Select"); }
  }
  else if ( IRstring == String("3:0xF9A25D") ) {
    if (IRdebug) { Serial.println("CM Skip"); }
  }
  else if ( IRstring == String("3:0xF902FD") ) {
    if (IRdebug) { Serial.println("Zoom out"); }
  }
  else if ( IRstring == String("3:0xF9728D") ) {
    if (IRdebug) { Serial.println("Confirm"); }
  }
  else if ( IRstring == String("3:0xF95AA5") ) {
    if (IRdebug) { Serial.println("Edit"); }
  }
  else if ( IRstring == String("3:0xF9B24D") ) {
    if (IRdebug) { Serial.println("Slow"); }
  }
  else if ( IRstring == String("3:0xF94AB5") ) {
    if (IRdebug) { Serial.println("Info"); }
  }
  else if ( IRstring == String("3:0xF90AF5") ) {
    if (IRdebug) { Serial.println("Play/Pause"); }
  }
  else if ( IRstring == String("3:0xF9C837") ) {
    if (IRdebug) { Serial.println("Stop"); }
  }
  else if ( IRstring == String("3:0xF9E21D") ) {
    if (IRdebug) { Serial.println("Home"); }
  }
  else if ( IRstring == String("3:0xF9F20D") ) {
    if (IRdebug) { Serial.println("Return"); }
  }
  else if ( IRstring == String("3:0xF9C23D") ) {
    if (IRdebug) { Serial.println("Up"); }
  }
  else if ( IRstring == String("3:0xF9609F") ) {
    if (IRdebug) { Serial.println("Left"); }
  }
  else if ( IRstring == String("3:0xF940BF") ) {
    if (IRdebug) { Serial.println("Center"); }
  }
  else if ( IRstring == String("3:0xF9708F") ) {
    if (IRdebug) { Serial.println("Right"); }
  }
  else if ( IRstring == String("3:0xF950AF") ) {
    if (IRdebug) { Serial.println("Down"); }
  }
  else if ( IRstring == String("3:0xF9E817") ) {
    if (IRdebug) { Serial.println("Vol+"); }
    lantern.on();
  }
  else if ( IRstring == String("3:0xF92AD5") ) {
    if (IRdebug) { Serial.println("Vol-"); }
    lantern.off();
  }
  else if ( IRstring == String("3:0xF9F00F") ) {
    if (IRdebug) { Serial.println("Prev"); }
    decklight.off();
  }
  else if ( IRstring == String("3:0xF9D02F") ) {
    if (IRdebug) { Serial.println("Next"); }
    decklight.on();
  }
  else if ( IRstring == String("3:0xF9A05F") ) {
    if (IRdebug) { Serial.println("1"); }
  }
  else if ( IRstring == String("3:0xF9906F") ) {
    if (IRdebug) { Serial.println("2"); }
  }
  else if ( IRstring == String("3:0xF9A857") ) {
    if (IRdebug) { Serial.println("3"); }
  }
  else if ( IRstring == String("3:0xF9E01F") ) {
    if (IRdebug) { Serial.println("FF"); }
  }
  else if ( IRstring == String("3:0xF920DF") ) {
    if (IRdebug) { Serial.println("4"); }
  }
  else if ( IRstring == String("3:0xF910EF") ) {
    if (IRdebug) { Serial.println("5"); }
  }
  else if ( IRstring == String("3:0xF928D7") ) {
    if (IRdebug) { Serial.println("6"); }
  }
  else if ( IRstring == String("3:0xF9C03F") ) {
    if (IRdebug) { Serial.println("FR"); }
  }
  else if ( IRstring == String("3:0xF900FF") ) {
    if (IRdebug) { Serial.println("7"); }
  }
  else if ( IRstring == String("3:0xF908F7") ) {
    if (IRdebug) { Serial.println("8"); }
  }
  else if ( IRstring == String("3:0xF930CF") ) {
    if (IRdebug) { Serial.println("9"); }
  }
  else if ( IRstring == String("3:0xF9B04F") ) {
    if (IRdebug) { Serial.println("Goto"); }
  }
  else if ( IRstring == String("3:0xF91AE5") ) {
    if (IRdebug) { Serial.println("Repeat"); }
  }
  else if ( IRstring == String("3:0xF98877") ) {
    if (IRdebug) { Serial.println("0"); }
  }
  else if ( IRstring == String("3:0xF9926D") ) {
    if (IRdebug) { Serial.println("Audio"); }
  }
  else if ( IRstring == String("3:0xF96A95") ) {
    if (IRdebug) { Serial.println("Music"); }
  }


  // LTC Båtsterio fjärr
  if      ( IRstring == String("3:0xFF50AF") ) {
    if (IRdebug) { Serial.println("Mute"); }
  }
  else if ( IRstring == String("3:0xFF906F") ) {
    if (IRdebug) { Serial.println("On/Off"); }
  }
  else if ( IRstring == String("3:0xFFE01F") ) {
    if (IRdebug) { Serial.println("Prev"); }
  }
  else if ( IRstring == String("3:0xFF609F") ) {
    if (IRdebug) { Serial.println("Next"); }
  }
  else if ( IRstring == String("3:0xFF") ) {
    if (IRdebug) { Serial.println("Vol+"); }
  }
  else if ( IRstring == String("3:0xFF") ) {
    if (IRdebug) { Serial.println("Vol-"); }
  }
  else if ( IRstring == String("3:0xFF8877") ) {
    if (IRdebug) { Serial.println("Src"); }
  }
  else if ( IRstring == String("3:0xFF22DD") ) {
    if (IRdebug) { Serial.println("Audio"); }
  }

  // Linas Philips
  if      ( IRstring == String("1:0x8CA") ) {
    if (IRdebug) { Serial.println("Lina på!"); }
//    switchLightWhite(2, 5, true); 
  }
  else if ( IRstring == String("1:0x8CB") ) {
    if (IRdebug) { Serial.println("Lina av!"); }
//    switchLightWhite(2, 5, false); 
  }

} // end actOnIR();
