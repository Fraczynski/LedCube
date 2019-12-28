bool sending = false;
bool exploded = false;
uint8_t gravitation = 0;

void fireworks() {
  if (loading) {
    clearCube();
    loading = false;
    currentEffectTime = timeScale * FIREWORKS_TIME;
  }

  timer++;
  if (timer > currentEffectTime) {
    timer = 0;
    if (!sending && !exploded) {
      clearCube();
      selX = random(0, 8);
      selZ = random(0, 8);
      selY = 0;
      sending = true;
    }
    else if (exploded) {
      uint8_t newX = 0;
      uint8_t newY = 0;
      uint8_t newZ = 0;

      for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
          for (int k = 0; k < 8; k++) {
            if (getVoxel(i, j, k)) {
              clearVoxel(i, j, k);
              if (i < selX) {
                newX = i - 1;
              }
              else {
                newX = i + 1;
              }
              if (j < selY) {
                newY = j - 1;
              }
              else {
                newY = j + 1;
              }
              if (k < selZ) {
                newZ = k - 1;
              }
              else {
                newZ = k + 1;
              }
              setVoxel(newX, newY, newZ);
            }
          }
        }
      }
      gravitation++;
      if (gravitation > 3) {
        gravitation = 0;
        shift(NEG_Y);
        selY--;
        if (selY < 0) {
          sending = false;
        }
      }
    }
    else {
      selY++;
      setVoxel(selX, selY, selZ);
      clearVoxel(selX, selY - 1, selZ);
      if (selY == 6) {
        sending = false;
        exploded = true;
        drawCube(selX - 1, selY - 1, selZ - 1, 3);
      }
    }
  }
}
