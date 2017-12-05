
void translateIR() // takes action based on IR code received

// describing Remote IR codes 

{

  switch(results.value)

  {
  case 0xFFA25D: Serial.println("POWER"); hardReset(); break;
  case 0xFFE21D: Serial.println("FUNC/STOP"); break;
  case 0xFF629D: Serial.println("VOL+"); if(!manualMode){
    switch(currentLevel) {
      case lowLight: currentLevel = 1;
      case medLight: currentLevel = 2;
      default: break;
    }
  }   break;
  case 0xFF22DD: Serial.println("FAST BACK");    break;
  case 0xFF02FD: Serial.println("PAUSE"); if (manualMode) { manualMode = false; resetShades(); }
                                          else manualMode = true; break;
  case 0xFFC23D: Serial.println("FAST FORWARD");   break;
  case 0xFFE01F: Serial.println("DOWN"); if(manualMode) for (int i = 0; i < 900; i++) Close();  break;
  case 0xFFA857: Serial.println("VOL-"); if(!manualMode){
    switch(currentLevel) {
      case highLight: currentLevel = 1;
      case medLight: currentLevel = 0;
      default: break;
    }
  }   break;
  case 0xFF906F: Serial.println("UP"); if(manualMode) for (int i = 0; i < 900; i++) Open();   break;
  case 0xFF9867: Serial.println("EQ");    break;
  case 0xFFB04F: Serial.println("ST/REPT");    break;
  case 0xFF6897: Serial.println("0");    break;
  case 0xFF30CF: Serial.println("1");    break;
  case 0xFF18E7: Serial.println("2");    break;
  case 0xFF7A85: Serial.println("3");    break;
  case 0xFF10EF: Serial.println("4");    break;
  case 0xFF38C7: Serial.println("5");    break;
  case 0xFF5AA5: Serial.println("6");    break;
  case 0xFF42BD: Serial.println("7");    break;
  case 0xFF4AB5: Serial.println("8");    break;
  case 0xFF52AD: Serial.println("9");    break;
  case 0xFFFFFFFF: Serial.println(" REPEAT");break;  

  default: 
    Serial.println(" other button   ");

  }// End Case

  delay(500); // Do not get immediate repeat


} //END translateIR
