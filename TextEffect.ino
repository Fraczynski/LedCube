uint8_t charCounter = 0;
uint8_t charPosition = 0;

uint8_t characters[37][8] = {
  {0x3C, 0x7E, 0x66, 0x6E, 0x76, 0x66, 0x7E, 0x3C}, //0
  {0x18, 0x38, 0x38, 0x18, 0x18, 0x18, 0x18, 0x7E}, //1
  {0x3C, 0x7E, 0x46, 0x0C, 0x30, 0x62, 0x7E, 0x3C}, //2
  {0x3C, 0x66, 0x06, 0x1C, 0x1C, 0x06, 0x66, 0x3C}, //3
  {0x0C, 0x1C, 0x2C, 0x4C, 0x7E, 0x7E, 0x0C, 0x0C}, //4
  {0x3C, 0x60, 0x60, 0x7C, 0x06, 0x06, 0x66, 0x3C}, //5
  {0x3C, 0x62, 0x60, 0x7C, 0x66, 0x66, 0x66, 0x3C}, //6
  {0x7E, 0x66, 0x06, 0x0C, 0x18, 0x18, 0x18, 0x18}, //7
  {0x3C, 0x66, 0x66, 0x3C, 0x66, 0x66, 0x66, 0x3C}, //8
  {0x3C, 0x66, 0x66, 0x66, 0x3E, 0x06, 0x46, 0x3C}, //9
  {0x18, 0x3C, 0x7E, 0x66, 0x66, 0x7E, 0x66, 0x66}, //A
  {0x7C, 0x66, 0x66, 0x7C, 0x7C, 0x66, 0x66, 0x7C}, //B
  {0x1C, 0x36, 0x60, 0x60, 0x60, 0x60, 0x36, 0x1C}, //C
  {0x78, 0x7C, 0x66, 0x66, 0x66, 0x66, 0x7C, 0x78}, //D
  {0x7E, 0x60, 0x60, 0x7C, 0x7C, 0x60, 0x60, 0x7E}, //E
  {0x7E, 0x7E, 0x60, 0x60, 0x7C, 0x60, 0x60, 0x60}, //F
  {0x3C, 0x66, 0x60, 0x60, 0x60, 0x6E, 0x66, 0x3C}, //G
  {0x66, 0x66, 0x66, 0x7E, 0x7E, 0x66, 0x66, 0x66}, //H
  {0x7E, 0x7E, 0x18, 0x18, 0x18, 0x18, 0x7E, 0x7E}, //I
  {0x7E, 0x7E, 0x0C, 0x0C, 0x0C, 0x6C, 0x7C, 0x38}, //J
  {0x66, 0x6C, 0x78, 0x70, 0x78, 0x6C, 0x66, 0x62}, //K
  {0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x7E, 0x7E}, //L
  {0xC3, 0xE7, 0xFF, 0xDB, 0xC3, 0xC3, 0xC3, 0xC3}, //M
  {0xC3, 0xE3, 0xF3, 0xDB, 0xCF, 0xC7, 0xC3, 0xC3}, //N
  {0x3C, 0x7E, 0x66, 0x66, 0x66, 0x66, 0x7E, 0x3C}, //O
  {0x7C, 0x66, 0x66, 0x66, 0x7C, 0x60, 0x60, 0x60}, //P
  {0x3C, 0x66, 0x66, 0x66, 0x66, 0x6E, 0x3C, 0x06}, //Q
  {0x7C, 0x7E, 0x66, 0x7C, 0x78, 0x6C, 0x66, 0x66}, //R
  {0x3C, 0x66, 0x60, 0x7C, 0x3E, 0x06, 0x66, 0x3C}, //S
  {0x7E, 0x7E, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18}, //T
  {0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x7E, 0x3C}, //U
  {0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C, 0x18}, //V
  {0xC3, 0xC3, 0xC3, 0xC3, 0xDB, 0xFF, 0xE7, 0xC3}, //W
  {0xC3, 0xC3, 0xE7, 0x7E, 0x3C, 0xE7, 0xC3, 0xC3}, //X
  {0x66, 0x66, 0x66, 0x66, 0x3C, 0x18, 0x18, 0x18}, //Y
  {0x7E, 0x7E, 0x06, 0x0E, 0x38, 0x60, 0x7E, 0x7E}, //Z
  {0x00, 0x00, 0x00, 0x7E, 0x7E, 0x00, 0x00, 0x00}  //-
};

void text() {
  if (loading) {
    clearCube();
    charPosition = -1;
    charCounter = 0;
    loading = false;
    currentEffectOriginalTime = TEXT_TIME;
    currentEffectTime = currentEffectOriginalTime * timeScale;
    textToDisplay.toUpperCase();
    textToDisplay = String(textToDisplay + " ");

    Serial.print(textToDisplay);
    char character;
    for (uint8_t i = 0; i < textToDisplay.length(); i++) {
      textToDisplay.replace("%C4%85", "A");
      textToDisplay.replace("%C4%87", "C");
      textToDisplay.replace("%C4%99", "E");
      textToDisplay.replace("%C5%82", "L");
      textToDisplay.replace("%C5%84", "N");
      textToDisplay.replace("%C3%B3", "O");
      textToDisplay.replace("%C5%9B", "S");
      textToDisplay.replace("%C5%BA", "Z");
      textToDisplay.replace("%C5%BC", "Z");
    }
    Serial.print(textToDisplay);
  }
  timer++;
  if (timer > currentEffectTime) {
    timer = 0;

    shift(POSITION_X);
    charPosition++;

    if (charPosition == 8) {
      charCounter++;
      if (charCounter > textToDisplay.length() - 1) {
        charCounter = 0;
      }
      charPosition = 0;
    }

    if (charPosition == 0) {
      for (uint8_t i = 0; i < 8; i++) {
        for (uint8_t j = 0; j < 8; j++) {
          if(textToDisplay[charCounter] >= '0' && textToDisplay[charCounter] <= '9'){
            cube[i][j] = BIT(characters[textToDisplay[charCounter] - '0'][i], j);
          }
          else if(textToDisplay[charCounter] >= 'A' && textToDisplay[charCounter] <= 'Z'){
            cube[i][j] = BIT(characters[textToDisplay[charCounter] - 'A' + 10][i], j);
          }
          else if(textToDisplay[charCounter] == '-'){
            cube[i][j] = BIT(characters[36][i], j);
          }
        }
      }
    }
  }
}
