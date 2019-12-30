uint8_t layerPosition = 0;
uint8_t layerDirection = 0;
uint8_t frameNumber = 0;
uint8_t voxelsDestinations[8][8];

void axisUpdownRandsuspend() {
  if (loading) {
    clearCube();
    setLayer(Z_axis, layerPosition);
    if (layerPosition == 0) {
      layerDirection = POSITION_Z;
    } else {
      layerDirection = NEG_Z;
    }
    setLayer(Z_axis, layerPosition);
    generateRandomVoxels();
    frameNumber = 0;
    timer = 0;
    loading = false;
    currentEffectTime = timeScale * AXIS_UPDOWN_RANDSUSPEND_TIME;
  }
  timer++;
  if (timer > currentEffectTime) {
    timer = 0;
    if (layerDirection % 2 == 1) {
      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
          for (int k = 0; k < 8; k++) {
            if ( getVoxel(cube, i, j, k) && (getVoxel(cube, i, j, k) != getVoxel(voxelsDestinations, i, j, k))) {
              shiftVoxel(layerDirection, i, j, k);
            }
          }
        }
      }
    }
    else {
      for (int i = 7; i >= 0; i--) {
        for (int j = 7; j >= 0; j--) {
          for (int k = 7; k >= 0; k--) {
            if ( getVoxel(cube, i, j, k) && (getVoxel(cube, i, j, k) != getVoxel(voxelsDestinations, i, j, k))) {
              shiftVoxel(layerDirection, i, j, k);
            }
          }
        }
      }
    }


    frameNumber++;
    if (frameNumber % 8 == 0 && frameNumber % 16 != 0) {
      layerPosition = (layerPosition == 0) ? 7 : 0;
      generateLayerDestinations();
      timer = - 5 * currentEffectTime;
    }
    else if (frameNumber == 16) {
      layerDirection = layerDirection == 2 ? 3 : 2;
      generateRandomVoxels();
      timer = - 5 * currentEffectTime;
    }
    else if (frameNumber == 32) {
      loading = true;
    }
  }
}

void generateLayerDestinations() {
  for (int j = 0; j < 8; j++) {
    for (int k = 0; k < 8; k++) {
      voxelsDestinations[j][k] = 0;
    }
  }

  for (uint8_t j = 0; j < 8; j++) {
    for (uint8_t k = 0; k < 8; k++) {
      setVoxel(voxelsDestinations, j, k, layerPosition);
    }
  }
}

void generateRandomVoxels() {
  for (int j = 0; j < 8; j++) {
    for (int k = 0; k < 8; k++) {
      voxelsDestinations[j][k] = 0;
    }
  }
  uint8_t temporaryArray[8][8];
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      temporaryArray[i][j] = 0x01 << random(0, 8);
    }
  }
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      for (int k = 0; k < 8; k++) {
        if (BIT(temporaryArray[j][k], i)) {
          setVoxel(voxelsDestinations, k, j, i);
        }
      }
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
