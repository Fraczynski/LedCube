void renderCube() {
  layer++;
  if (layer >= 8) {
    layer = 0;
  }
  digitalWrite(RCLK, LOW);

  for (int i = 0; i < 8; i++) {
    digitalWrite(SRCLK, LOW);
    if (i != layer) {
      digitalWrite(SER, 0);
    }
    else {
      digitalWrite(SER, 1);
    }
    digitalWrite(SRCLK, HIGH);
  }

  for (int i = 0 ; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
        digitalWrite(SRCLK, LOW);
        digitalWrite(SER, BIT(cube[layer][j], i));
        digitalWrite(SRCLK, HIGH);
      }
    }
  digitalWrite(RCLK, HIGH);
}

void setVoxel(uint8_t x, uint8_t y, uint8_t z) {
  cube[7 - y][7 - z] |= (0x01 << x);
}

void clearVoxel(uint8_t x, uint8_t y, uint8_t z) {
  cube[7 - y][7 - z] ^= (0x01 << x);
}

bool getVoxel(uint8_t x, uint8_t y, uint8_t z) {
  return (cube[7 - y][7 - z] & (0x01 << x)) == (0x01 << x);
}

void lightCube() {
  for (uint8_t i = 0; i < 8; i++) {
    for (uint8_t j = 0; j < 8; j++) {
      cube[i][j] = 0xFF;
    }
  }
}

void clearCube() {
  for (uint8_t i = 0; i < 8; i++) {
    for (uint8_t j = 0; j < 8; j++) {
      cube[i][j] = 0;
    }
  }
}
