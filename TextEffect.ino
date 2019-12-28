uint8_t charCounter = 0;
uint8_t charPosition = 0;

void text(char string[], uint8_t len) {
  if (loading) {
    clearCube();
    charPosition = -1;
    charCounter = 0;
    loading = false;
    currentEffectTime = timeScale * TEXT_TIME;
  }
  timer++;
  if (timer > currentEffectTime) {
    timer = 0;

    shift(NEG_Z);
    charPosition++;

    if (charPosition == 7) {
      charCounter++;
      if (charCounter > len - 1) {
        charCounter = 0;
      }
      charPosition = 0;
    }

    if (charPosition == 0) {
      for (uint8_t i = 0; i < 8; i++) {
        cube[i][0] = characters[string[charCounter] - '0'][i];
      }
    }
  }
}
