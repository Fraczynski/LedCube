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

void copyCube(uint8_t fromCube[8][8], uint8_t toCube[8][8]) {
  for (int j = 0; j < 8; j++) {
    for (int k = 0; k < 8; k++) {
      toCube[j][k] = fromCube[j][k];
    }
  }
}

void lightCube() {
  if(loading){
    for (uint8_t i = 0; i < 8; i++) {
      for (uint8_t j = 0; j < 8; j++) {
        cube[i][j] = 0xFF;
      }
    }
    loading = false;
  }
}

void clearCube() {
  for (uint8_t i = 0; i < 8; i++) {
    for (uint8_t j = 0; j < 8; j++) {
      cube[i][j] = 0;
    }
  }
}

void setVoxel(uint8_t voxelsArray[8][8], uint8_t x, uint8_t y, uint8_t z) {
  voxelsArray[7 - y][7 - z] |= (0x01 << x);
}

void clearVoxel(uint8_t voxelsArray[8][8], uint8_t x, uint8_t y, uint8_t z) {
  voxelsArray[7 - y][7 - z] ^= (0x01 << x);
}

bool getVoxel(uint8_t voxelsArray[8][8], uint8_t x, uint8_t y, uint8_t z) {
  return (voxelsArray[7 - y][7 - z] & (0x01 << x)) == (0x01 << x);
}

void clearCube(uint8_t voxelsArray[8][8]) {
  for (uint8_t i = 0; i < 8; i++) {
    for (uint8_t j = 0; j < 8; j++) {
      voxelsArray[i][j] = 0;
    }
  }
}

void setLayer(uint8_t axis, uint8_t i) {
  for (uint8_t j = 0; j < 8; j++) {
    for (uint8_t k = 0; k < 8; k++) {
      if (axis == X_axis) {
        setVoxel(i, j, k);
      } else if (axis == Y_axis) {
        setVoxel(j, i, k);
      } else if (axis == Z_axis) {
        setVoxel(j, k, i);
      }
    }
  }
}
