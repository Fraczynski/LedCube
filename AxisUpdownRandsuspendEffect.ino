uint8_t layerPosition = 0;
uint8_t layerDirection = 0;
uint8_t frameNumber = 0;
uint8_t voxelsDestinations[8][8];
uint8_t axis = 0;

void axisUpdownRandsuspend() {
  if (loading) {
    clearCube();
    axis = random(0, 3);
    layerPosition = random(0, 2) * 7;
    setLayer(axis, layerPosition);
    if (axis == X_axis) {
      if (layerPosition == 0) {
        layerDirection = POSITION_X;
      } else {
        layerDirection = NEG_X;
      }
    } else if (axis == Y_axis) {
      if (layerPosition == 0) {
        layerDirection = POSITION_Y;
      } else {
        layerDirection = NEG_Y;
      }
    } else if (axis == Z_axis) {
      if (layerPosition == 0) {
        layerDirection = POSITION_Z;
      } else {
        layerDirection = NEG_Z;
      }
    }
    setLayer(axis, layerPosition);
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
      layerDirection = layerDirection % 2 == 0 ? layerDirection + 1 : layerDirection - 1;
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
      if (axis == X_axis) {
        setVoxel(voxelsDestinations, layerPosition, j, k);
      } else if (axis == Y_axis) {
        setVoxel(voxelsDestinations, j, layerPosition, k);
      } else if (axis == Z_axis) {
        setVoxel(voxelsDestinations, j, k, layerPosition);
      }
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
  if (axis == X_axis) {
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        for (int k = 0; k < 8; k++) {
          if (BIT(temporaryArray[j][k], i)) {
            setVoxel(voxelsDestinations, i, j, k);
          }
        }
      }
    }
  }
  if (axis == Y_axis) {
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        for (int k = 0; k < 8; k++) {
          if (BIT(temporaryArray[j][k], i)) {
            setVoxel(voxelsDestinations, j, i, k);
          }
        }
      }
    }
  }
  if (axis == Z_axis) {
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
}
